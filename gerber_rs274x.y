%code requires {
#include "gerber_scanner_defs.h"
#include "gerber_scanner.yy.h"
#include "gerber_parser_defs.h"

#include <stdio.h>
%}

%code {
void yyerror(YYLTYPE* yylocp, char const* s);
%}

%defines "gerber_parser.yy.h"
%output "gerber_parser.yy.c"
%define api.pure full
%language "C"
%locations

%union {
	UnitType unit_type;
	LevelPolarity level_polarity;
	int aperture_number;
	char* comment_string;
	char* custom_aperture_name;
	char* aperture_comment;
	int x_coordinate;
	int y_coordinate;
	int i_offset;
	int j_offset;
	int num_int_positions;
	int num_dec_positions;
	double aperture_definition_modifier;
	int variable_definition;
	double arithmetic_constant;
	int arithmetic_var_reference;
	int x_repeats;
	int y_repeats;
	double x_step_distance;
	double y_step_distance;
}

%destructor { free($$); } <comment_string>
%destructor { free($$); } <custom_aperture_name>
%destructor { free($$); } <aperture_comment>

%token D_CMD_TYPE_INTERPOLATE
%token D_CMD_TYPE_MOVE
%token D_CMD_TYPE_FLASH
%token G_CMD_TYPE_LINEAR_INTERP_MODE
%token G_CMD_TYPE_CW_CIRC_INTERP_MODE
%token G_CMD_TYPE_CCW_CIRC_INTERP_MODE
%token G_CMD_TYPE_SINGLE_QUADRANT_MODE
%token G_CMD_TYPE_MULTI_QUADRANT_MODE
%token G_CMD_TYPE_REGION_MODE_ON
%token G_CMD_TYPE_REGION_MODE_OFF
%token COMMENT_START
%token <comment_string> COMMENT_STRING
%token END_OF_FILE
%token <x_coordinate> X_COORDINATE
%token <y_coordinate> Y_COORDINATE
%token <i_offset> I_OFFSET
%token <j_offset> J_OFFSET
%token <x_repeats> X_REPEATS
%token <y_repeats> Y_REPEATS
%token <x_step_distance> X_STEP_DISTANCE
%token <y_step_distance> Y_STEP_DISTANCE
%token COORD_FORMAT
%token <num_int_positions> COORD_FORMAT_NUM_INT_POSITIONS
%token <num_dec_positions> COORD_FORMAT_NUM_DEC_POSITIONS
%token <unit_type> UNIT_SPECIFIER
%token END_OF_DATA_BLOCK
%token EXT_CMD_DELIMITER
%token <aperture_number> APERTURE_DEFINITION
%token STANDARD_APERTURE_TYPE_CIRCLE
%token STANDARD_APERTURE_TYPE_RECTANGLE
%token STANDARD_APERTURE_TYPE_OBROUND
%token STANDARD_APERTURE_TYPE_POLYGON
%token <custom_aperture_name> CUSTOM_APERTURE_NAME
%token <aperture_definition_modifier> APERTURE_DEFINITION_MODIFIER
%token APERTURE_MACRO
%token <variable_definition> VARIABLE_DEFINITION
%left ARITHMETIC_ADD ARITHMETIC_SUB
%left ARITHMETIC_MULT ARITHMETIC_DIV
%token ARITHMETIC_LEFT_PAREN
%token ARITHMETIC_RIGHT_PAREN
%token <arithmetic_constant> ARITHMETIC_CONSTANT
%token <arithmetic_var_reference> ARITHMETIC_VAR_REFERENCE
%token APERTURE_PRIMITIVE_TYPE_CIRCLE
%token APERTURE_PRIMITIVE_TYPE_VECTOR_LINE
%token APERTURE_PRIMITIVE_TYPE_CENTER_LINE
%token APERTURE_PRIMITIVE_TYPE_OUTLINE
%token APERTURE_PRIMITIVE_LINE_POLYGON
%token APERTURE_PRIMITIVE_TYPE_MOIRE
%token APERTURE_PRIMITIVE_TYPE_THERMAL
%token APERTURE_PRIMITIVE_MODIFIER_DELIMITER
%token APERTURE_COMMENT_START
%token <aperture_comment> APERTURE_COMMENT_CONTENT
%token STEP_AND_REPEAT_START
%token <level_polarity> LEVEL_POLARITY


%%

am_command:
	APERTURE_MACRO CUSTOM_APERTURE_NAME END_OF_DATA_BLOCK macro_content {
		$am_command = calloc(1, sizeof(ApertureMacro));
		$am_command->name = $CUSTOM_APERTUE_NAME;
		$am_command->content = $macro_content;
		/*
		$am_command->variable_defs_capacity = STARTING_NUM_VARIABLE_DEFS;
		$am_command->primitives_capacity = STARTING_NUM_PRIMITIVES;
		$am_command->variable_defs_length = 0;
		$am_command->primitives_length = 0;
		$am_command->variable_defs = calloc(STARTING_NUM_VARIABLE_DEFS, sizeof(VariableDefinition));
		$am_command->primitives = calloc(STARTING_NUM_PRIMITIVES, sizeof(MacroPrimitive));
		*/
		
	}

macro_content:
	

variable_definition:
	VARIABLE_DEFINITION arithmetic_expression END_OF_DATA_BLOCK {
		$variable_definition = calloc(1, sizeof(VariableDefinition));
		$variable_definition->variable_number = $VARIABLE_DEFINITION;
		$variable_definition->expression = $arithmetic_expression;
	}

arithmetic_expression[result]:
	ARITHMETIC_CONSTANT {
		$result = calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_CONSTANT;
		$result->element.constant = $ARITHMETIC_CONSTANT;
		$result->left = NULL;
		$result->right = NULL;
	}
|	ARITHMETIC_VAR_REFERENCE {
		$result = calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_VARIABLE;
		$result->element.variable = $ARITHMETIC_VAR_REFERENCE;
		$result->left = NULL;
		$result->right = NULL;
	}
|	arithmetic_expression[left] ARITHMETIC_ADD arithmetic_expression[right] {
		$result = calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_ADD;
		$result->left = $left;
		$result->right = $right;
	}
|	arithmetic_expression[left] ARITHMETIC_SUB arithmetic_expression[right] {
		$result = calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_SUB;
		$result->left = $left;
		$result->right = $right;
	}
|	arithmetic_expression[left] ARITHMETIC_MULT arithmetic_expression[right] {
		$result = calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_MULT;
		$result->left = $left;
		$result->right = $right;
	}
|	arithmetic_expression[left] ARITHMETIC_DIV arithmetic_expression[right] {
		$result = calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_DIV;
		$result->left = $left;
		$result->right = $right;
	}

%%

void yyerror(YYLTYPE* locp, char const* s)
{
	fprintf(stderr, "%s\n", s);
}