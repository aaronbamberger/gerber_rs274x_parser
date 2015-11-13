
#include "gerber_rs274x_scanner.hh"
#include "gerber_parser.yy.hh"

#include "GerberClasses/GlobalDefs.hh"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <iostream>
#include <fstream>
#include <ios>
#include <memory>

void pretty_print_token(int token_type, const yy::GerberRS274XParser::semantic_type& semantic_value, const yy::GerberRS274XParser::location_type& location);
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
	
	yy::GerberRS274XParser::semantic_type semantic_value;
	yy::GerberRS274XParser::location_type location;
	
	bool done = false;
	
	while (!done) {
		int token_type = scanner.yylex(&semantic_value, &location);
		if (token_type == 0) {
			done = true;
		} else {
			pretty_print_token(token_type, semantic_value, location);
		}
	}

	/*
	std::shared_ptr<CommandList> result;
	yy::GerberRS274XParser parser(&result, scanner);
	parser.set_debug_level(1);
	int parse_result = parser.parse();
	printf("Parser returned result %d\n", parse_result);

	printf("Parsed Gerber File.  Stream of Commands:\n");
	pretty_print_command_list(result);
	
	result->check_semantic_validity();
	*/

	gerber_file.close();
	
	return 0;
}

void pretty_print_command_list(std::shared_ptr<CommandList>& command_list)
{
	std::cout << *command_list;
}

void pretty_print_token(int token_type, const yy::GerberRS274XParser::semantic_type& semantic_value, const yy::GerberRS274XParser::location_type& location)
{
    printf("Token Location: (%d, %d)-->(%d, %d)\n", location.begin.line, location.begin.column, location.end.line, location.end.column);

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
			switch (semantic_value.as<Gerber::UnitType>()) {
				case Gerber::UnitType::UNIT_TYPE_IN:
					printf("Inches\n");
					break;

				case Gerber::UnitType::UNIT_TYPE_MM:
					printf("Millimeters\n");
					break;

				case Gerber::UnitType::UNIT_TYPE_UNDEFINED:
				    printf("Undefined\n");
				    break;
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
			switch (semantic_value.as<Gerber::LevelPolarityType>()) {
				case Gerber::LevelPolarityType::LEVEL_POLARITY_CLEAR:
					printf("Level Polarity Clear\n");
					break;

				case Gerber::LevelPolarityType::LEVEL_POLARITY_DARK:
					printf("Level Polarity Dark\n");
					break;
			}
			break;
	}
}
