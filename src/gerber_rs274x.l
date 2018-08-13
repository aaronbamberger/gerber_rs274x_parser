%top{
	#include "gerber_parser.yy.hh"
}

%{
	// This include needs to be here, because we need the GerberRS274XScanner class
	// to be defined before yylex is defined, but we need the include to be after
	// FlexLexer.h is included, or else it is included twice
	#include "gerber_rs274x_scanner.hh"

    #include "GlobalDefs.hh"

    #include <string>

	int return_state;

	#define YY_USER_INIT return_state = INITIAL;
	
	// Normal location update for most patterns, token is entire match
    #define UPDATE_LOCATION_COLS_STANDARD yylloc->columns(YYLeng())
	
	// Location update that skips the 1st character in the match
    #define UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR yylloc->columns(1); yylloc->step(); yylloc->columns(YYLeng() - 1)
%}

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
%x PARSING_COORD_FORMAT_NUM_INT_POSITIONS
%x PARSING_COORD_FORMAT_NUM_DEC_POSITIONS
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

BLANK [ \t]

%%

%{
    // Run each time yylex is called, to update the current token location
    yylloc->step();
%}

<*>\n {
    // Eat up newlines and update the current token position
    yylloc->lines();
    yylloc->step();
}

<*>{BLANK} {
    // Eat up whitespace and update the current token position
    yylloc->step();
}

{LEVEL_POLARITY} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    // Third character in matched text should be either C or D
    // for Clear and Dark
    if (YYText()[2] == 'C') {
        yylval->build(Gerber::LevelPolarityType::LEVEL_POLARITY_CLEAR);
    } else if (YYText()[2] == 'D') {
        yylval->build(Gerber::LevelPolarityType::LEVEL_POLARITY_DARK);
    }
    return yy::GerberRS274XParser::token::LEVEL_POLARITY;
}

X{INT_W_SIGN} {
    // Location skips 1st X
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Create a string with just the number by skipping the first character (X)
    std::string number(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stoi(number));
    return yy::GerberRS274XParser::token::X_COORDINATE;
}
				
Y{INT_W_SIGN} {
    // Location skips 1st Y
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Create a string with just the number by skipping the first character (Y)
    std::string number(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stoi(number));
    return yy::GerberRS274XParser::token::Y_COORDINATE;
}
				
I{INT_W_SIGN} {
    // Location skips 1st I
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Create a string with just the number by skipping the first character (I)
    std::string number(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stoi(number));
    return yy::GerberRS274XParser::token::I_OFFSET;
}
				
J{INT_W_SIGN} {
    // Location skips 1st J
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Create a string with just the number by skipping the first character (J)
    std::string number(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stoi(number));
    return yy::GerberRS274XParser::token::J_OFFSET;
}

{STEP_AND_REPEAT_START} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return_state = INITIAL;
    BEGIN(PARSING_STEP_AND_REPEAT);
    return yy::GerberRS274XParser::token::STEP_AND_REPEAT_START;
}

<PARSING_STEP_AND_REPEAT>X{INT_WO_SIGN} {
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Create a string with just the number by skipping the first character (X)
    std::string number(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stoi(number));
    return yy::GerberRS274XParser::token::X_REPEATS;
}

<PARSING_STEP_AND_REPEAT>Y{INT_WO_SIGN} {
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Create a string with just the number by skipping the first character (Y)
    std::string number(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stoi(number));
    return yy::GerberRS274XParser::token::Y_REPEATS;
}

<PARSING_STEP_AND_REPEAT>I{DECIMAL} {
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Build string with just decimal by skipping the 1st character (I)
    std::string decimal(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stod(decimal));
    return yy::GerberRS274XParser::token::X_STEP_DISTANCE;
}

<PARSING_STEP_AND_REPEAT>J{DECIMAL} {
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Build string with just decimal by skipping the 1st character (J)
    std::string decimal(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stod(decimal));
    return yy::GerberRS274XParser::token::Y_STEP_DISTANCE;
}
				
<*>{END_OF_DATA_BLOCK} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(return_state);
    return yy::GerberRS274XParser::token::END_OF_DATA_BLOCK;
}
					
<*>{EXT_CMD_DELIMITER} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    // An extended command delimiter always sets us back to the initial state
    BEGIN(INITIAL);
    return_state = INITIAL;
    return yy::GerberRS274XParser::token::EXT_CMD_DELIMITER;
}
					
{INTERPOLATE_CMD} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::D_CMD_TYPE_INTERPOLATE;
}

{MOVE_CMD} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::D_CMD_TYPE_MOVE;
}
					
{FLASH_CMD} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::D_CMD_TYPE_FLASH;
}
					
{APERTURE_NUMBER} {
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Build string with just decimal by skipping the 1st character (D)
    std::string aperture_id(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stoi(aperture_id));
    return yy::GerberRS274XParser::token::APERTURE_NUMBER;
}

{LINEAR_INTERP_MODE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::G_CMD_TYPE_LINEAR_INTERP_MODE;
}

{CW_CIRC_INTERP_MODE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::G_CMD_TYPE_CW_CIRC_INTERP_MODE;
}

{CCW_CIRC_INTERP_MODE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::G_CMD_TYPE_CCW_CIRC_INTERP_MODE;
}
						
{REGION_MODE_ON} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::G_CMD_TYPE_REGION_MODE_ON;
}

{REGION_MODE_OFF} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::G_CMD_TYPE_REGION_MODE_OFF;
}
						
{SINGLE_QUADRANT_MODE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::G_CMD_TYPE_SINGLE_QUADRANT_MODE;
}
						
{MULTI_QUADRANT_MODE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::G_CMD_TYPE_MULTI_QUADRANT_MODE;
}
						
{END_OF_FILE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::END_OF_FILE;
}
						
{COORD_FORMAT} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return_state = INITIAL;
    BEGIN(PARSING_COORD_FORMAT);
    return yy::GerberRS274XParser::token::COORD_FORMAT;
}

<PARSING_COORD_FORMAT>X {
    // Skip location over X
    yylloc->columns(1);
    yylloc->step();
    
    BEGIN(PARSING_COORD_FORMAT_NUM_INT_POSITIONS);
}

<PARSING_COORD_FORMAT_NUM_INT_POSITIONS>[[:digit:]] {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_COORD_FORMAT_NUM_DEC_POSITIONS);
    yylval->build(std::stoi(std::string(YYText(), YYLeng())));
    return yy::GerberRS274XParser::token::COORD_FORMAT_NUM_INT_POSITIONS;
}

<PARSING_COORD_FORMAT_NUM_DEC_POSITIONS>[[:digit:]] {
    UPDATE_LOCATION_COLS_STANDARD;
    
    yylval->build(std::stoi(std::string(YYText(), YYLeng())));
    return yy::GerberRS274XParser::token::COORD_FORMAT_NUM_DEC_POSITIONS;
}

<PARSING_COORD_FORMAT_NUM_DEC_POSITIONS>Y {
    // Skip location over Y
    yylloc->columns(1);
    yylloc->step();
    
    BEGIN(PARSING_COORD_FORMAT_NUM_INT_POSITIONS);
}
										
{UNIT_SPECIFIER} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    std::string unit_specifier(YYText(), YYLeng());
    
    if (unit_specifier.find("IN") != std::string::npos) {
        yylval->build(Gerber::UnitType::UNIT_TYPE_IN);
    } else {
        yylval->build(Gerber::UnitType::UNIT_TYPE_MM);
    }
    return yy::GerberRS274XParser::token::UNIT_SPECIFIER;
}
										
{COMMENT_START} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return_state = INITIAL;
    BEGIN(PARSING_COMMENT_STRING);
    return yy::GerberRS274XParser::token::COMMENT_START;
}
										
<PARSING_COMMENT_STRING>{COMMENT_STRING} {
    std::string comment(YYText(), YYLeng());
    
    // If the comment string contains any newlines, we need to account
    // for them in the token location
    int newline_count = 0;
    std::size_t current_search_pos = 0;
    std::size_t next_search_pos = comment.find("\n", current_search_pos);
    while (next_search_pos != std::string::npos) {
        ++newline_count;
        current_search_pos = next_search_pos + 1;
        next_search_pos = comment.find("\n", current_search_pos);
    }
    
    if (newline_count > 0) {
        yylloc->lines(newline_count);
        yylloc->columns(comment.length() - current_search_pos);
    } else {
        // If it's a single-line comment, then the token length is just the comment length
        yylloc->columns(comment.length());
    }
    
    yylval->build(comment);
    return yy::GerberRS274XParser::token::COMMENT_STRING;
}

{APERTURE_DEFINITION} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return_state = INITIAL;
    BEGIN(PARSING_APERTURE_NUMBER);
    return yy::GerberRS274XParser::token::APERTURE_DEFINITION;
}

<PARSING_APERTURE_NUMBER>{APERTURE_NUMBER} {
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    BEGIN(PARSING_APERTURE_TEMPLATE);
    // Create a string with just the number by skipping the first character (D)
    std::string aperture_id(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stoi(aperture_id));
    return yy::GerberRS274XParser::token::APERTURE_NUMBER;
}

<PARSING_APERTURE_TEMPLATE>C {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_MODIFIERS);
    return yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_CIRCLE;
}

<PARSING_APERTURE_TEMPLATE>R {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_MODIFIERS);
    return yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_RECTANGLE;
}

<PARSING_APERTURE_TEMPLATE>O {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_MODIFIERS);
    return yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_OBROUND;
}

<PARSING_APERTURE_TEMPLATE>P {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_MODIFIERS);
    return yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_POLYGON;
}


<PARSING_APERTURE_TEMPLATE>{NAME} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_MODIFIERS);
    std::string aperture_name(YYText(), YYLeng());
    yylval->build(aperture_name);
    return yy::GerberRS274XParser::token::CUSTOM_APERTURE_NAME;
}

<PARSING_APERTURE_MODIFIERS>[,X]{DECIMAL} {
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Build a string with just the decimal by skipping the 1st character (, or X)
    std::string decimal(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stod(decimal));
    return yy::GerberRS274XParser::token::APERTURE_DEFINITION_MODIFIER;
}

{APERTURE_MACRO} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return_state = PARSING_APERTURE_MACRO_CONTENT;
    BEGIN(PARSING_APERTURE_MACRO_NAME);
    return yy::GerberRS274XParser::token::APERTURE_MACRO;
}

<PARSING_APERTURE_MACRO_NAME>{NAME} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    std::string custom_aperture_name(YYText(), YYLeng());
    yylval->build(custom_aperture_name);
    return yy::GerberRS274XParser::token::CUSTOM_APERTURE_NAME;
}

<PARSING_APERTURE_MACRO_CONTENT>{VARIABLE_DEFINITION} {
    // Token location doesn't include 1st or last character
    yylloc->columns(1);
    yylloc->step();
    yylloc->columns(YYLeng() - 2);
    
    BEGIN(PARSING_ARITHMETIC_EXPRESSION);
    // Create string with just variable id by chopping off the first ($) and last (=) character of the string
    std::string var_id(&(YYText()[1]), YYLeng() - 2);
    
    yylval->build(std::stoi(var_id));
    return yy::GerberRS274XParser::token::VARIABLE_DEFINITION;
}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_COMMENT_START} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_COMMENT);
    return yy::GerberRS274XParser::token::APERTURE_COMMENT_START;
}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_CIRCLE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_PRIMITIVE);
    return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_CIRCLE;
}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_VECTOR_LINE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_PRIMITIVE);
    return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_VECTOR_LINE;
}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_CENTER_LINE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_PRIMITIVE);
    return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_CENTER_LINE;
}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_OUTLINE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_PRIMITIVE);
    return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_OUTLINE;
}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_POLYGON} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_PRIMITIVE);
    return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_POLYGON;
}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_MOIRE} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_PRIMITIVE);
    return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_MOIRE;
}

<PARSING_APERTURE_MACRO_CONTENT>{APERTURE_PRIMITIVE_THERMAL} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    BEGIN(PARSING_APERTURE_PRIMITIVE);
    return yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_THERMAL;
}

<PARSING_APERTURE_COMMENT>{COMMENT_STRING} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    std::string aperture_comment(YYText(), YYLeng());
    yylval->build(aperture_comment);
    return yy::GerberRS274XParser::token::APERTURE_COMMENT_CONTENT;
}

<PARSING_APERTURE_PRIMITIVE>{APERTURE_PRIMITIVE_MODIFIER_DELIMITER} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::AM_DELIM;
}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_ADD} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::ARITHMETIC_ADD;
}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_SUB} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::ARITHMETIC_SUB;
}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_MULT} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::ARITHMETIC_MULT;
}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_DIV} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::ARITHMETIC_DIV;
}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_LEFT_PAREN} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::ARITHMETIC_LEFT_PAREN;
}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_RIGHT_PAREN} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    return yy::GerberRS274XParser::token::ARITHMETIC_RIGHT_PAREN;
}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{ARITHMETIC_VAR_REFERENCE} {
    UPDATE_LOCATION_COLS_SKIP_FIRST_CHAR;
    
    // Build a string with just the variable id by skipping the first character ($)
    std::string var_id(&(YYText()[1]), YYLeng() - 1);
    yylval->build(std::stoi(var_id));
    return yy::GerberRS274XParser::token::ARITHMETIC_VAR_REFERENCE;
}

<PARSING_ARITHMETIC_EXPRESSION,PARSING_APERTURE_PRIMITIVE>{DECIMAL} {
    UPDATE_LOCATION_COLS_STANDARD;
    
    std::string decimal(YYText(), YYLeng());
    yylval->build(std::stod(decimal));
    return yy::GerberRS274XParser::token::ARITHMETIC_CONSTANT;
}

%%
