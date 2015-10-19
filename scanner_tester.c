#include "gerber_scanner_defs.h"
#include "gerber_parser_defs.h"
#include "gerber_scanner.yy.h"
#include "gerber_parser.yy.h"

#include <stdio.h>
#include <stdbool.h>

void pretty_print_token(int token_type, YYSTYPE* semantic_value);
void pretty_print_arithmetic_expression_tree(ArithmeticExpressionTreeElement* root, int level);
void pretty_print_aperture_macro(ApertureMacro* macro);
void pretty_print_circle_primitive(MacroPrimitiveCircle* circle);
void pretty_print_vector_line_primitive(MacroPrimitiveVectorLine* vector_line);
void pretty_print_center_line_primitive(MacroPrimitiveCenterLine* center_line);
void pretty_print_outline_primitive(MacroPrimitiveOutline* outline);
void pretty_print_polygon_primitive(MacroPrimitivePolygon* polygon);
void pretty_print_moire_primitive(MacroPrimitiveMoire* moire);
void pretty_print_thermal_primitive(MacroPrimitiveThermal* thermal);
void pretty_print_expression_coord_list(ExpressionCoordList* coord_list);
void pretty_print_arithmetic_expression(ArithmeticExpressionTreeElement* root);

int main(int argc, char** argv)
{
	if (argc != 2) {
		printf("Usage: scanner_tester <gerber_file>\n");
		return 1;
	}
	
	FILE* gerber_file = fopen(argv[1], "r");
	if (gerber_file == NULL) {
		printf("Error opening file %s\n", argv[1]);
		return 2;
	}
	
	yyscan_t scanner;
	yylex_init(&scanner);
	
	yyset_in(gerber_file, scanner);
	
	/*
	YYSTYPE semantic_value;
	YYLTYPE location;
	
	bool done = false;
	
	while (!done) {
		int token_type = yylex(&semantic_value, &location, scanner);
		if (token_type == 0) {
			done = true;
		} else {
			pretty_print_token(token_type, &semantic_value);
		}
	}void pretty_print_center_line_primitive(MacroPrimitiveCenterLine* center_line)
	*/

	yydebug = 1;
	ApertureMacro* result;
	int parse_result = yyparse(&result, scanner);
	printf("Parser returned result %d\n", parse_result);

	printf("Parsed Macro Primitive:\n");
	pretty_print_aperture_macro(result);
	
	yylex_destroy(scanner);
	fclose(gerber_file);
	
	return 0;
}

void pretty_print_aperture_macro(ApertureMacro* macro)
{
	printf("Macro Name: %s\n", macro->name);
	MacroContentElement* content_element;
	for(content_element = macro->content_list->head; content_element != NULL; content_element = content_element->next) {
		const char* element_type = "none";
		switch (content_element->type) {
			case MACRO_CONTENT_VAR_DEF:
				element_type = "Variable Definition";
				break;

			case MACRO_CONTENT_PRIMITIVE:
				element_type = "Primitive";
				break;
		}
		printf("---Macro content element, type: %s---\n", element_type);

		switch (content_element->type) {
			case MACRO_CONTENT_VAR_DEF:
				printf("Variable number: %d\n", content_element->content.var_def->variable_number);
				printf("Expression:\n");
				pretty_print_arithmetic_expression(content_element->content.var_def->expression);
				break;

			case MACRO_CONTENT_PRIMITIVE:
				switch (content_element->content.primitive->type) {
					case MACRO_PRIMITIVE_TYPE_CIRCLE:
						pretty_print_circle_primitive(content_element->content.primitive->primitive.circle);
						break;

					case MACRO_PRIMITIVE_TYPE_VECTOR_LINE:
						pretty_print_vector_line_primitive(content_element->content.primitive->primitive.vector_line);
						break;

					case MACRO_PRIMITIVE_TYPE_CENTER_LINE:
						pretty_print_center_line_primitive(content_element->content.primitive->primitive.center_line);
						break;

					case MACRO_PRIMITIVE_TYPE_OUTLINE:
						pretty_print_outline_primitive(content_element->content.primitive->primitive.outline);
						break;

					case MACRO_PRIMITIVE_TYPE_POLYGON:
						pretty_print_polygon_primitive(content_element->content.primitive->primitive.polygon);
						break;

					case MACRO_PRIMITIVE_TYPE_MOIRE:
						pretty_print_moire_primitive(content_element->content.primitive->primitive.moire);
						break;

					case MACRO_PRIMITIVE_TYPE_THERMAL:
						pretty_print_thermal_primitive(content_element->content.primitive->primitive.thermal);
						break;

					case MACRO_PRIMITIVE_TYPE_COMMENT:
						printf("Macro primitive: Comment\n");
						printf("Contents: %s\n", content_element->content.primitive->primitive.comment);
						break;
				}
				break;
		}
	}
}

void pretty_print_circle_primitive(MacroPrimitiveCircle* circle)
{
	printf("Macro primitive: Circle\n");
	printf("Exposure:\n");
	pretty_print_arithmetic_expression(circle->exposure);
	printf("Diameter:\n");
	pretty_print_arithmetic_expression(circle->diameter);
	printf("Center X:\n");
	pretty_print_arithmetic_expression(circle->center_x);
	printf("Center Y:\n");
	pretty_print_arithmetic_expression(circle->center_y);
	printf("Rotation:\n");
	if (circle->rotation != NULL) {
		pretty_print_arithmetic_expression(circle->rotation);
	} else {
		printf("None\n");
	}
}

void pretty_print_vector_line_primitive(MacroPrimitiveVectorLine* vector_line)
{
	printf("Macro primitive: Vector Line\n");
	printf("Exposure:\n");
	pretty_print_arithmetic_expression(vector_line->exposure);
	printf("Line width:\n");
	pretty_print_arithmetic_expression(vector_line->line_width);
	printf("Start X:\n");
	pretty_print_arithmetic_expression(vector_line->start_x);
	printf("Start Y:\n");
	pretty_print_arithmetic_expression(vector_line->start_y);
	printf("End X:\n");
	pretty_print_arithmetic_expression(vector_line->end_x);
	printf("End Y:\n");
	pretty_print_arithmetic_expression(vector_line->end_y);
	printf("Rotation:\n");
	if (vector_line->rotation != NULL) {
		pretty_print_arithmetic_expression(vector_line->rotation);
	} else {
		printf("None\n");
	}
}

void pretty_print_center_line_primitive(MacroPrimitiveCenterLine* center_line)
{
	printf("Macro primitive: Center Line\n");
	printf("Exposure:\n");
	pretty_print_arithmetic_expression(center_line->exposure);
	printf("Rect width:\n");
	pretty_print_arithmetic_expression(center_line->rect_width);
	printf("Rect height:\n");
	pretty_print_arithmetic_expression(center_line->rect_height);
	printf("Center X:\n");
	pretty_print_arithmetic_expression(center_line->center_x);
	printf("Center Y:\n");
	pretty_print_arithmetic_expression(center_line->center_y);
	printf("Rotation:\n");
	if (center_line->rotation != NULL) {
		pretty_print_arithmetic_expression(center_line->rotation);
	} else {
		printf("None\n");
	}
}

void pretty_print_outline_primitive(MacroPrimitiveOutline* outline)
{
	printf("Macro primitive: Outline\n");
	printf("Exposure:\n");
	pretty_print_arithmetic_expression(outline->exposure);
	printf("Num points:\n");
	pretty_print_arithmetic_expression(outline->num_points);
	printf("Points:\n");
	pretty_print_expression_coord_list(outline->coords);
	printf("Rotation:\n");
	if (outline->rotation != NULL) {
		pretty_print_arithmetic_expression(outline->rotation);
	} else {
		printf("None\n");
	}
}

void pretty_print_polygon_primitive(MacroPrimitivePolygon* polygon)
{
	printf("Macro primitive: Polygon\n");
	printf("Exposure:\n");
	pretty_print_arithmetic_expression(polygon->exposure);
	printf("Num vertices:\n");
	pretty_print_arithmetic_expression(polygon->num_vertices);
	printf("Center X:\n");
	pretty_print_arithmetic_expression(polygon->center_x);
	printf("Center Y:\n");
	pretty_print_arithmetic_expression(polygon->center_y);
	printf("Diameter:\n");
	pretty_print_arithmetic_expression(polygon->diameter);
	printf("Rotation:\n");
	if (polygon->rotation != NULL) {
		pretty_print_arithmetic_expression(polygon->rotation);
	} else {
		printf("None\n");
	}
}

void pretty_print_moire_primitive(MacroPrimitiveMoire* moire)
{
	printf("Macro primitive: Moire\n");
	printf("Center X:\n");
	pretty_print_arithmetic_expression(moire->center_x);
	printf("Center Y:\n");
	pretty_print_arithmetic_expression(moire->center_y);
	printf("Outer diameter:\n");
	pretty_print_arithmetic_expression(moire->outer_diameter);
	printf("Ring thickness:\n");
	pretty_print_arithmetic_expression(moire->ring_thickness);
	printf("Ring gap:\n");
	pretty_print_arithmetic_expression(moire->ring_gap);
	printf("Max rings\n");
	pretty_print_arithmetic_expression(moire->max_rings);
	printf("Crosshair thickness:\n");
	pretty_print_arithmetic_expression(moire->crosshair_thickness);
	printf("Crosshair length:\n");
	pretty_print_arithmetic_expression(moire->crosshair_length);
	printf("Rotation:\n");
	if (moire->rotation != NULL) {
		pretty_print_arithmetic_expression(moire->rotation);
	} else {
		printf("None\n");
	}
}

void pretty_print_thermal_primitive(MacroPrimitiveThermal* thermal)
{
	printf("Macro primitive: Thermal\n");
	printf("Center X:\n");
	pretty_print_arithmetic_expression(thermal->center_x);
	printf("Center Y:\n");
	pretty_print_arithmetic_expression(thermal->center_y);
	printf("Outer diameter:\n");
	pretty_print_arithmetic_expression(thermal->outer_diameter);
	printf("Inner diameter:\n");
	pretty_print_arithmetic_expression(thermal->inner_diameter);
	printf("Gap thickness:\n");
	pretty_print_arithmetic_expression(thermal->gap_thickness);
	printf("Rotation:\n");
	if (thermal->rotation != NULL) {
		pretty_print_arithmetic_expression(thermal->rotation);
	} else {
		printf("None\n");
	}
}

void pretty_print_expression_coord_list(ExpressionCoordList* coord_list)
{
	ExpressionCoord* coord;
	int point_num = 1;
	for (coord = coord_list->head; coord != NULL; coord = coord->next) {
		printf("Point %d\n", point_num);
		printf("X:\n");
		pretty_print_arithmetic_expression(coord->coord_x);
		printf("Y:\n");
		pretty_print_arithmetic_expression(coord->coord_y);
		point_num++;
	}
}

void pretty_print_arithmetic_expression(ArithmeticExpressionTreeElement* root)
{
	pretty_print_arithmetic_expression_tree(root, 1);
}

void pretty_print_arithmetic_expression_tree(ArithmeticExpressionTreeElement* root, int level)
{
	// Print the root at the current level
	switch (root->type) {
		case EXPRESSION_ELEMENT_TYPE_CONSTANT:
			printf("Constant: %f\n", root->element.constant);
			break;

		case EXPRESSION_ELEMENT_TYPE_VARIABLE:
			printf("Variable: %d\n", root->element.variable);
			break;

		case EXPRESSION_ELEMENT_TYPE_OPERATOR:
			printf("Operator: ");
			switch (root->element.op) {
				case OPERATOR_ADD:
					printf("+\n");
					break;

				case OPERATOR_SUB:
					printf("-\n");
					break;

				case OPERATOR_MULT:
					printf("*\n");
					break;

				case OPERATOR_DIV:
					printf("/\n");
					break;
			}
			break;
	}

	// For each child, if it exists, generate the proper amount of indentation, then
	// recursively print the child
	if (root->left != NULL) {
		int i;
		for (i = 0; i < (level * 2); i++) {
			printf(" ");
		}
		pretty_print_arithmetic_expression_tree(root->left, level + 1);
	}

	if (root->right != NULL) {
		int i;
		for (i = 0; i < (level * 2); i++) {
			printf(" ");
		}
		pretty_print_arithmetic_expression_tree(root->right, level + 1);
	}
}

void pretty_print_token(int token_type, YYSTYPE* semantic_value)
{
	switch (token_type) {
		case D_CMD_TYPE_INTERPOLATE:
			printf("D Command: Interpolate\n");
			break;

		case D_CMD_TYPE_MOVE:
			printf("D Command: Move\n");
			break;

		case D_CMD_TYPE_FLASH:
			printf("D Command: Flash\n");
			break;

		case G_CMD_TYPE_LINEAR_INTERP_MODE:
			printf("G Command: Linear Interpolation Mode\n");
			break;

		case G_CMD_TYPE_CW_CIRC_INTERP_MODE:
			printf("G Command: Clockwise Circular Interpolation Mode\n");
			break;

		case G_CMD_TYPE_CCW_CIRC_INTERP_MODE:
			printf("G Command: Counter-Clockwise Circular Interpolation Mode\n");
			break;

		case G_CMD_TYPE_SINGLE_QUADRANT_MODE:
			printf("G Command: Single-Quadrant Mode\n");
			break;

		case G_CMD_TYPE_MULTI_QUADRANT_MODE:
			printf("G Command: Multi-Quadrant Mode\n");
			break;

		case G_CMD_TYPE_REGION_MODE_ON:
			printf("G Command: Region Mode On\n");
			break;

		case G_CMD_TYPE_REGION_MODE_OFF:
			printf("G Command: Region Mode Off\n");
			break;
			
		case APERTURE_NUMBER:
			printf("Aperture Number %d\n", semantic_value->aperture_number);
			break;
			
		case COMMENT_START:
			printf("Comment Start\n");
			break;
		
		case COMMENT_STRING:
			printf("Comment Content: %s\n", semantic_value->comment_string);
			free(semantic_value->comment_string);
			break;
			
		case END_OF_FILE:
			printf("End of file\n");
			break;
			
		case X_COORDINATE:
			printf("X Coordinate: %d\n", semantic_value->x_coordinate);
			break;
			
		case Y_COORDINATE:
			printf("Y Coordinate: %d\n", semantic_value->y_coordinate);
			break;
			
		case I_OFFSET:
			printf("I Offset: %d\n", semantic_value->i_offset);
			break;
			
		case J_OFFSET:
			printf("J Offset: %d\n", semantic_value->j_offset);
			break;
			
		case COORD_FORMAT:
			printf("Coordinate Format\n");
			break;
			
		case COORD_FORMAT_NUM_INT_POSITIONS:
			printf("Coordinate Format Number of Integer Positions: %d\n", semantic_value->num_int_positions);
			break;
			
		case COORD_FORMAT_NUM_DEC_POSITIONS:
			printf("Coordinate Format Number of Decimal Positions: %d\n", semantic_value->num_dec_positions);			
			break;
			
		case UNIT_SPECIFIER:
			printf("Units: ");
			if (semantic_value->unit_type == UNIT_TYPE_IN) {
				printf("Inches\n");
			} else {
				printf("Millimeters\n");
			}
			break;
			
		case END_OF_DATA_BLOCK:
			printf("End of Data Block\n");		
			break;
			
		case EXT_CMD_DELIMITER:
			printf("Extended Command Delimiter\n");
			break;

		case APERTURE_DEFINITION:
			printf("Aperture Definition\n");
			break;

		case STANDARD_APERTURE_TYPE_CIRCLE:
			printf("Standard Aperture: Circle\n");
			break;

		case STANDARD_APERTURE_TYPE_RECTANGLE:
			printf("Standard Aperture: Rectangle\n");
			break;

		case STANDARD_APERTURE_TYPE_OBROUND:
			printf("Standard Aperture: Obround\n");
			break;

		case STANDARD_APERTURE_TYPE_POLYGON:
			printf("Standard Aperture: Polygon\n");
			break;

		case CUSTOM_APERTURE_NAME:
			printf("Custom Aperture Name: %s\n", semantic_value->custom_aperture_name);
			free(semantic_value->custom_aperture_name);
			break;

		case APERTURE_DEFINITION_MODIFIER:
			printf("Aperture Definition Modifier: %f\n", semantic_value->aperture_definition_modifier);
			break;

		case APERTURE_MACRO:
			printf("Aperture Macro\n");
			break;

		case VARIABLE_DEFINITION:
			printf("Variable Definition: $%d\n", semantic_value->variable_definition);
			break;

		case ARITHMETIC_ADD:
			printf("Arithmetic Operator: +\n");
			break;

		case ARITHMETIC_SUB:
			printf("Arithmetic Operator: -\n");
			break;

		case ARITHMETIC_MULT:
			printf("Arithmetic Operator: *\n");
			break;

		case ARITHMETIC_DIV:
			printf("Arithmetic Operator: /\n");
			break;

		case ARITHMETIC_LEFT_PAREN:
			printf("Arithmetic Operator: (\n");
			break;

		case ARITHMETIC_RIGHT_PAREN:
			printf("Arithmetic Operator: )\n");
			break;

		case ARITHMETIC_CONSTANT:
			printf("Arithmetic Constant: %f\n", semantic_value->arithmetic_constant);
			break;

		case ARITHMETIC_VAR_REFERENCE:
			printf("Arithmetic Variable Reference: $%d\n", semantic_value->arithmetic_var_reference);
			break;

		case APERTURE_PRIMITIVE_TYPE_CIRCLE:
			printf("Aperture Primitive: Circle\n");
			break;

		case APERTURE_PRIMITIVE_TYPE_VECTOR_LINE:
			printf("Aperture Primitive: Vector Line\n");
			break;

		case APERTURE_PRIMITIVE_TYPE_CENTER_LINE:
			printf("Aperture Primitive: Center Line\n");
			break;

		case APERTURE_PRIMITIVE_TYPE_OUTLINE:
			printf("Aperture Primitive: Outline\n");
			break;

		case APERTURE_PRIMITIVE_TYPE_POLYGON:
			printf("Aperture Primitive: Polygon\n");
			break;

		case APERTURE_PRIMITIVE_TYPE_MOIRE:
			printf("Aperture Primitive: Moire\n");
			break;

		case APERTURE_PRIMITIVE_TYPE_THERMAL:
			printf("Aperture Primitive: Thermal\n");
			break;

		case AM_DELIM:
			printf("Aperture Primitive Modifier Delimiter\n");
			break;

		case APERTURE_COMMENT_START:
			printf("Aperture Comment Start\n");
			break;

		case APERTURE_COMMENT_CONTENT:
			printf("Aperture Comment: %s\n", semantic_value->aperture_comment);
			free(semantic_value->aperture_comment);
			break;

		case STEP_AND_REPEAT_START:
			printf("Step and Repeat\n");
			break;

		case X_REPEATS:
			printf("X Repeats: %d\n", semantic_value->x_repeats);
			break;

		case Y_REPEATS:
			printf("Y Repeats: %d\n", semantic_value->y_repeats);
			break;

		case X_STEP_DISTANCE:
			printf("X Step Distance: %f\n", semantic_value->x_step_distance);
			break;

		case Y_STEP_DISTANCE:
			printf("Y Step Distance: %f\n", semantic_value->y_step_distance);
			break;

		case LEVEL_POLARITY:
			switch (semantic_value->level_polarity) {
				case LEVEL_POLARITY_CLEAR:
					printf("Level Polarity Clear\n");
					break;

				case LEVEL_POLARITY_DARK:
					printf("Level Polarity Dark\n");
					break;
			}
			break;
	}
}
