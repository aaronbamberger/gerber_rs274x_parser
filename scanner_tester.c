#include "gerber_scanner_defs.h"
#include "gerber_parser_defs.h"
#include "gerber_scanner.yy.h"
#include "gerber_parser.yy.h"

#include <stdio.h>
#include <stdbool.h>

void pretty_print_token(int token_type, YYSTYPE* semantic_value);

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
	}
	*/

	yydebug = 1;
	ApertureMacro* result;
	int parse_result = yyparse(&result, scanner);
	printf("Parser returned result %d, top level of AST: %p\n", parse_result, result);
	
	yylex_destroy(scanner);
	fclose(gerber_file);
	
	return 0;
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
