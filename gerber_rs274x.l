%top{
	#include "gerber_parser.yy.h"
}

%{
	#include "gerber_scanner_defs.h"

	#include <stdlib.h>
	#include <string.h>

	int return_state;

	#define YY_USER_INIT return_state = INITIAL;
%}

%option header-file="gerber_scanner.yy.h"
%option outfile="gerber_scanner.yy.c"
%option 8bit
%option default
%option never-interactive
%option noyywrap
%option bison-bridge
%option bison-locations
%option reentrant

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
														if (yytext[2] == 'C') {
															yylval->level_polarity = LEVEL_POLARITY_CLEAR;
														} else if (yytext[2] == 'D') {
															yylval->level_polarity = LEVEL_POLARITY_DARK;
														}
														return LEVEL_POLARITY;
													}

X{INT_W_SIGN}										{
														yylval->x_coordinate = atoi(&(yytext[1])); // Skip X
														return X_COORDINATE;
													}
				
Y{INT_W_SIGN}										{
														yylval->y_coordinate = atoi(&(yytext[1])); // Skip Y
														return Y_COORDINATE;
													}
				
I{INT_W_SIGN}										{
														yylval->i_offset = atoi(&(yytext[1])); // Skip I
														return I_OFFSET;
													}
				
J{INT_W_SIGN}										{
														yylval->j_offset = atoi(&(yytext[1])); // Skip J
														return J_OFFSET;
													}

{STEP_AND_REPEAT_START}								{
														return_state = INITIAL;
														BEGIN(PARSING_STEP_AND_REPEAT);
														return STEP_AND_REPEAT_START;
													}

<PARSING_STEP_AND_REPEAT>X{INT_WO_SIGN}				{
														yylval->x_repeats = atoi(&(yytext[1])); // Skip X
														return X_REPEATS;
													}

<PARSING_STEP_AND_REPEAT>Y{INT_WO_SIGN}				{
														yylval->y_repeats = atoi(&(yytext[1])); // Skip Y
														return Y_REPEATS;
													}

<PARSING_STEP_AND_REPEAT>I{DECIMAL}					{
														yylval->x_step_distance = atoi(&(yytext[1])); // Skip I
														return X_STEP_DISTANCE;
													}

<PARSING_STEP_AND_REPEAT>J{DECIMAL}					{
														yylval->y_step_distance = atoi(&(yytext[1])); // Skip J
														return Y_STEP_DISTANCE;
													}
				
<*>{END_OF_DATA_BLOCK}						{
												BEGIN(return_state);
												return END_OF_DATA_BLOCK;
											}
					
<*>{EXT_CMD_DELIMITER}							{
												// An extended command delimiter always sets us back to the initial state
												BEGIN(INITIAL);
												return_state = INITIAL;
												return EXT_CMD_DELIMITER;
											}
					
{INTERPOLATE_CMD}							{
												return D_CMD_TYPE_INTERPOLATE;
											}

{MOVE_CMD}									{
												return D_CMD_TYPE_MOVE;
											}
					
{FLASH_CMD}									{
												return D_CMD_TYPE_FLASH;
											}
					
{APERTURE_NUMBER}							{
												yylval->aperture_number = atoi(&(yytext[1])); // Skip D
												return APERTURE_NUMBER;
											}

{LINEAR_INTERP_MODE}						{
												return G_CMD_TYPE_LINEAR_INTERP_MODE;
											}

{CW_CIRC_INTERP_MODE}						{
												return G_CMD_TYPE_CW_CIRC_INTERP_MODE;
											}

{CCW_CIRC_INTERP_MODE}						{
												return G_CMD_TYPE_CCW_CIRC_INTERP_MODE;
											}
						
{REGION_MODE_ON}							{
												return G_CMD_TYPE_REGION_MODE_ON;
											}

{REGION_MODE_OFF}							{
												return G_CMD_TYPE_REGION_MODE_OFF;
											}
						
{SINGLE_QUADRANT_MODE}						{
												return G_CMD_TYPE_SINGLE_QUADRANT_MODE;
											}
						
{MULTI_QUADRANT_MODE}						{
												return G_CMD_TYPE_MULTI_QUADRANT_MODE;
											}
						
{END_OF_FILE}								{
												return END_OF_FILE;
											}
						
{COORD_FORMAT}								{
												return_state = INITIAL;
												BEGIN(PARSING_COORD_FORMAT);
												return COORD_FORMAT;
											}

<PARSING_COORD_FORMAT>X{INT_WO_SIGN}		{
												yylval->num_int_positions = atoi(&(yytext[1])); // Skip X
												return COORD_FORMAT_NUM_INT_POSITIONS;
											}
										
<PARSING_COORD_FORMAT>Y{INT_WO_SIGN}		{
												yylval->num_dec_positions = atoi(&(yytext[1])); // Skip Y
												return COORD_FORMAT_NUM_DEC_POSITIONS;
											}
										
{UNIT_SPECIFIER}							{
												if (strncmp(&(yytext[2]), "IN", 2) == 0) {
													yylval->unit_type = UNIT_TYPE_IN;
												} else {
													yylval->unit_type = UNIT_TYPE_MM;
												}
												return UNIT_SPECIFIER;
											}
										
{COMMENT_START}								{
												return_state = INITIAL;
												BEGIN(PARSING_COMMENT_STRING);
												return COMMENT_START;
											}
										
<PARSING_COMMENT_STRING>{COMMENT_STRING}	{
												yylval->comment_string = malloc(yyleng + 1);
												strncpy(yylval->comment_string, yytext, yyleng);
												yylval->comment_string[yyleng] = '\0';
												return COMMENT_STRING;
											}

{APERTURE_DEFINITION}						{
												return_state = INITIAL;
												BEGIN(PARSING_APERTURE_NUMBER);
												return APERTURE_DEFINITION;
											}

<PARSING_APERTURE_NUMBER>{APERTURE_NUMBER}		{
													BEGIN(PARSING_APERTURE_TEMPLATE);
													yylval->aperture_number = atoi(&(yytext[1])); // Skip D
													return APERTURE_NUMBER;
												}

<PARSING_APERTURE_TEMPLATE>C					{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													return STANDARD_APERTURE_TYPE_CIRCLE;
												}

<PARSING_APERTURE_TEMPLATE>R					{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													return STANDARD_APERTURE_TYPE_RECTANGLE;
												}

<PARSING_APERTURE_TEMPLATE>O					{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													return STANDARD_APERTURE_TYPE_OBROUND;
												}

<PARSING_APERTURE_TEMPLATE>P					{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													return STANDARD_APERTURE_TYPE_POLYGON;
												}


<PARSING_APERTURE_TEMPLATE>{NAME}				{
													BEGIN(PARSING_APERTURE_MODIFIERS);
													yylval->custom_aperture_name = malloc(yyleng + 1);
													strncpy(yylval->custom_aperture_name, yytext, yyleng);
													yylval->custom_aperture_name[yyleng] = '\0';
													return CUSTOM_APERTURE_NAME;
												}

<PARSING_APERTURE_MODIFIERS>[,X]{DECIMAL}		{
													yylval->aperture_definition_modifier = strtod(&(yytext[1]), NULL); // Skip , or X
													return APERTURE_DEFINITION_MODIFIER;
												}

{APERTURE_MACRO}								{
													return_state = PARSING_APERTURE_MACRO_CONTENT;
													BEGIN(PARSING_APERTURE_MACRO_NAME);
													return APERTURE_MACRO;
												}

<PARSING_APERTURE_MACRO_NAME>{NAME}				{

													yylval->custom_aperture_name = malloc(yyleng + 1);
													strncpy(yylval->custom_aperture_name, yytext, yyleng);
													yylval->custom_aperture_name[yyleng] = '\0';
													return CUSTOM_APERTURE_NAME;
												}

<PARSING_APERTURE_MACRO_CONTENT>{VARIABLE_DEFINITION}	{
															BEGIN(PARSING_ARITHMETIC_EXPRESSION);
															char temp_buffer[yyleng - 1]; // We're chopping off two characters, adding one extra for the terminating null
															strncpy(temp_buffer, &(yytext[1]), yyleng - 2); // Copy the variable number, less the preceding $ and the following =
															temp_buffer[yyleng - 2] = '\0';
															yylval->variable_definition = atoi(temp_buffer);
															return VARIABLE_DEFINITION;
														}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_COMMENT_START}			{
																		BEGIN(PARSING_APERTURE_COMMENT);
																		return APERTURE_COMMENT_START;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_CIRCLE}			{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return APERTURE_PRIMITIVE_TYPE_CIRCLE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_VECTOR_LINE}	{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return APERTURE_PRIMITIVE_TYPE_VECTOR_LINE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_CENTER_LINE}	{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return APERTURE_PRIMITIVE_TYPE_CENTER_LINE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_OUTLINE}		{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return APERTURE_PRIMITIVE_TYPE_OUTLINE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_POLYGON}		{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return APERTURE_PRIMITIVE_TYPE_POLYGON;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_MOIRE}			{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return APERTURE_PRIMITIVE_TYPE_MOIRE;
																	}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_THERMAL}		{
																		BEGIN(PARSING_APERTURE_PRIMITIVE);
																		return APERTURE_PRIMITIVE_TYPE_THERMAL;
																	}

<PARSING_APERTURE_COMMENT>{COMMENT_STRING}							{
																		yylval->aperture_comment = malloc(yyleng + 1);
																		strncpy(yylval->aperture_comment, yytext, yyleng);
																		yylval->aperture_comment[yyleng] = '\0';
																		return APERTURE_COMMENT_CONTENT;
																	}

<PARSING_APERTURE_PRIMITIVE>{APERTURE_PRIMITIVE_MODIFIER_DELIMITER}	{
																		return AM_DELIM;
																	}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_ADD}				{
																							return ARITHMETIC_ADD;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_SUB}				{
																							return ARITHMETIC_SUB;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_MULT}				{
																							return ARITHMETIC_MULT;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_DIV}				{
																							return ARITHMETIC_DIV;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_LEFT_PAREN}		{
																							return ARITHMETIC_LEFT_PAREN;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_RIGHT_PAREN}		{
																							return ARITHMETIC_RIGHT_PAREN;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_VAR_REFERENCE}	{
																							yylval->arithmetic_var_reference = atoi(&(yytext[1])); // Skip $
																							return ARITHMETIC_VAR_REFERENCE;
																						}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{DECIMAL}						{
																							yylval->arithmetic_constant = strtod(yytext, NULL);
																							return ARITHMETIC_CONSTANT;
																						}
%%


