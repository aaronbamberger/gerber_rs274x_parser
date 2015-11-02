
#include "gerber_rs274x_scanner.hh"
#include "gerber_parser_defs.h"
#include "gerber_parser.yy.hh"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <iostream>
#include <fstream>
#include <ios>
#include <memory>

/*
void pretty_print_token(int token_type, yy::GerberRS274XParser::semantic_type& semantic_value);
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
void pretty_print_command(Command* command);
void pretty_print_d_command(DCommand* d_command);
void pretty_print_coordinate_data(CoordinateData* coord_data);
void pretty_print_g_command(GCodeType g_code);
void pretty_print_format_specifier(FormatSpecifier* format_specifier);
void pretty_print_step_and_repeat(StepAndRepeat* step_and_repeat);
void pretty_print_standard_aperture_circle(StandardApertureCircle* circle);
void pretty_print_standard_aperture_rectangle(StandardApertureRectangle* rectangle);
void pretty_print_standard_aperture_obround(StandardApertureObround* obround);
void pretty_print_standard_aperture_polygon(StandardAperturePolygon* polygon);
void pretty_print_standard_aperture(StandardAperture* aperture);
void pretty_print_aperture_definition(ApertureDefinition* aperture_definition);
*/
void pretty_print_command_list(std::shared_ptr<CommandList>& command_list);

int main(int argc, char** argv)
{
	if (argc != 2) {
		std::cout << "Usage: scanner_tester <gerber_file>" << std::endl;
		return 1;
	}

	std::ifstream gerber_file;
	gerber_file.open(argv[1], std::ios::in);
	if (!gerber_file.is_open()) {
		std::cout << "Error opening file" << std::endl;
		return 2;
	}

	GerberRS274XScanner scanner(&gerber_file, &std::cout);
	
	/*
	yy::GerberRS274XParser::semantic_type semantic_value;
	yy::GerberRS274XParser::location_type location;
	
	bool done = false;
	
	while (!done) {
		int token_type = scanner.yylex(&semantic_value, &location);
		if (token_type == 0) {
			done = true;
		} else {
			pretty_print_token(token_type, semantic_value);
		}
	}
	*/

	std::shared_ptr<CommandList> result;
	yy::GerberRS274XParser parser(&result, scanner);
	parser.set_debug_level(1);
	int parse_result = parser.parse();
	printf("Parser returned result %d\n", parse_result);

	printf("Parsed Gerber File.  Stream of Commands:\n");
	pretty_print_command_list(result);
	
	gerber_file.close();
	
	return 0;
}

void pretty_print_command_list(std::shared_ptr<CommandList>& command_list)
{
	std::cout << *command_list;
}

/*
void pretty_print_command(Command* command)
{
	switch (command->type) {
		case COMMAND_TYPE_D_CODE:
			pretty_print_d_command(command->contents.d_command);
			break;

		case COMMAND_TYPE_SELECT_APERTURE:
			printf("Select aperture: %d\n", command->contents.aperture);
			break;

		case COMMAND_TYPE_G_CODE:
			pretty_print_g_command(command->contents.g_command);
			break;

		case COMMAND_TYPE_COMMENT:
			printf("Comment: %s\n", command->contents.comment);
			break;

		case COMMAND_TYPE_END_OF_FILE:
			printf("End of File\n");
			break;

		case COMMAND_TYPE_FORMAT_SPECIFIER:
			pretty_print_format_specifier(command->contents.format_specifier);
			break;

		case COMMAND_TYPE_UNITS:
			printf("Units: ");
			switch (command->contents.units) {
				case UNIT_TYPE_IN:
					printf("Inches\n");
					break;

				case UNIT_TYPE_MM:
					printf("Millimeters\n");
					break;
			}
			break;

		case COMMAND_TYPE_APERTURE_DEFINITION:
			pretty_print_aperture_definition(command->contents.aperture_definition);
			break;

		case COMMAND_TYPE_APERTURE_MACRO:
			printf("Aperture Macro:\n");
			pretty_print_aperture_macro(command->contents.aperture_macro);
			break;

		case COMMAND_TYPE_STEP_AND_REPEAT:
			pretty_print_step_and_repeat(command->contents.step_and_repeat);
			break;

		case COMMAND_TYPE_LEVEL_POLARITY:
			printf("Level polarity: ");
			switch (command->contents.level_polarity) {
				case LEVEL_POLARITY_DARK:
					printf("Dark\n");
					break;

				case LEVEL_POLARITY_CLEAR:
					printf("Clear\n");
					break;
			}
			break;
	}
}

void pretty_print_aperture_definition(ApertureDefinition* aperture_definition)
{
	printf("Aperture Definition: %d\n", aperture_definition->aperture_number);
	switch (aperture_definition->type) {
		case APERTURE_DEFINITION_TYPE_STANDARD:
			pretty_print_standard_aperture(aperture_definition->aperture.standard);
			break;

		case APERTURE_DEFINITION_TYPE_CUSTOM:
			printf("Custom aperture: %s\n", aperture_definition->aperture.custom_name);
			break;
	}
}

void pretty_print_standard_aperture(StandardAperture* aperture)
{
	switch (aperture->type) {
		case STANDARD_APERTURE_CIRCLE:
			pretty_print_standard_aperture_circle(aperture->contents.circle);
			break;

		case STANDARD_APERTURE_RECTANGLE:
			pretty_print_standard_aperture_rectangle(aperture->contents.rectangle);
			break;

		case STANDARD_APERTURE_OBROUND:
			pretty_print_standard_aperture_obround(aperture->contents.obround);
			break;

		case STANDARD_APERTURE_POLYGON:
			pretty_print_standard_aperture_polygon(aperture->contents.polygon);
			break;
	}
}

void pretty_print_standard_aperture_circle(StandardApertureCircle* circle)
{
	printf("Standard Aperture: Circle\n");
	printf("  Diameter: %f\n", circle->diameter);
	printf("  Has Hole: %s\n", circle->has_hole ? "True" : "False");
	if (circle->has_hole) {
		printf("  Hole Diameter: %f\n", circle->hole_diameter);
	}
}

void pretty_print_standard_aperture_rectangle(StandardApertureRectangle* rectangle)
{
	printf("Standard Aperture: Rectangle\n");
	printf("  X Size: %f\n", rectangle->x_size);
	printf("  Y Size: %f\n", rectangle->y_size);
	printf("  Has Hole: %s\n", rectangle->has_hole ? "True" : "False");
	if (rectangle->has_hole) {
		printf("  Hole Diameter: %f\n", rectangle->hole_diameter);
	}
}

void pretty_print_standard_aperture_obround(StandardApertureObround* obround)
{
	printf("Standard Aperture: Obround\n");
	printf("  X Size: %f\n", obround->x_size);
	printf("  Y Size: %f\n", obround->y_size);
	printf("  Has Hole: %s\n", obround->has_hole ? "True" : "False");
	if (obround->has_hole) {
		printf("  Hole Diameter: %f\n", obround->hole_diameter);
	}
}

void pretty_print_standard_aperture_polygon(StandardAperturePolygon* polygon)
{
	printf("Standard Aperture: Polygon\n");
	printf("  Diameter: %f\n", polygon->diameter);
	printf("  Number of Vertices: %f\n", polygon->num_vertices);
	printf("  Has Rotation: %s\n", polygon->has_rotation ? "True" : "False");
	if (polygon->has_rotation) {
		printf("  Rotation: %f\n", polygon->rotation);
	}
	printf("  Has Hole: %s\n", polygon->has_hole ? "True" : "False");
	if (polygon->has_hole) {
		printf("  Hole Diameter: %f\n", polygon->hole_diameter);
	}
}

void pretty_print_step_and_repeat(StepAndRepeat* step_and_repeat)
{
	printf("Step and Repeat\n");
	printf("  Number of repeats in the X dimension: %d\n", step_and_repeat->x_num_repeats);
	printf("  Number of repeats in the Y dimension: %d\n", step_and_repeat->y_num_repeats);
	printf("  Step distance in the X dimension: %f\n", step_and_repeat->x_step_distance);
	printf("  Step distance in the Y dimension: %f\n", step_and_repeat->y_step_distance);
}

void pretty_print_format_specifier(FormatSpecifier* format_specifier)
{
	printf("Format Specifier:\n");
	printf("  Number of Integer Places: %d\n", format_specifier->num_int_positions);
	printf("  Number of Decimal Places: %d\n", format_specifier->num_dec_positions);
}

void pretty_print_d_command(DCommand* d_command)
{
	printf("D Command: ");
	switch (d_command->type) {
		case D_CODE_INTERPOLATE:
			printf("Interpolate\n");
			break;

		case D_CODE_MOVE:
			printf("Move\n");
			break;

		case D_CODE_FLASH:
			printf("Flash\n");
			break;
	}

	if (d_command->coord_data != NULL) {
		pretty_print_coordinate_data(d_command->coord_data);
	} else {
		printf("  No coordinate data\n");
	}
}

void pretty_print_coordinate_data(CoordinateData* coord_data)
{
	printf("  Coordinate Data:\n");

	if (coord_data->x_valid) {
		printf("    X: %d\n", coord_data->x);
	} else {
		printf("    X: None\n");
	}

	if (coord_data->y_valid) {
		printf("    Y: %d\n", coord_data->y);
	} else {
		printf("    Y: None\n");
	}

	if (coord_data->i_valid) {
		printf("    I: %d\n", coord_data->i);
	} else {
		printf("    I: None\n");
	}

	if (coord_data->j_valid) {
		printf("    J: %d\n", coord_data->j);
	} else {
		printf("    J: None\n");
	}
}

void pretty_print_g_command(GCodeType g_code)
{
	printf("G Code: ");
	switch (g_code) {
		case G_CODE_LINEAR_INTERP_MODE:
			printf("Linear interpolation mode\n");
			break;

		case G_CODE_CW_CIRCULAR_INTERP_MODE:
			printf("Clockwise circular interpolation mode\n");
			break;

		case G_CODE_CCW_CIRCULAR_INTERP_MODE:
			printf("Counter-Clockwise circular interpolation mode\n");
			break;

		case G_CODE_SINGLE_QUADRANT_MODE:
			printf("Single-Quadrant mode\n");
			break;

		case G_CODE_MULTI_QUADRANT_MODE:
			printf("Multi-Quadrant mode\n");
			break;

		case G_CODE_REGION_MODE_ON:
			printf("Region mode on\n");
			break;

		case G_CODE_REGION_MODE_OFF:
			printf("Region mode off\n");
			break;
	}
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

void pretty_print_token(int token_type, yy::GerberRS274XParser::semantic_type& semantic_value)
{
	switch (token_type) {
		case yy::GerberRS274XParser::token::D_CMD_TYPE_INTERPOLATE:
			printf("D Command: Interpolate\n");
			break;

		case yy::GerberRS274XParser::token::D_CMD_TYPE_MOVE:
			printf("D Command: Move\n");
			break;

		case yy::GerberRS274XParser::token::D_CMD_TYPE_FLASH:
			printf("D Command: Flash\n");
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_LINEAR_INTERP_MODE:
			printf("G Command: Linear Interpolation Mode\n");
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_CW_CIRC_INTERP_MODE:
			printf("G Command: Clockwise Circular Interpolation Mode\n");
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_CCW_CIRC_INTERP_MODE:
			printf("G Command: Counter-Clockwise Circular Interpolation Mode\n");
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_SINGLE_QUADRANT_MODE:
			printf("G Command: Single-Quadrant Mode\n");
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_MULTI_QUADRANT_MODE:
			printf("G Command: Multi-Quadrant Mode\n");
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_REGION_MODE_ON:
			printf("G Command: Region Mode On\n");
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_REGION_MODE_OFF:
			printf("G Command: Region Mode Off\n");
			break;
			
		case yy::GerberRS274XParser::token::APERTURE_NUMBER:
			printf("Aperture Number %d\n", semantic_value.as<int>());
			break;
			
		case yy::GerberRS274XParser::token::COMMENT_START:
			printf("Comment Start\n");
			break;
		
		case yy::GerberRS274XParser::token::COMMENT_STRING:
			printf("Comment Content: %s\n", semantic_value.as<char*>());
			free(semantic_value.as<char*>());
			break;
			
		case yy::GerberRS274XParser::token::END_OF_FILE:
			printf("End of file\n");
			break;
			
		case yy::GerberRS274XParser::token::X_COORDINATE:
			printf("X Coordinate: %d\n", semantic_value.as<int>());
			break;
			
		case yy::GerberRS274XParser::token::Y_COORDINATE:
			printf("Y Coordinate: %d\n", semantic_value.as<int>());
			break;
			
		case yy::GerberRS274XParser::token::I_OFFSET:
			printf("I Offset: %d\n", semantic_value.as<int>());
			break;
			
		case yy::GerberRS274XParser::token::J_OFFSET:
			printf("J Offset: %d\n", semantic_value.as<int>());
			break;
			
		case yy::GerberRS274XParser::token::COORD_FORMAT:
			printf("Coordinate Format\n");
			break;
			
		case yy::GerberRS274XParser::token::COORD_FORMAT_NUM_INT_POSITIONS:
			printf("Coordinate Format Number of Integer Positions: %d\n", semantic_value.as<int>());
			break;
			
		case yy::GerberRS274XParser::token::COORD_FORMAT_NUM_DEC_POSITIONS:
			printf("Coordinate Format Number of Decimal Positions: %d\n", semantic_value.as<int>());
			break;
			
		case yy::GerberRS274XParser::token::UNIT_SPECIFIER:
			printf("Units: ");
			if (semantic_value.as<UnitType>() == UNIT_TYPE_IN) {
				printf("Inches\n");
			} else {
				printf("Millimeters\n");
			}
			break;
			
		case yy::GerberRS274XParser::token::END_OF_DATA_BLOCK:
			printf("End of Data Block\n");		
			break;
			
		case yy::GerberRS274XParser::token::EXT_CMD_DELIMITER:
			printf("Extended Command Delimiter\n");
			break;

		case yy::GerberRS274XParser::token::APERTURE_DEFINITION:
			printf("Aperture Definition\n");
			break;

		case yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_CIRCLE:
			printf("Standard Aperture: Circle\n");
			break;

		case yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_RECTANGLE:
			printf("Standard Aperture: Rectangle\n");
			break;

		case yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_OBROUND:
			printf("Standard Aperture: Obround\n");
			break;

		case yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_POLYGON:
			printf("Standard Aperture: Polygon\n");
			break;

		case yy::GerberRS274XParser::token::CUSTOM_APERTURE_NAME:
			printf("Custom Aperture Name: %s\n", semantic_value.as<char*>());
			free(semantic_value.as<char*>());
			break;

		case yy::GerberRS274XParser::token::APERTURE_DEFINITION_MODIFIER:
			printf("Aperture Definition Modifier: %f\n", semantic_value.as<double>());
			break;

		case yy::GerberRS274XParser::token::APERTURE_MACRO:
			printf("Aperture Macro\n");
			break;

		case yy::GerberRS274XParser::token::VARIABLE_DEFINITION:
			printf("Variable Definition: $%d\n", semantic_value.as<int>());
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_ADD:
			printf("Arithmetic Operator: +\n");
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_SUB:
			printf("Arithmetic Operator: -\n");
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_MULT:
			printf("Arithmetic Operator: *\n");
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_DIV:
			printf("Arithmetic Operator: /\n");
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_LEFT_PAREN:
			printf("Arithmetic Operator: (\n");
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_RIGHT_PAREN:
			printf("Arithmetic Operator: )\n");
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_CONSTANT:
			printf("Arithmetic Constant: %f\n", semantic_value.as<double>());
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_VAR_REFERENCE:
			printf("Arithmetic Variable Reference: $%d\n", semantic_value.as<int>());
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_CIRCLE:
			printf("Aperture Primitive: Circle\n");
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_VECTOR_LINE:
			printf("Aperture Primitive: Vector Line\n");
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_CENTER_LINE:
			printf("Aperture Primitive: Center Line\n");
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_OUTLINE:
			printf("Aperture Primitive: Outline\n");
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_POLYGON:
			printf("Aperture Primitive: Polygon\n");
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_MOIRE:
			printf("Aperture Primitive: Moire\n");
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_THERMAL:
			printf("Aperture Primitive: Thermal\n");
			break;

		case yy::GerberRS274XParser::token::AM_DELIM:
			printf("Aperture Primitive Modifier Delimiter\n");
			break;

		case yy::GerberRS274XParser::token::APERTURE_COMMENT_START:
			printf("Aperture Comment Start\n");
			break;

		case yy::GerberRS274XParser::token::APERTURE_COMMENT_CONTENT:
			printf("Aperture Comment: %s\n", semantic_value.as<char*>());
			free(semantic_value.as<char*>());
			break;

		case yy::GerberRS274XParser::token::STEP_AND_REPEAT_START:
			printf("Step and Repeat\n");
			break;

		case yy::GerberRS274XParser::token::X_REPEATS:
			printf("X Repeats: %d\n", semantic_value.as<int>());
			break;

		case yy::GerberRS274XParser::token::Y_REPEATS:
			printf("Y Repeats: %d\n", semantic_value.as<int>());
			break;

		case yy::GerberRS274XParser::token::X_STEP_DISTANCE:
			printf("X Step Distance: %f\n", semantic_value.as<double>());
			break;

		case yy::GerberRS274XParser::token::Y_STEP_DISTANCE:
			printf("Y Step Distance: %f\n", semantic_value.as<double>());
			break;

		case yy::GerberRS274XParser::token::LEVEL_POLARITY:
			switch (semantic_value.as<LevelPolarity>()) {
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
*/
