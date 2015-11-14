
#include "gerber_rs274x_scanner.hh"
#include "gerber_parser.yy.hh"

#include "GerberClasses/GlobalDefs.hh"

#include <iostream>
#include <fstream>
#include <ios>
#include <memory>
#include <string>

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
	std::cout << "Parser returned result: " << parse_result << std::endl;

	std::cout << "Parsed Gerber File.  Stream of Commands:" << std::endl;
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
		    std::cout << "D Command: Interpolate" << std::endl;
			break;

		case yy::GerberRS274XParser::token::D_CMD_TYPE_MOVE:
		    std::cout << "D Command: Move" << std::endl;
			break;

		case yy::GerberRS274XParser::token::D_CMD_TYPE_FLASH:
		    std::cout << "D Command: Flash" << std::endl;
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_LINEAR_INTERP_MODE:
			std::cout << "G Command: Linear Interpolation Mode" << std::endl;
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_CW_CIRC_INTERP_MODE:
			std::cout << "G Command: Clockwise Circular Interpolation Mode" << std::endl;
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_CCW_CIRC_INTERP_MODE:
			std::cout << "G Command: Counter-Clockwise Circular Interpolation Mode" << std::endl;
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_SINGLE_QUADRANT_MODE:
			std::cout << "G Command: Single-Quadrant Mode" << std::endl;
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_MULTI_QUADRANT_MODE:
			std::cout << "G Command: Multi-Quadrant Mode" << std::endl;
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_REGION_MODE_ON:
			std::cout << "G Command: Region Mode On" << std::endl;
			break;

		case yy::GerberRS274XParser::token::G_CMD_TYPE_REGION_MODE_OFF:
			std::cout << "G Command: Region Mode Off" << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::APERTURE_NUMBER:
		    std::cout << "Aperture Number: " << semantic_value.as<int>() << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::COMMENT_START:
			std::cout << "Comment Start" << std::endl;
			break;
		
		case yy::GerberRS274XParser::token::COMMENT_STRING:
		    std::cout << "Comment Content: " << semantic_value.as<std::string>() << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::END_OF_FILE:
			std::cout << "End of file" << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::X_COORDINATE:
			std::cout << "X Coordinate: " << semantic_value.as<int>() << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::Y_COORDINATE:
			std::cout << "Y Coordinate: " << semantic_value.as<int>() << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::I_OFFSET:
			std::cout << "I Offset: " << semantic_value.as<int>() << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::J_OFFSET:
			std::cout << "J Offset: " << semantic_value.as<int>() << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::COORD_FORMAT:
			std::cout << "Coordinate Format" << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::COORD_FORMAT_NUM_INT_POSITIONS:
			std::cout << "Coordinate Format Number of Integer Positions: " << semantic_value.as<int>() << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::COORD_FORMAT_NUM_DEC_POSITIONS:
			std::cout << "Coordinate Format Number of Decimal Positions: " << semantic_value.as<int>() << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::UNIT_SPECIFIER:
			std::cout << "Units: ";
			switch (semantic_value.as<Gerber::UnitType>()) {
				case Gerber::UnitType::UNIT_TYPE_IN:
					std::cout << "Inches" << std::endl;
					break;

				case Gerber::UnitType::UNIT_TYPE_MM:
					std::cout << "Millimeters" << std::endl;
					break;

				case Gerber::UnitType::UNIT_TYPE_UNDEFINED:
				    std::cout << "Undefined" << std::endl;
				    break;
			}
			break;
			
		case yy::GerberRS274XParser::token::END_OF_DATA_BLOCK:
			std::cout << "End of Data Block" << std::endl;
			break;
			
		case yy::GerberRS274XParser::token::EXT_CMD_DELIMITER:
			std::cout << "Extended Command Delimiter" << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_DEFINITION:
			std::cout << "Aperture Definition" << std::endl;
			break;

		case yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_CIRCLE:
			std::cout << "Standard Aperture: Circle" << std::endl;
			break;

		case yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_RECTANGLE:
			std::cout << "Standard Aperture: Rectangle" << std::endl;
			break;

		case yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_OBROUND:
			std::cout << "Standard Aperture: Obround" << std::endl;
			break;

		case yy::GerberRS274XParser::token::STANDARD_APERTURE_TYPE_POLYGON:
			std::cout << "Standard Aperture: Polygon" << std::endl;
			break;

		case yy::GerberRS274XParser::token::CUSTOM_APERTURE_NAME:
		    std::cout << "Custom Aperture Name: " << semantic_value.as<std::string>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_DEFINITION_MODIFIER:
			std::cout << "Aperture Definition Modifier: " << semantic_value.as<double>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_MACRO:
			std::cout << "Aperture Macro" << std::endl;
			break;

		case yy::GerberRS274XParser::token::VARIABLE_DEFINITION:
			std::cout << "Variable Definition: $" << semantic_value.as<int>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_ADD:
			std::cout << "Arithmetic Operator: +" << std::endl;
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_SUB:
			std::cout << "Arithmetic Operator: -" << std::endl;
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_MULT:
			std::cout << "Arithmetic Operator: *" << std::endl;
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_DIV:
			std::cout << "Arithmetic Operator: /" << std::endl;
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_LEFT_PAREN:
			std::cout << "Arithmetic Operator: (" << std::endl;
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_RIGHT_PAREN:
			std::cout << "Arithmetic Operator: )" << std::endl;
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_CONSTANT:
			std::cout << "Arithmetic Constant: " << semantic_value.as<double>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::ARITHMETIC_VAR_REFERENCE:
			std::cout << "Arithmetic Variable Reference: " << semantic_value.as<int>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_CIRCLE:
			std::cout << "Aperture Primitive: Circle" << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_VECTOR_LINE:
			std::cout << "Aperture Primitive: Vector Line" << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_CENTER_LINE:
			std::cout << "Aperture Primitive: Center Line" << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_OUTLINE:
			std::cout << "Aperture Primitive: Outline" << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_POLYGON:
		    std::cout << "Aperture Primitive: Polygon" << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_MOIRE:
			std::cout << "Aperture Primitive: Moire" << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_PRIMITIVE_TYPE_THERMAL:
			std::cout << "Aperture Primitive: Thermal" << std::endl;
			break;

		case yy::GerberRS274XParser::token::AM_DELIM:
			std::cout << "Aperture Primitive Modifier Delimiter" << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_COMMENT_START:
			std::cout << "Aperture Comment Start" << std::endl;
			break;

		case yy::GerberRS274XParser::token::APERTURE_COMMENT_CONTENT:
		    std::cout << "Aperture Comment: " << semantic_value.as<std::string>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::STEP_AND_REPEAT_START:
			std::cout << "Step and Repeat" << std::endl;
			break;

		case yy::GerberRS274XParser::token::X_REPEATS:
			std::cout << "X Repeats: " << semantic_value.as<int>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::Y_REPEATS:
			std::cout << "Y Repeats: " << semantic_value.as<int>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::X_STEP_DISTANCE:
			std::cout << "X Step Distance: " << semantic_value.as<double>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::Y_STEP_DISTANCE:
			std::cout << "Y Step Distance: " << semantic_value.as<double>() << std::endl;
			break;

		case yy::GerberRS274XParser::token::LEVEL_POLARITY:
			switch (semantic_value.as<Gerber::LevelPolarityType>()) {
				case Gerber::LevelPolarityType::LEVEL_POLARITY_CLEAR:
					std::cout << "Level Polarity Clear" << std::endl;
					break;

				case Gerber::LevelPolarityType::LEVEL_POLARITY_DARK:
					std::cout << "Level Polarity Dark" << std::endl;
					break;
			}
			break;
	}
}
