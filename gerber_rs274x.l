%top{
	#include "gerber_parser.yy.hh"
}

%{
	// This include needs to be here, because we need the GerberRS274XScanner class
	// to be defined before yylex is defined, but we need the include to be after
	// FlexLexer.h is included, or else it is included twice
	#include "gerber_rs274x_scanner.hh"

	// Include these to get the proper enum types in scope
	#include "GerberClasses/LevelPolarity.hh"
	#include "GerberClasses/UnitSpecifier.hh"

	#include <stdlib.h>
	#include <string.h>

	int return_state;

	#define YY_USER_INIT return_state = INITIAL;

	yy::GerberRS274XParser::location_type scan_location;
%}

%option outfile="gerber_scanner.yy.cc"
%option 8bit
%option default
%option never-interactive
%option noyywrap
%option nounput
%option noinput
%option c++
%option yyclass="GerberRS274XScanner"
%option debug

%x PARSING_COORD_FORMAT
%x PARSING_COMMENT_STRING
%x PARSING_APERTURE_NUMBER
%x PARSING_APERTURE_TEMPLATE
%x PARSING_APERTURE_MODIFIERS
%x PARSING_APERTURE_MACRO_NAME
%x PARSING_APERTURE_MACRO_CONTENT
%x PARSING_ARITHMETIC_EXPRESSION
%x PARSING_APERTURE_PRIMITIVE
%x PARSING_APERTURE_COMMENT
%x PARSING_STEP_AND_REPEAT

INTERPOLATE_CMD D0{0,9}1
MOVE_CMD D0{0,9}2
FLASH_CMD D0{0,9}3
APERTURE_NUMBER D[1-9][[:digit:]]+
LINEAR_INTERP_MODE G0{0,9}1
CW_CIRC_INTERP_MODE G0{0,9}2
CCW_CIRC_INTERP_MODE G0{0,9}3
COMMENT_START G0{0,9}4
SINGLE_QUADRANT_MODE G0{0,8}74
MULTI_QUADRANT_MODE G0{0,8}75
REGION_MODE_ON G0{0,8}36
REGION_MODE_OFF G0{0,8}37
END_OF_FILE M0{0,9}2
STRING [[:alnum:]_+-/!?<>"'(){}.\|&@# ,;$:=]+
COMMENT_STRING ([[:alnum:]_+-/?<>"'(){}.\|& ,;$:=])([[:alnum:]_+-/!?<>"'(){}.\|&@# ,;$:=\n])*
NAME [[:alpha:]_.$]([[:alnum:]_.]*)
COORD_FORMAT FSLA
UNIT_SPECIFIER MO((IN)|(MM))
APERTURE_DEFINITION AD
APERTURE_MACRO AM
VARIABLE_DEFINITION \$[[:digit:]]+=
ARITHMETIC_ADD "+"
ARITHMETIC_SUB "-"
ARITHMETIC_MULT "x"
ARITHMETIC_DIV "/"
ARITHMETIC_LEFT_PAREN "("
ARITHMETIC_RIGHT_PAREN ")"
ARITHMETIC_VAR_REFERENCE \$[[:digit:]]+
APERTURE_PRIMITIVE_CIRCLE "1"
APERTURE_PRIMITIVE_VECTOR_LINE "20"
APERTURE_PRIMITIVE_CENTER_LINE "21"
APERTURE_PRIMITIVE_OUTLINE "4"
APERTURE_PRIMITIVE_POLYGON "5"
APERTURE_PRIMITIVE_MOIRE "6"
APERTURE_PRIMITIVE_THERMAL "7"
APERTURE_COMMENT_START "0 "
STEP_AND_REPEAT_START SR
LEVEL_POLARITY LP(C|D)


INT_WO_SIGN [[:digit:]]+
INT_W_SIGN (\+|\-)?[[:digit:]]+
DECIMAL (\+|\-)?[[:digit:]]*\.?[[:digit:]]*

EXT_CMD_DELIMITER "%"
END_OF_DATA_BLOCK "*"
APERTURE_PRIMITIVE_MODIFIER_DELIMITER ","

%%

<*>\n										// Eat up newlines

{LEVEL_POLARITY}									{
														// Third character in matched text should be either C or D
														// for Clear and Dark
														if (YYText()[2] == 'C') {
															yylval->build(LevelPolarity::LevelPolarityType::LEVEL_POLARITY_CLEAR);
														} else if (YYText()[2] == 'D') {
															yylval->build(LevelPolarity::LevelPolarityType::LEVEL_POLARITY_DARK);
														}
														return yy::GerberRS274XParser::token::LEVEL_POLARITY;
													}

X{INT_W_SIGN}										{
														yylval->build(atoi(&(YYText()[1]))); // Skip X
														return yy::GerberRS274XParser::token::X_COORDINATE;
													}
				
Y{INT_W_SIGN}										{
														yylval->build(atoi(&(YYText()[1]))); // Skip Y
														return yy::GerberRS274XParser::token::Y_COORDINATE;
													}
				
I{INT_W_SIGN}										{
														yylval->build(atoi(&(YYText()[1]))); // Skip I
														return yy::GerberRS274XParser::token::I_OFFSET;
													}
				
J{INT_W_SIGN}										{
														yylval->build(atoi(&(YYText()[1]))); // Skip J
														return yy::GerberRS274XParser::token::J_OFFSET;
													}

{STEP_AND_REPEAT_START}								{
														return_state = INITIAL;
														BEGIN(PARSING_STEP_AND_REPEAT);
														return yy::GerberRS274XParser::token::STEP_AND_REPEAT_START;
													}

<PARSING_STEP_AND_REPEAT>X{INT_WO_SIGN}				{
														yylval->build(atoi(&(YYText()[1]))); // Skip X
														return yy::GerberRS274XParser::token::X_REPEATS;
													}

<PARSING_STEP_AND_REPEAT>Y{INT_WO_SIGN}				{
														yylval->build(atoi(&(YYText()[1]))); // Skip Y
														return yy::GerberRS274XParser::token::Y_REPEATS;
													}

<PARSING_STEP_AND_REPEAT>I{DECIMAL}					{
														yylval->build(strtod(&(YYText()[1]), NULL)); // Skip I
														return yy::GerberRS274XParser::token::X_STEP_DISTANCE;
													}

<PARSING_STEP_AND_REPEAT>J{DECIMAL}					{
														yylval->build(strtod(&(YYText()[1]), NULL)); // Skip J
														return yy::GerberRS274XParser::token::Y_STEP_DISTANCE;
													}
				
<*>{END_OF_DATA_BLOCK}						{
												BEGIN(return_state);
												return yy::GerberRS274XParser::token::END_OF_DATA_BLOCK;
											}
					
<*>{EXT_CMD_DELIMITER}							{
												// An extended command delimiter always sets us back to the initial state
												BEGIN(INITIAL);
												return_state = INITIAL;
												return yy::GerberRS274XParser::token::EXT_CMD_DELIMITER;
											}
					
{INTERPOLATE_CMD}							{
												return yy::GerberRS274XParser::token::D_CMD_TYPE_INTERPOLATE;
											}

{MOVE_CMD}									{
												return yy::GerberRS274XParser::token::D_CMD_TYPE_MOVE;
											}
					
{FLASH_CMD}									{
												return yy::GerberRS274XParser::token::D_CMD_TYPE_FLASH;
											}
					
{APERTURE_NUMBER}							{
												yylval->build(atoi(&(YYText()[1]))); // Skip D
												return yy::GerberRS274XParser::token::APERTURE_NUMBER;
											}

{LINEAR_INTERP_MODE}						{
												return yy::GerberRS274XParser::token::G_CMD_TYPE_LINEAR_INTERP_MODE;
											}

{CW_CIRC_INTERP_MODE}						{
												return yy::GerberRS274XParser::token::G_CMD_TYPE_CW_CIRC_INTERP_MODE;
											}

{CCW_CIRC_INTERP_MODE}						{
												return yy::GerberRS274XParser::token::G_CMD_TYPE_CCW_CIRC_INTERP_MODE;
											}
						
{REGION_MODE_ON}							{
												return yy::GerberRS274XParser::token::G_CMD_TYPE_REGION_MODE_ON;
											}

{REGION_MODE_OFF}							{
												return yy::GerberRS274XParser::token::G_CMD_TYPE_REGION_MODE_OFF;
											}
						
{SINGLE_QUADRANT_MODE}						{
												return yy::GerberRS274XParser::token::G_CMD_TYPE_SINGLE_QUADRANT_MODE;
											}
						
{MULTI_QUADRANT_MODE}						{
												return yy::GerberRS274XParser::token::G_CMD_TYPE_MULTI_QUADRANT_MODE;
											}
						
{END_OF_FILE}								{
												return yy::GerberRS274XParser::token::END_OF_FILE;
											}
						
{COORD_FORMAT}								{
												return_state = INITIAL;
												BEGIN(PARSING_COORD_FORMAT);
												return yy::GerberRS274XParser::token::COORD_FORMAT;
											}

<PARSING_COORD_FORMAT>X{INT_WO_SIGN}		{
												yylval->build(atoi(&(YYText()[1]))); // Skip X
												return yy::GerberRS274XParser::token::COORD_FORMAT_NUM_INT_POSITIONS;
											}
										
<PARSING_COORD_FORMAT>Y{INT_WO_SIGN}		{
												yylval->build(atoi(&(YYText()[1]))); // Skip Y
												return yy::GerberRS274XParser::token::COORD_FORMAT_NUM_DEC_POSITIONS;
											}
										
{UNIT_SPECIFIER}							{
												if (strncmp(&(YYText()[2]), "IN", 2) == 0) {
													yylval->build(UnitSpecifier::UnitType::UNIT_TYPE_IN);
												} else {
													yylval->build(UnitSpecifier::UnitType::UNIT_TYPE_MM);
												}
												return yy::GerberRS274XParser::token::UNIT_SPECIFIER;
											}
										
{COMMENT_START}								{
												return_state = INITIAL;
												BEGIN(PARSING_COMMENT_STRING);
												return yy::GerberRS274XParser::token::COMMENT_START;
											}
										
<PARSING_COMMENT_STRING>{COMMENT_STRING}	{
												char* comment_string = (char*)malloc(YYLeng() + 1);
												strncpy(comment_string, YYText(), YYLeng());
												comment_string[YYLeng()] = '\0';
												yylval->build(comment_string);
												return yy::GerberRS274XParser::token::COMMENT_STRING;
											}

{APERTURE_DEFINITION}						{
												return_state = INITIAL;
												BEGIN(PARSING_APERTURE_NUMBER);
												return yy::GerberRS274XParser::token::APERTURE_DEFINITION;
											}

<PARSING_APERTURE_NUMBER>{APERTURE_NUMBER}		{
													BEGIN(PARSING_APERTURE_TEMPLATE);
													yylval->build(atoi(&(YYText()[1]))); // Skip D
													return yy::GerberRS274XParser::token::APERTURE_NUMBER;
												}

<PARSING_APERTURE_TEMPLATE>C					{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													return yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_CIRCLE;
												}

<PARSING_APERTURE_TEMPLATE>R					{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													return yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_RECTANGLE;
												}

<PARSING_APERTURE_TEMPLATE>O					{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													return yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_OBROUND;
												}

<PARSING_APERTURE_TEMPLATE>P					{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													return yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_POLYGON;
												}


<PARSING_APERTURE_TEMPLATE>{NAME}				{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													char* custom_aperture_name = (char*)malloc(YYLeng() + 1);
													strncpy(custom_aperture_name, YYText(), YYLeng());
													custom_aperture_name[YYLeng()] = '\0';
													yylval->build(custom_aperture_name);
													return yy::GerberRS274XParser::token::CUSTOM_APERTURE_NAME;
												}

<PARSING_APERTURE_MODIFIERS>[,X]{DECIMAL}		{
													yylval->build(strtod(&(YYText()[1]), NULL)); // Skip , or X
													return yy::GerberRS274XParser::token::APERTURE_DEFINITION_MODIFIER;
												}

{APERTURE_MACRO}								{
													return_state = PARSING_APERTURE_MACRO_CONTENT;
													BEGIN(PARSING_APERTURE_MACRO_NAME);
													return yy::GerberRS274XParser::token::APERTURE_MACRO;
												}

<PARSING_APERTURE_MACRO_NAME>{NAME}				{

													char* custom_aperture_name = (char*)malloc(YYLeng() + 1);
													strncpy(custom_aperture_name, YYText(), YYLeng());
													custom_aperture_name[YYLeng()] = '\0';
													yylval->build(custom_aperture_name);
													return yy::GerberRS274XParser::token::CUSTOM_APERTURE_NAME;
												}

<PARSING_APERTURE_MACRO_CONTENT>{VARIABLE_DEFINITION}	{
															BEGIN(PARSING_ARITHMETIC_EXPRESSION);
															char temp_buffer[YYLeng() - 1]; // We're chopping off two characters, adding one extra for the terminating null
															strncpy(temp_buffer, &(YYText()[1]), YYLeng() - 2); // Copy the variable number, less the preceding $ and the following =
															temp_buffer[YYLeng() - 2] = '\0';
															yylval->build(atoi(temp_buffer));
															return yy::GerberRS274XParser::token::VARIABLE_DEFINITION;
														}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_COMMENT_START}			{
																		BEGIN(PARSING_APERTURE_COMMENT);
																		return yy::GerberRS274XParser::token::APERTURE_COMMENT_START;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_CIRCLE}			{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_CIRCLE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_VECTOR_LINE}	{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_VECTOR_LINE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_CENTER_LINE}	{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_CENTER_LINE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_OUTLINE}		{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_OUTLINE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_POLYGON}		{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_POLYGON;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_MOIRE}			{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_MOIRE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_THERMAL}		{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_THERMAL;
																	}

<PARSING_APERTURE_COMMENT>{COMMENT_STRING}							{
																		char* aperture_comment = (char*)malloc(YYLeng() + 1);
																		strncpy(aperture_comment, YYText(), YYLeng());
																		aperture_comment[YYLeng()] = '\0';
																		yylval->build(aperture_comment);
																		return yy::GerberRS274XParser::token::APERTURE_COMMENT_CONTENT;
																	}

<PARSING_APERTURE_PRIMITIVE>{APERTURE_PRIMITIVE_MODIFIER_DELIMITER}	{
																		return yy::GerberRS274XParser::token::AM_DELIM;
																	}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_ADD}				{
																							return yy::GerberRS274XParser::token::ARITHMETIC_ADD;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_SUB}				{
																							return yy::GerberRS274XParser::token::ARITHMETIC_SUB;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_MULT}				{
																							return yy::GerberRS274XParser::token::ARITHMETIC_MULT;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_DIV}				{
																							return yy::GerberRS274XParser::token::ARITHMETIC_DIV;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_LEFT_PAREN}		{
																							return yy::GerberRS274XParser::token::ARITHMETIC_LEFT_PAREN;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_RIGHT_PAREN}		{
																							return yy::GerberRS274XParser::token::ARITHMETIC_RIGHT_PAREN;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_VAR_REFERENCE}	{
																							yylval->build(atoi(&(YYText()[1]))); // Skip $
																							return yy::GerberRS274XParser::token::ARITHMETIC_VAR_REFERENCE;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{DECIMAL}						{
																							yylval->build(strtod(YYText(), NULL));
																							return yy::GerberRS274XParser::token::ARITHMETIC_CONSTANT;
																						}
%%


