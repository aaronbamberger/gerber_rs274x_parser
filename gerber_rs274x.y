%code top {
	#include <stdio.h>
	#include <stdlib.h>
}

%code requires {
	#include "gerber_scanner_defs.h"
	#include "gerber_parser_defs.h"
	//#include "gerber_scanner.yy.h"
}

%code {
	void yyerror(YYLTYPE* yylocp, ApertureMacro** result, void* scanner, char const* s);
}

%defines "gerber_parser.yy.h"
%output "gerber_parser.yy.c"
%define api.pure full
%define parse.trace
%language "C"
%locations
%parse-param {ApertureMacro** result}
%param {void* scanner}

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
	ArithmeticExpressionTreeElement* arithmetic_expression_tree_element_t;
	VariableDefinition* variable_definition_t;
	MacroPrimitiveCircle* macro_primitive_circle_t;
	MacroPrimitiveVectorLine* macro_primitive_vector_line_t;
	MacroPrimitiveCenterLine* macro_primitive_center_line_t;
	ExpressionCoord* expression_coord_t;
	ExpressionCoordList* expression_coord_list_t;
	MacroPrimitiveOutline* macro_primitive_outline_t;
	MacroPrimitivePolygon* macro_primitive_polygon_t;
	MacroPrimitiveMoire* macro_primitive_moire_t;
	MacroPrimitiveThermal* macro_primitive_thermal_t;
	MacroPrimitive* macro_primitive_t;
	MacroContentElement* macro_content_element_t;
	MacroContentList* macro_content_list_t;
	ApertureMacro* aperture_macro_t;
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
%token APERTURE_DEFINITION
%token <aperture_number> APERTURE_NUMBER
%token STANDARD_APERTURE_TYPE_CIRCLE
%token STANDARD_APERTURE_TYPE_RECTANGLE
%token STANDARD_APERTURE_TYPE_OBROUND
%token STANDARD_APERTURE_TYPE_POLYGON
%token <custom_aperture_name> CUSTOM_APERTURE_NAME
%token <aperture_definition_modifier> APERTURE_DEFINITION_MODIFIER
%token APERTURE_MACRO
%token <variable_definition> VARIABLE_DEFINITION
%token ARITHMETIC_LEFT_PAREN
%token ARITHMETIC_RIGHT_PAREN
%token <arithmetic_constant> ARITHMETIC_CONSTANT
%token <arithmetic_var_reference> ARITHMETIC_VAR_REFERENCE
%token APERTURE_PRIMITIVE_TYPE_CIRCLE
%token APERTURE_PRIMITIVE_TYPE_VECTOR_LINE
%token APERTURE_PRIMITIVE_TYPE_CENTER_LINE
%token APERTURE_PRIMITIVE_TYPE_OUTLINE
%token APERTURE_PRIMITIVE_TYPE_POLYGON
%token APERTURE_PRIMITIVE_TYPE_MOIRE
%token APERTURE_PRIMITIVE_TYPE_THERMAL
%token AM_DELIM
%token APERTURE_COMMENT_START
%token <aperture_comment> APERTURE_COMMENT_CONTENT
%token STEP_AND_REPEAT_START
%token <level_polarity> LEVEL_POLARITY

%left ARITHMETIC_ADD ARITHMETIC_SUB
%left ARITHMETIC_MULT ARITHMETIC_DIV
%precedence UNARY_MINUS

%type <aperture_macro_t> am_command
%type <macro_content_list_t> macro_content_list
%type <macro_content_element_t> macro_content_element
%type <macro_primitive_t> macro_primitive
%type <aperture_comment> macro_primitive_comment
%type <macro_primitive_circle_t> macro_primitive_circle
%type <macro_primitive_vector_line_t> macro_primitive_vector_line
%type <macro_primitive_center_line_t> macro_primitive_center_line
%type <expression_coord_t> expression_coord
%type <expression_coord_list_t> expression_coord_list
%type <macro_primitive_outline_t> macro_primitive_outline
%type <macro_primitive_polygon_t> macro_primitive_polygon
%type <macro_primitive_moire_t> macro_primitive_moire
%type <macro_primitive_thermal_t> macro_primitive_thermal
%type <arithmetic_expression_tree_element_t> arithmetic_expression
%type <variable_definition_t> variable_definition

%%

top_level:
	am_command {
		*result = $[am_command];
	}

am_command:
	EXT_CMD_DELIMITER APERTURE_MACRO CUSTOM_APERTURE_NAME END_OF_DATA_BLOCK macro_content_list EXT_CMD_DELIMITER {
		$am_command = calloc(1, sizeof(ApertureMacro));
		$am_command->name = $CUSTOM_APERTURE_NAME;
		$am_command->content_list = $macro_content_list;
	}

macro_content_list[result]:
	macro_content_list[list] macro_content_element[new_elem] {
		$list->tail->next = $[new_elem];
		$list->tail = $[new_elem];
		$result = $list;
	}
|	macro_content_element[new_elem] {
		$result = calloc(1, sizeof(MacroContentList));
		$result->head = $[new_elem];
		$result->tail = $[new_elem];
	}

macro_content_element:
	variable_definition {
		$macro_content_element = calloc(1, sizeof(MacroContentElement));
		$macro_content_element->next = NULL;
		$macro_content_element->type = MACRO_CONTENT_VAR_DEF;
		$macro_content_element->content.var_def = $[variable_definition];
	}
|	macro_primitive {
		$macro_content_element = calloc(1, sizeof(MacroContentElement));
		$macro_content_element->next = NULL;
		$macro_content_element->type = MACRO_CONTENT_PRIMITIVE;
		$macro_content_element->content.primitive = $[macro_primitive];
	}

macro_primitive:
	macro_primitive_comment END_OF_DATA_BLOCK {
		$macro_primitive = calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_COMMENT;
		$macro_primitive->primitive.comment = $macro_primitive_comment;
	}
|	macro_primitive_circle END_OF_DATA_BLOCK {
		$macro_primitive = calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_CIRCLE;
		$macro_primitive->primitive.circle = $macro_primitive_circle;
	}
|	macro_primitive_vector_line END_OF_DATA_BLOCK {
		$macro_primitive = calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_VECTOR_LINE;
		$macro_primitive->primitive.vector_line = $macro_primitive_vector_line;
	}
|	macro_primitive_center_line END_OF_DATA_BLOCK {
		$macro_primitive = calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_CENTER_LINE;
		$macro_primitive->primitive.center_line = $macro_primitive_center_line;
	}
|	macro_primitive_outline END_OF_DATA_BLOCK {
		$macro_primitive = calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_OUTLINE;
		$macro_primitive->primitive.outline = $macro_primitive_outline;
	}
|	macro_primitive_polygon END_OF_DATA_BLOCK {
		$macro_primitive = calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_POLYGON;
		$macro_primitive->primitive.polygon = $macro_primitive_polygon;
	}
|	macro_primitive_moire END_OF_DATA_BLOCK {
		$macro_primitive = calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_MOIRE;
		$macro_primitive->primitive.moire = $macro_primitive_moire;
	}
|	macro_primitive_thermal END_OF_DATA_BLOCK {
		$macro_primitive = calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_THERMAL;
		$macro_primitive->primitive.thermal = $macro_primitive_thermal;
	}

macro_primitive_comment:
	APERTURE_COMMENT_START APERTURE_COMMENT_CONTENT {
		$macro_primitive_comment = $APERTURE_COMMENT_CONTENT;
	}

macro_primitive_circle:
	APERTURE_PRIMITIVE_TYPE_CIRCLE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[diameter] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_circle = calloc(1, sizeof(MacroPrimitiveCircle));
		$macro_primitive_circle->exposure = $exposure;
		$macro_primitive_circle->diameter = $diameter;
		$macro_primitive_circle->center_x = $[center_x];
		$macro_primitive_circle->center_y = $[center_y];
		$macro_primitive_circle->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_CIRCLE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[diameter] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] {
		$macro_primitive_circle = calloc(1, sizeof(MacroPrimitiveCircle));
		$macro_primitive_circle->exposure = $exposure;
		$macro_primitive_circle->diameter = $diameter;
		$macro_primitive_circle->center_x = $[center_x];
		$macro_primitive_circle->center_y = $[center_y];
		$macro_primitive_circle->rotation = NULL;
	}

macro_primitive_vector_line:
	APERTURE_PRIMITIVE_TYPE_VECTOR_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[line_width] AM_DELIM arithmetic_expression[start_x] AM_DELIM arithmetic_expression[start_y] AM_DELIM arithmetic_expression[end_x] AM_DELIM arithmetic_expression[end_y] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_vector_line = calloc(1, sizeof(MacroPrimitiveVectorLine));
		$macro_primitive_vector_line->exposure = $exposure;
		$macro_primitive_vector_line->line_width = $[line_width];
		$macro_primitive_vector_line->start_x = $[start_x];
		$macro_primitive_vector_line->start_y = $[start_y];
		$macro_primitive_vector_line->end_x = $[end_x];
		$macro_primitive_vector_line->end_y = $[end_y];
		$macro_primitive_vector_line->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_VECTOR_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[line_width] AM_DELIM arithmetic_expression[start_x] AM_DELIM arithmetic_expression[start_y] AM_DELIM arithmetic_expression[end_x] AM_DELIM arithmetic_expression[end_y] {
		$macro_primitive_vector_line = calloc(1, sizeof(MacroPrimitiveVectorLine));
		$macro_primitive_vector_line->exposure = $exposure;
		$macro_primitive_vector_line->line_width = $[line_width];
		$macro_primitive_vector_line->start_x = $[start_x];
		$macro_primitive_vector_line->start_y = $[start_y];
		$macro_primitive_vector_line->end_x = $[end_x];
		$macro_primitive_vector_line->end_y = $[end_y];
		$macro_primitive_vector_line->rotation = NULL;
	}

macro_primitive_center_line:
	APERTURE_PRIMITIVE_TYPE_CENTER_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[rect_width] AM_DELIM arithmetic_expression[rect_height] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_center_line = calloc(1, sizeof(MacroPrimitiveCenterLine));
		$macro_primitive_center_line->exposure = $exposure;
		$macro_primitive_center_line->rect_width = $[rect_width];
		$macro_primitive_center_line->rect_height = $[rect_height];
		$macro_primitive_center_line->center_x = $[center_x];
		$macro_primitive_center_line->center_y = $[center_y];
		$macro_primitive_center_line->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_CENTER_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[rect_width] AM_DELIM arithmetic_expression[rect_height] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] {
		$macro_primitive_center_line = calloc(1, sizeof(MacroPrimitiveCenterLine));
		$macro_primitive_center_line->exposure = $exposure;
		$macro_primitive_center_line->rect_width = $[rect_width];
		$macro_primitive_center_line->rect_height = $[rect_height];
		$macro_primitive_center_line->center_x = $[center_x];
		$macro_primitive_center_line->center_y = $[center_y];
		$macro_primitive_center_line->rotation = NULL;
	}

macro_primitive_outline:
	APERTURE_PRIMITIVE_TYPE_OUTLINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_points] expression_coord_list[coords] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_outline = calloc(1, sizeof(MacroPrimitiveOutline));
		$macro_primitive_outline->exposure = $exposure;
		$macro_primitive_outline->num_points = $[num_points];
		$macro_primitive_outline->coords = $coords;
		$macro_primitive_outline->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_OUTLINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_points] expression_coord_list[coords] {
		$macro_primitive_outline = calloc(1, sizeof(MacroPrimitiveOutline));
		$macro_primitive_outline->exposure = $exposure;
		$macro_primitive_outline->num_points = $[num_points];
		$macro_primitive_outline->coords = $coords;
		$macro_primitive_outline->rotation = NULL;
	}

macro_primitive_polygon:
	APERTURE_PRIMITIVE_TYPE_POLYGON AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_vertices] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[diameter] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_polygon = calloc(1, sizeof(MacroPrimitivePolygon));
		$macro_primitive_polygon->exposure = $exposure;
		$macro_primitive_polygon->num_vertices = $[num_vertices];
		$macro_primitive_polygon->center_x = $[center_x];
		$macro_primitive_polygon->center_y = $[center_y];
		$macro_primitive_polygon->diameter = $diameter;
		$macro_primitive_polygon->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_POLYGON AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_vertices] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[diameter] {
		$macro_primitive_polygon = calloc(1, sizeof(MacroPrimitivePolygon));
		$macro_primitive_polygon->exposure = $exposure;
		$macro_primitive_polygon->num_vertices = $[num_vertices];
		$macro_primitive_polygon->center_x = $[center_x];
		$macro_primitive_polygon->center_y = $[center_y];
		$macro_primitive_polygon->diameter = $diameter;
		$macro_primitive_polygon->rotation = NULL;
	}

macro_primitive_moire:
	APERTURE_PRIMITIVE_TYPE_MOIRE AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[ring_thickness] AM_DELIM arithmetic_expression[ring_gap] AM_DELIM arithmetic_expression[max_rings] AM_DELIM arithmetic_expression[crosshair_thickness] AM_DELIM arithmetic_expression[crosshair_length] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_moire = calloc(1, sizeof(MacroPrimitiveMoire));
		$macro_primitive_moire->center_x = $[center_x];
		$macro_primitive_moire->center_y = $[center_y];
		$macro_primitive_moire->outer_diameter = $[outer_diameter];
		$macro_primitive_moire->ring_thickness = $[ring_thickness];
		$macro_primitive_moire->ring_gap = $[ring_gap];
		$macro_primitive_moire->max_rings = $[max_rings];
		$macro_primitive_moire->crosshair_thickness = $[crosshair_thickness];
		$macro_primitive_moire->crosshair_length = $[crosshair_length];
		$macro_primitive_moire->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_MOIRE AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[ring_thickness] AM_DELIM arithmetic_expression[ring_gap] AM_DELIM arithmetic_expression[max_rings] AM_DELIM arithmetic_expression[crosshair_thickness] AM_DELIM arithmetic_expression[crosshair_length] {
		$macro_primitive_moire = calloc(1, sizeof(MacroPrimitiveMoire));
		$macro_primitive_moire->center_x = $[center_x];
		$macro_primitive_moire->center_y = $[center_y];
		$macro_primitive_moire->outer_diameter = $[outer_diameter];
		$macro_primitive_moire->ring_thickness = $[ring_thickness];
		$macro_primitive_moire->ring_gap = $[ring_gap];
		$macro_primitive_moire->max_rings = $[max_rings];
		$macro_primitive_moire->crosshair_thickness = $[crosshair_thickness];
		$macro_primitive_moire->crosshair_length = $[crosshair_length];
		$macro_primitive_moire->rotation = NULL;
	}

macro_primitive_thermal:
	APERTURE_PRIMITIVE_TYPE_THERMAL AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[inner_diameter] AM_DELIM arithmetic_expression[gap_thickness] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_thermal = calloc(1, sizeof(MacroPrimitiveThermal));
		$macro_primitive_thermal->center_x = $[center_x];
		$macro_primitive_thermal->center_y = $[center_y];
		$macro_primitive_thermal->outer_diameter = $[outer_diameter];
		$macro_primitive_thermal->inner_diameter = $[inner_diameter];
		$macro_primitive_thermal->gap_thickness = $[gap_thickness];
		$macro_primitive_thermal->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_THERMAL AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[inner_diameter] AM_DELIM arithmetic_expression[gap_thickness] {
		$macro_primitive_thermal = calloc(1, sizeof(MacroPrimitiveThermal));
		$macro_primitive_thermal->center_x = $[center_x];
		$macro_primitive_thermal->center_y = $[center_y];
		$macro_primitive_thermal->outer_diameter = $[outer_diameter];
		$macro_primitive_thermal->inner_diameter = $[inner_diameter];
		$macro_primitive_thermal->gap_thickness = $[gap_thickness];
		$macro_primitive_thermal->rotation = NULL;
	}

expression_coord_list[result]:
	expression_coord_list[list] expression_coord[new_elem] {
		$list->tail->next = $[new_elem];
		$list->tail = $[new_elem];
		$result = $list;
	}
|	expression_coord[new_elem] {
		$result = calloc(1, sizeof(ExpressionCoordList));
		$result->head = $[new_elem];
		$result->tail = $[new_elem];
	}

expression_coord:
	AM_DELIM arithmetic_expression[coord_x] AM_DELIM arithmetic_expression[coord_y] {
		$expression_coord = calloc(1, sizeof(ExpressionCoord));
		$expression_coord->coord_x = $[coord_x];
		$expression_coord->coord_y = $[coord_y];
		$expression_coord->next = NULL;
	}

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
|	ARITHMETIC_SUB arithmetic_expression[right] %prec UNARY_MINUS {
		$result = calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_SUB;
		$result->left = calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->left->type = EXPRESSION_ELEMENT_TYPE_CONSTANT;
		$result->left->element.constant = 0.0;
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
|	ARITHMETIC_LEFT_PAREN arithmetic_expression[mid] ARITHMETIC_RIGHT_PAREN {
		$result = $mid;
	}

%%

void yyerror(YYLTYPE* locp, ApertureMacro** result, void* scanner, char const* s)
{
	fprintf(stderr, "%s\n", s);
}