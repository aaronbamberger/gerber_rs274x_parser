%code top {
	#include <stdio.h>
	#include <stdlib.h>
}

%code requires {
	#include "gerber_parser_defs.h"
	#include "GerberClasses/CommandList.hh"
	#include "GerberClasses/Command.hh"
	#include "GerberClasses/DCommand.hh"
	#include "GerberClasses/GCommand.hh"
	#include "GerberClasses/CoordinateData.hh"
	#include "GerberClasses/SelectApertureCommand.hh"
	#include "GerberClasses/ConstantArithmeticExpressionElement.hh"

	#include <memory>

	// Forward declare the scanner class so we can use it in the function prototypes
	class GerberRS274XScanner;
}

%code {
	static int yylex(yy::GerberRS274XParser::semantic_type* yylval, yy::GerberRS274XParser::location_type* yylloc, GerberRS274XScanner& scanner);
}

%defines "gerber_parser.yy.hh"
%output "gerber_parser.yy.cc"
%define parse.trace
%define api.value.type variant
%define parser_class_name {GerberRS274XParser}
%skeleton "lalr1.cc"
%locations
%parse-param {std::shared_ptr<CommandList>* result}
%param {GerberRS274XScanner& scanner}

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
%token <char*> COMMENT_STRING
%token END_OF_FILE
%token <int> X_COORDINATE
%token <int> Y_COORDINATE
%token <int> I_OFFSET
%token <int> J_OFFSET
%token <int> X_REPEATS
%token <int> Y_REPEATS
%token <double> X_STEP_DISTANCE
%token <double> Y_STEP_DISTANCE
%token COORD_FORMAT
%token <int> COORD_FORMAT_NUM_INT_POSITIONS
%token <int> COORD_FORMAT_NUM_DEC_POSITIONS
%token <UnitType> UNIT_SPECIFIER
%token END_OF_DATA_BLOCK
%token EXT_CMD_DELIMITER
%token APERTURE_DEFINITION
%token <int> APERTURE_NUMBER
%token STANDARD_APERTURE_TYPE_CIRCLE
%token STANDARD_APERTURE_TYPE_RECTANGLE
%token STANDARD_APERTURE_TYPE_OBROUND
%token STANDARD_APERTURE_TYPE_POLYGON
%token <char*> CUSTOM_APERTURE_NAME
%token <double> APERTURE_DEFINITION_MODIFIER
%token APERTURE_MACRO
%token <int> VARIABLE_DEFINITION
%token ARITHMETIC_LEFT_PAREN
%token ARITHMETIC_RIGHT_PAREN
%token <double> ARITHMETIC_CONSTANT
%token <int> ARITHMETIC_VAR_REFERENCE
%token APERTURE_PRIMITIVE_TYPE_CIRCLE
%token APERTURE_PRIMITIVE_TYPE_VECTOR_LINE
%token APERTURE_PRIMITIVE_TYPE_CENTER_LINE
%token APERTURE_PRIMITIVE_TYPE_OUTLINE
%token APERTURE_PRIMITIVE_TYPE_POLYGON
%token APERTURE_PRIMITIVE_TYPE_MOIRE
%token APERTURE_PRIMITIVE_TYPE_THERMAL
%token AM_DELIM
%token APERTURE_COMMENT_START
%token <char*> APERTURE_COMMENT_CONTENT
%token STEP_AND_REPEAT_START
%token <LevelPolarity> LEVEL_POLARITY

%left ARITHMETIC_ADD ARITHMETIC_SUB
%left ARITHMETIC_MULT ARITHMETIC_DIV
%precedence UNARY_MINUS

/*
%type <ApertureMacro*> aperture_macro
%type <MacroContentList*> macro_content_list
%type <MacroContentElement*> macro_content_element
%type <MacroPrimitive*> macro_primitive
%type <char*> macro_primitive_comment
%type <MacroPrimitiveCircle*> macro_primitive_circle
%type <MacroPrimitiveVectorLine*> macro_primitive_vector_line
%type <MacroPrimitiveCenterLine*> macro_primitive_center_line
%type <ExpressionCoord*> expression_coord
%type <ExpressionCoordList*> expression_coord_list
%type <MacroPrimitiveOutline*> macro_primitive_outline
%type <MacroPrimitivePolygon*> macro_primitive_polygon
%type <MacroPrimitiveMoire*> macro_primitive_moire
%type <MacroPrimitiveThermal*> macro_primitive_thermal
*/
%type <std::shared_ptr<ArithmeticExpressionElement>> arithmetic_expression
/*
%type <VariableDefinition*> variable_definition
*/
%type <std::shared_ptr<CoordinateData>> coordinate_data
%type <std::shared_ptr<Command>> interpolate_cmd
%type <std::shared_ptr<Command>> move_cmd
%type <std::shared_ptr<Command>> flash_cmd
/*
%type <FormatSpecifier*> format_specifier
%type <StepAndRepeat*> step_and_repeat
%type <StandardApertureCircle*> standard_aperture_circle
%type <StandardApertureRectangle*> standard_aperture_rectangle
%type <StandardApertureObround*> standard_aperture_obround
%type <StandardAperturePolygon*> standard_aperture_polygon
%type <StandardAperture*> standard_aperture
%type <ApertureDefinition*> aperture_definition
*/
%type <std::shared_ptr<Command>> command
%type <std::shared_ptr<CommandList>> command_list

%%

top_level:
	command_list {
		*result = $[command_list];
	}

command_list[result]:
	command_list[list] command {
		$list->add_command($command);
		$result = $list;
	}
|	command {
		$result = std::make_shared<CommandList>();
		$result->add_command($command);
	}

command:
	interpolate_cmd {
		$command = $[interpolate_cmd];
	}
|	move_cmd {
		$command = $[move_cmd];
	}
|	flash_cmd {
		$command = $[flash_cmd];
	}
|	APERTURE_NUMBER END_OF_DATA_BLOCK {
		$command = std::make_shared<SelectApertureCommand>($[APERTURE_NUMBER]);
	}
|	G_CMD_TYPE_LINEAR_INTERP_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_LINEAR_INTERP_MODE);
	}
|	G_CMD_TYPE_CW_CIRC_INTERP_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_CW_CIRCULAR_INTERP_MODE);
	}
|	G_CMD_TYPE_CCW_CIRC_INTERP_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_CCW_CIRCULAR_INTERP_MODE);
	}
|	G_CMD_TYPE_REGION_MODE_ON END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_REGION_MODE_ON);
	}
|	G_CMD_TYPE_REGION_MODE_OFF END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_REGION_MODE_OFF);
	}
|	G_CMD_TYPE_MULTI_QUADRANT_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_MULTI_QUADRANT_MODE);
	}
|	G_CMD_TYPE_SINGLE_QUADRANT_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_SINGLE_QUADRANT_MODE);
	}
/*
|	COMMENT_START COMMENT_STRING END_OF_DATA_BLOCK {
		$command = (Command*)calloc(1, sizeof(Command));
		$command->next = NULL;
		$command->type = COMMAND_TYPE_COMMENT;
		$command->contents.comment = $[COMMENT_STRING];
	}
|	END_OF_FILE END_OF_DATA_BLOCK {
		$command = (Command*)calloc(1, sizeof(Command));
		$command->next = NULL;
		$command->type = COMMAND_TYPE_END_OF_FILE;
	}
|	format_specifier {
		$command = (Command*)calloc(1, sizeof(Command));
		$command->next = NULL;
		$command->type = COMMAND_TYPE_FORMAT_SPECIFIER;
		$command->contents.format_specifier = $[format_specifier];
	}
|	EXT_CMD_DELIMITER UNIT_SPECIFIER END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$command = (Command*)calloc(1, sizeof(Command));
		$command->next = NULL;
		$command->type = COMMAND_TYPE_UNITS;
		$command->contents.units = $[UNIT_SPECIFIER];
	}
|	aperture_definition {
		$command = (Command*)calloc(1, sizeof(Command));
		$command->next = NULL;
		$command->type = COMMAND_TYPE_APERTURE_DEFINITION;
		$command->contents.aperture_definition = $[aperture_definition];
	}
|	aperture_macro {
		$command = (Command*)calloc(1, sizeof(Command));
		$command->next = NULL;
		$command->type = COMMAND_TYPE_APERTURE_MACRO;
		$command->contents.aperture_macro = $[aperture_macro];
	}
|	step_and_repeat {
		$command = (Command*)calloc(1, sizeof(Command));
		$command->next = NULL;
		$command->type = COMMAND_TYPE_STEP_AND_REPEAT;
		$command->contents.step_and_repeat = $[step_and_repeat];
	}
| 	EXT_CMD_DELIMITER LEVEL_POLARITY END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$command = (Command*)calloc(1, sizeof(Command));
		$command->next = NULL;
		$command->type = COMMAND_TYPE_LEVEL_POLARITY;
		$command->contents.level_polarity = $[LEVEL_POLARITY];
	}

aperture_definition:
	EXT_CMD_DELIMITER APERTURE_DEFINITION APERTURE_NUMBER standard_aperture END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[aperture_definition] = (ApertureDefinition*)calloc(1, sizeof(ApertureDefinition));
		$[aperture_definition]->type = APERTURE_DEFINITION_TYPE_STANDARD;
		$[aperture_definition]->aperture_number = $[APERTURE_NUMBER];
		$[aperture_definition]->aperture.standard = $[standard_aperture];
	}
|	EXT_CMD_DELIMITER APERTURE_DEFINITION APERTURE_NUMBER CUSTOM_APERTURE_NAME END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[aperture_definition] = (ApertureDefinition*)calloc(1, sizeof(ApertureDefinition));
		$[aperture_definition]->type = APERTURE_DEFINITION_TYPE_CUSTOM;
		$[aperture_definition]->aperture_number = $[APERTURE_NUMBER];
		$[aperture_definition]->aperture.custom_name = $[CUSTOM_APERTURE_NAME];
	}

standard_aperture:
	standard_aperture_circle {
		$[standard_aperture] = (StandardAperture*)calloc(1, sizeof(StandardAperture));
		$[standard_aperture]->type = STANDARD_APERTURE_CIRCLE;
		$[standard_aperture]->contents.circle = $[standard_aperture_circle];
	}
|	standard_aperture_rectangle {
		$[standard_aperture] = (StandardAperture*)calloc(1, sizeof(StandardAperture));
		$[standard_aperture]->type = STANDARD_APERTURE_RECTANGLE;
		$[standard_aperture]->contents.rectangle = $[standard_aperture_rectangle];
	}
|	standard_aperture_obround {
		$[standard_aperture] = (StandardAperture*)calloc(1, sizeof(StandardAperture));
		$[standard_aperture]->type = STANDARD_APERTURE_OBROUND;
		$[standard_aperture]->contents.obround = $[standard_aperture_obround];
	}
|	standard_aperture_polygon {
		$[standard_aperture] = (StandardAperture*)calloc(1, sizeof(StandardAperture));
		$[standard_aperture]->type = STANDARD_APERTURE_POLYGON;
		$[standard_aperture]->contents.polygon = $[standard_aperture_polygon];
	}

standard_aperture_circle:
	STANDARD_APERTURE_TYPE_CIRCLE APERTURE_DEFINITION_MODIFIER[diameter] APERTURE_DEFINITION_MODIFIER[hole_diameter] {
		$[standard_aperture_circle] = (StandardApertureCircle*)calloc(1, sizeof(StandardApertureCircle));
		$[standard_aperture_circle]->diameter = $diameter;
		$[standard_aperture_circle]->hole_diameter = $[hole_diameter];
		$[standard_aperture_circle]->has_hole = true;
	}
|	STANDARD_APERTURE_TYPE_CIRCLE APERTURE_DEFINITION_MODIFIER[diameter] {
		$[standard_aperture_circle] = (StandardApertureCircle*)calloc(1, sizeof(StandardApertureCircle));
		$[standard_aperture_circle]->diameter = $diameter;
		$[standard_aperture_circle]->has_hole = false;
	}

standard_aperture_rectangle:
	STANDARD_APERTURE_TYPE_RECTANGLE APERTURE_DEFINITION_MODIFIER[x_size] APERTURE_DEFINITION_MODIFIER[y_size] APERTURE_DEFINITION_MODIFIER[hole_diameter] {
		$[standard_aperture_rectangle] = (StandardApertureRectangle*)calloc(1, sizeof(StandardApertureRectangle));
		$[standard_aperture_rectangle]->x_size = $[x_size];
		$[standard_aperture_rectangle]->y_size = $[y_size];
		$[standard_aperture_rectangle]->hole_diameter = $[hole_diameter];
		$[standard_aperture_rectangle]->has_hole = true;
	}
|	STANDARD_APERTURE_TYPE_RECTANGLE APERTURE_DEFINITION_MODIFIER[x_size] APERTURE_DEFINITION_MODIFIER[y_size] {
		$[standard_aperture_rectangle] = (StandardApertureRectangle*)calloc(1, sizeof(StandardApertureRectangle));
		$[standard_aperture_rectangle]->x_size = $[x_size];
		$[standard_aperture_rectangle]->y_size = $[y_size];
		$[standard_aperture_rectangle]->has_hole = false;
	}

standard_aperture_obround:
	STANDARD_APERTURE_TYPE_OBROUND APERTURE_DEFINITION_MODIFIER[x_size] APERTURE_DEFINITION_MODIFIER[y_size] APERTURE_DEFINITION_MODIFIER[hole_diameter] {
		$[standard_aperture_obround] = (StandardApertureObround*)calloc(1, sizeof(StandardApertureObround));
		$[standard_aperture_obround]->x_size = $[x_size];
		$[standard_aperture_obround]->y_size = $[y_size];
		$[standard_aperture_obround]->hole_diameter = $[hole_diameter];
		$[standard_aperture_obround]->has_hole = true;
	}
|	STANDARD_APERTURE_TYPE_OBROUND APERTURE_DEFINITION_MODIFIER[x_size] APERTURE_DEFINITION_MODIFIER[y_size] {
		$[standard_aperture_obround] = (StandardApertureObround*)calloc(1, sizeof(StandardApertureObround));
		$[standard_aperture_obround]->x_size = $[x_size];
		$[standard_aperture_obround]->y_size = $[y_size];
		$[standard_aperture_obround]->has_hole = false;
	}

standard_aperture_polygon:
	STANDARD_APERTURE_TYPE_POLYGON APERTURE_DEFINITION_MODIFIER[diameter] APERTURE_DEFINITION_MODIFIER[num_vertices] APERTURE_DEFINITION_MODIFIER[rotation] APERTURE_DEFINITION_MODIFIER[hole_diameter] {
		$[standard_aperture_polygon] = (StandardAperturePolygon*)calloc(1, sizeof(StandardAperturePolygon));
		$[standard_aperture_polygon]->diameter = $diameter;
		$[standard_aperture_polygon]->num_vertices = $[num_vertices];
		$[standard_aperture_polygon]->rotation = $rotation;
		$[standard_aperture_polygon]->hole_diameter = $[hole_diameter];
		$[standard_aperture_polygon]->has_rotation = true;
		$[standard_aperture_polygon]->has_hole = true;
	}
|	STANDARD_APERTURE_TYPE_POLYGON APERTURE_DEFINITION_MODIFIER[diameter] APERTURE_DEFINITION_MODIFIER[num_vertices] APERTURE_DEFINITION_MODIFIER[rotation] {
		$[standard_aperture_polygon] = (StandardAperturePolygon*)calloc(1, sizeof(StandardAperturePolygon));
		$[standard_aperture_polygon]->diameter = $diameter;
		$[standard_aperture_polygon]->num_vertices = $[num_vertices];
		$[standard_aperture_polygon]->rotation = $rotation;
		$[standard_aperture_polygon]->has_rotation = true;
		$[standard_aperture_polygon]->has_hole = false;
	}
|	STANDARD_APERTURE_TYPE_POLYGON APERTURE_DEFINITION_MODIFIER[diameter] APERTURE_DEFINITION_MODIFIER[num_vertices] {
		$[standard_aperture_polygon] = (StandardAperturePolygon*)calloc(1, sizeof(StandardAperturePolygon));
		$[standard_aperture_polygon]->diameter = $diameter;
		$[standard_aperture_polygon]->num_vertices = $[num_vertices];
		$[standard_aperture_polygon]->has_rotation = false;
		$[standard_aperture_polygon]->has_hole = false;
	}

step_and_repeat:
	EXT_CMD_DELIMITER STEP_AND_REPEAT_START X_REPEATS Y_REPEATS X_STEP_DISTANCE Y_STEP_DISTANCE END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[step_and_repeat] = (StepAndRepeat*)calloc(1, sizeof(StepAndRepeat));
		$[step_and_repeat]->x_num_repeats = $[X_REPEATS];
		$[step_and_repeat]->y_num_repeats = $[Y_REPEATS];
		$[step_and_repeat]->x_step_distance = $[X_STEP_DISTANCE];
		$[step_and_repeat]->y_step_distance = $[Y_STEP_DISTANCE];
	}
|	EXT_CMD_DELIMITER STEP_AND_REPEAT_START END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[step_and_repeat] = (StepAndRepeat*)calloc(1, sizeof(StepAndRepeat));
		$[step_and_repeat]->x_num_repeats = 1;
		$[step_and_repeat]->y_num_repeats = 1;
		$[step_and_repeat]->x_step_distance = 0.0;
		$[step_and_repeat]->y_step_distance = 0.0;
	}

format_specifier:
	EXT_CMD_DELIMITER COORD_FORMAT COORD_FORMAT_NUM_INT_POSITIONS COORD_FORMAT_NUM_DEC_POSITIONS END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[format_specifier] = (FormatSpecifier*)calloc(1, sizeof(FormatSpecifier));
		$[format_specifier]->num_int_positions = $[COORD_FORMAT_NUM_INT_POSITIONS];
		$[format_specifier]->num_dec_positions = $[COORD_FORMAT_NUM_DEC_POSITIONS];
	}
*/

interpolate_cmd:
	coordinate_data D_CMD_TYPE_INTERPOLATE END_OF_DATA_BLOCK {
		$[interpolate_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_INTERPOLATE, $[coordinate_data]);
		//$[interpolate_cmd] = std::move(std::unique_ptr<Command>(new DCommand(DCommand::DCommandType::D_COMMAND_INTERPOLATE, std::move($[coordinate_data]))));
	}
|	D_CMD_TYPE_INTERPOLATE END_OF_DATA_BLOCK {
		$[interpolate_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_INTERPOLATE);
		//$[interpolate_cmd] = std::move(std::unique_ptr<Command>(new DCommand(DCommand::DCommandType::D_COMMAND_INTERPOLATE)));
	}

move_cmd:
	coordinate_data D_CMD_TYPE_MOVE END_OF_DATA_BLOCK {
		$[move_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_MOVE, $[coordinate_data]);
		//$[move_cmd] = std::move(std::unique_ptr<Command>(new DCommand(DCommand::DCommandType::D_COMMAND_MOVE, std::move($[coordinate_data]))));
	}
|	D_CMD_TYPE_MOVE END_OF_DATA_BLOCK {
		$[move_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_MOVE);
		//$[move_cmd] = std::move(std::unique_ptr<Command>(new DCommand(DCommand::DCommandType::D_COMMAND_MOVE)));
	}

flash_cmd:
	coordinate_data D_CMD_TYPE_FLASH END_OF_DATA_BLOCK {
		$[flash_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_FLASH, $[coordinate_data]);
		//$[flash_cmd] = std::move(std::unique_ptr<Command>(new DCommand(DCommand::DCommandType::D_COMMAND_FLASH, std::move($[coordinate_data]))));
	}
|	D_CMD_TYPE_FLASH END_OF_DATA_BLOCK {
		$[flash_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_FLASH);
		//$[flash_cmd] = std::move(std::unique_ptr<Command>(new DCommand(DCommand::DCommandType::D_COMMAND_FLASH)));
	}

coordinate_data:
	X_COORDINATE {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], 0, 0, 0, true, false, false, false);
	}
|	Y_COORDINATE {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, $[Y_COORDINATE], 0, 0, false, true, false, false);
	}
|	X_COORDINATE Y_COORDINATE {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], $[Y_COORDINATE], 0, 0, true, true, false, false);
	}
|	I_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, 0, $[I_OFFSET], 0, false, false, true, false);
	}
|	X_COORDINATE I_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], 0, $[I_OFFSET], 0, true, false, true, false);
	}
|	Y_COORDINATE I_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, $[Y_COORDINATE], $[I_OFFSET], 0, false, true, true, false);
	}
|	X_COORDINATE Y_COORDINATE I_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], $[Y_COORDINATE], $[I_OFFSET], 0, true, true, true, false);
	}
|	J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, 0, 0, $[J_OFFSET], false, false, false, true);
	}
|	X_COORDINATE J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], 0, 0, $[J_OFFSET], true, false, false, true);
	}
|	Y_COORDINATE J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, $[Y_COORDINATE], 0, $[J_OFFSET], false, true, false, true);
	}
|	X_COORDINATE Y_COORDINATE J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], $[Y_COORDINATE], 0, $[J_OFFSET], true, true, false, true);
	}
|	I_OFFSET J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, 0, $[I_OFFSET], $[J_OFFSET], false, false, true, true);
	}
|	X_COORDINATE I_OFFSET J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], 0, $[I_OFFSET], $[J_OFFSET], true, false, true, true);
	}
|	Y_COORDINATE I_OFFSET J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, $[Y_COORDINATE], $[I_OFFSET], $[J_OFFSET], false, true, true, true);
	}
|	X_COORDINATE Y_COORDINATE I_OFFSET J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], $[Y_COORDINATE], $[I_OFFSET], $[J_OFFSET], true, true, true, true);
	}

/*
aperture_macro:
	EXT_CMD_DELIMITER APERTURE_MACRO CUSTOM_APERTURE_NAME END_OF_DATA_BLOCK macro_content_list EXT_CMD_DELIMITER {
		$aperture_macro = (ApertureMacro*)calloc(1, sizeof(ApertureMacro));
		$aperture_macro->name = $CUSTOM_APERTURE_NAME;
		$aperture_macro->content_list = $macro_content_list;
	}

macro_content_list[result]:
	macro_content_list[list] macro_content_element[new_elem] {
		$list->tail->next = $[new_elem];
		$list->tail = $[new_elem];
		$result = $list;
	}
|	macro_content_element[new_elem] {
		$result = (MacroContentList*)calloc(1, sizeof(MacroContentList));
		$result->head = $[new_elem];
		$result->tail = $[new_elem];
	}

macro_content_element:
	variable_definition {
		$macro_content_element = (MacroContentElement*)calloc(1, sizeof(MacroContentElement));
		$macro_content_element->next = NULL;
		$macro_content_element->type = MACRO_CONTENT_VAR_DEF;
		$macro_content_element->content.var_def = $[variable_definition];
	}
|	macro_primitive {
		$macro_content_element = (MacroContentElement*)calloc(1, sizeof(MacroContentElement));
		$macro_content_element->next = NULL;
		$macro_content_element->type = MACRO_CONTENT_PRIMITIVE;
		$macro_content_element->content.primitive = $[macro_primitive];
	}

macro_primitive:
	macro_primitive_comment END_OF_DATA_BLOCK {
		$macro_primitive = (MacroPrimitive*)calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_COMMENT;
		$macro_primitive->primitive.comment = $macro_primitive_comment;
	}
|	macro_primitive_circle END_OF_DATA_BLOCK {
		$macro_primitive = (MacroPrimitive*)calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_CIRCLE;
		$macro_primitive->primitive.circle = $macro_primitive_circle;
	}
|	macro_primitive_vector_line END_OF_DATA_BLOCK {
		$macro_primitive = (MacroPrimitive*)calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_VECTOR_LINE;
		$macro_primitive->primitive.vector_line = $macro_primitive_vector_line;
	}
|	macro_primitive_center_line END_OF_DATA_BLOCK {
		$macro_primitive = (MacroPrimitive*)calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_CENTER_LINE;
		$macro_primitive->primitive.center_line = $macro_primitive_center_line;
	}
|	macro_primitive_outline END_OF_DATA_BLOCK {
		$macro_primitive = (MacroPrimitive*)calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_OUTLINE;
		$macro_primitive->primitive.outline = $macro_primitive_outline;
	}
|	macro_primitive_polygon END_OF_DATA_BLOCK {
		$macro_primitive = (MacroPrimitive*)calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_POLYGON;
		$macro_primitive->primitive.polygon = $macro_primitive_polygon;
	}
|	macro_primitive_moire END_OF_DATA_BLOCK {
		$macro_primitive = (MacroPrimitive*)calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_MOIRE;
		$macro_primitive->primitive.moire = $macro_primitive_moire;
	}
|	macro_primitive_thermal END_OF_DATA_BLOCK {
		$macro_primitive = (MacroPrimitive*)calloc(1, sizeof(MacroPrimitive));
		$macro_primitive->type = MACRO_PRIMITIVE_TYPE_THERMAL;
		$macro_primitive->primitive.thermal = $macro_primitive_thermal;
	}

macro_primitive_comment:
	APERTURE_COMMENT_START APERTURE_COMMENT_CONTENT {
		$macro_primitive_comment = $APERTURE_COMMENT_CONTENT;
	}

macro_primitive_circle:
	APERTURE_PRIMITIVE_TYPE_CIRCLE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[diameter] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_circle = (MacroPrimitiveCircle*)calloc(1, sizeof(MacroPrimitiveCircle));
		$macro_primitive_circle->exposure = $exposure;
		$macro_primitive_circle->diameter = $diameter;
		$macro_primitive_circle->center_x = $[center_x];
		$macro_primitive_circle->center_y = $[center_y];
		$macro_primitive_circle->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_CIRCLE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[diameter] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] {
		$macro_primitive_circle = (MacroPrimitiveCircle*)calloc(1, sizeof(MacroPrimitiveCircle));
		$macro_primitive_circle->exposure = $exposure;
		$macro_primitive_circle->diameter = $diameter;
		$macro_primitive_circle->center_x = $[center_x];
		$macro_primitive_circle->center_y = $[center_y];
		$macro_primitive_circle->rotation = NULL;
	}

macro_primitive_vector_line:
	APERTURE_PRIMITIVE_TYPE_VECTOR_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[line_width] AM_DELIM arithmetic_expression[start_x] AM_DELIM arithmetic_expression[start_y] AM_DELIM arithmetic_expression[end_x] AM_DELIM arithmetic_expression[end_y] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_vector_line = (MacroPrimitiveVectorLine*)calloc(1, sizeof(MacroPrimitiveVectorLine));
		$macro_primitive_vector_line->exposure = $exposure;
		$macro_primitive_vector_line->line_width = $[line_width];
		$macro_primitive_vector_line->start_x = $[start_x];
		$macro_primitive_vector_line->start_y = $[start_y];
		$macro_primitive_vector_line->end_x = $[end_x];
		$macro_primitive_vector_line->end_y = $[end_y];
		$macro_primitive_vector_line->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_VECTOR_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[line_width] AM_DELIM arithmetic_expression[start_x] AM_DELIM arithmetic_expression[start_y] AM_DELIM arithmetic_expression[end_x] AM_DELIM arithmetic_expression[end_y] {
		$macro_primitive_vector_line = (MacroPrimitiveVectorLine*)calloc(1, sizeof(MacroPrimitiveVectorLine));
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
		$macro_primitive_center_line = (MacroPrimitiveCenterLine*)calloc(1, sizeof(MacroPrimitiveCenterLine));
		$macro_primitive_center_line->exposure = $exposure;
		$macro_primitive_center_line->rect_width = $[rect_width];
		$macro_primitive_center_line->rect_height = $[rect_height];
		$macro_primitive_center_line->center_x = $[center_x];
		$macro_primitive_center_line->center_y = $[center_y];
		$macro_primitive_center_line->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_CENTER_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[rect_width] AM_DELIM arithmetic_expression[rect_height] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] {
		$macro_primitive_center_line = (MacroPrimitiveCenterLine*)calloc(1, sizeof(MacroPrimitiveCenterLine));
		$macro_primitive_center_line->exposure = $exposure;
		$macro_primitive_center_line->rect_width = $[rect_width];
		$macro_primitive_center_line->rect_height = $[rect_height];
		$macro_primitive_center_line->center_x = $[center_x];
		$macro_primitive_center_line->center_y = $[center_y];
		$macro_primitive_center_line->rotation = NULL;
	}

macro_primitive_outline:
	APERTURE_PRIMITIVE_TYPE_OUTLINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_points] expression_coord_list[coords] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_outline = (MacroPrimitiveOutline*)calloc(1, sizeof(MacroPrimitiveOutline));
		$macro_primitive_outline->exposure = $exposure;
		$macro_primitive_outline->num_points = $[num_points];
		$macro_primitive_outline->coords = $coords;
		$macro_primitive_outline->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_OUTLINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_points] expression_coord_list[coords] {
		$macro_primitive_outline = (MacroPrimitiveOutline*)calloc(1, sizeof(MacroPrimitiveOutline));
		$macro_primitive_outline->exposure = $exposure;
		$macro_primitive_outline->num_points = $[num_points];
		$macro_primitive_outline->coords = $coords;
		$macro_primitive_outline->rotation = NULL;
	}

macro_primitive_polygon:
	APERTURE_PRIMITIVE_TYPE_POLYGON AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_vertices] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[diameter] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_polygon = (MacroPrimitivePolygon*)calloc(1, sizeof(MacroPrimitivePolygon));
		$macro_primitive_polygon->exposure = $exposure;
		$macro_primitive_polygon->num_vertices = $[num_vertices];
		$macro_primitive_polygon->center_x = $[center_x];
		$macro_primitive_polygon->center_y = $[center_y];
		$macro_primitive_polygon->diameter = $diameter;
		$macro_primitive_polygon->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_POLYGON AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_vertices] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[diameter] {
		$macro_primitive_polygon = (MacroPrimitivePolygon*)calloc(1, sizeof(MacroPrimitivePolygon));
		$macro_primitive_polygon->exposure = $exposure;
		$macro_primitive_polygon->num_vertices = $[num_vertices];
		$macro_primitive_polygon->center_x = $[center_x];
		$macro_primitive_polygon->center_y = $[center_y];
		$macro_primitive_polygon->diameter = $diameter;
		$macro_primitive_polygon->rotation = NULL;
	}

macro_primitive_moire:
	APERTURE_PRIMITIVE_TYPE_MOIRE AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[ring_thickness] AM_DELIM arithmetic_expression[ring_gap] AM_DELIM arithmetic_expression[max_rings] AM_DELIM arithmetic_expression[crosshair_thickness] AM_DELIM arithmetic_expression[crosshair_length] AM_DELIM arithmetic_expression[rotation] {
		$macro_primitive_moire = (MacroPrimitiveMoire*)calloc(1, sizeof(MacroPrimitiveMoire));
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
		$macro_primitive_moire = (MacroPrimitiveMoire*)calloc(1, sizeof(MacroPrimitiveMoire));
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
		$macro_primitive_thermal = (MacroPrimitiveThermal*)calloc(1, sizeof(MacroPrimitiveThermal));
		$macro_primitive_thermal->center_x = $[center_x];
		$macro_primitive_thermal->center_y = $[center_y];
		$macro_primitive_thermal->outer_diameter = $[outer_diameter];
		$macro_primitive_thermal->inner_diameter = $[inner_diameter];
		$macro_primitive_thermal->gap_thickness = $[gap_thickness];
		$macro_primitive_thermal->rotation = $rotation;
	}
|	APERTURE_PRIMITIVE_TYPE_THERMAL AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[inner_diameter] AM_DELIM arithmetic_expression[gap_thickness] {
		$macro_primitive_thermal = (MacroPrimitiveThermal*)calloc(1, sizeof(MacroPrimitiveThermal));
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
		$result = (ExpressionCoordList*)calloc(1, sizeof(ExpressionCoordList));
		$result->head = $[new_elem];
		$result->tail = $[new_elem];
	}

expression_coord:
	AM_DELIM arithmetic_expression[coord_x] AM_DELIM arithmetic_expression[coord_y] {
		$expression_coord = (ExpressionCoord*)calloc(1, sizeof(ExpressionCoord));
		$expression_coord->coord_x = $[coord_x];
		$expression_coord->coord_y = $[coord_y];
		$expression_coord->next = NULL;
	}

variable_definition:
	VARIABLE_DEFINITION arithmetic_expression END_OF_DATA_BLOCK {
		$variable_definition = (VariableDefinition*)calloc(1, sizeof(VariableDefinition));
		$variable_definition->variable_number = $VARIABLE_DEFINITION;
		$variable_definition->expression = $arithmetic_expression;
	}
*/

arithmetic_expression[result]:
	ARITHMETIC_CONSTANT {
		$result = make_shared<ConstantAritmeticExpressionElement>($[ARITHMETIC_CONSTANT]);
	}
/*
|	ARITHMETIC_VAR_REFERENCE {
		$result = (ArithmeticExpressionTreeElement*)calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_VARIABLE;
		$result->element.variable = $ARITHMETIC_VAR_REFERENCE;
		$result->left = NULL;
		$result->right = NULL;
	}
|	arithmetic_expression[left] ARITHMETIC_ADD arithmetic_expression[right] {
		$result = (ArithmeticExpressionTreeElement*)calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_ADD;
		$result->left = $left;
		$result->right = $right;
	}
|	arithmetic_expression[left] ARITHMETIC_SUB arithmetic_expression[right] {
		$result = (ArithmeticExpressionTreeElement*)calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_SUB;
		$result->left = $left;
		$result->right = $right;
	}
|	ARITHMETIC_SUB arithmetic_expression[right] %prec UNARY_MINUS {
		$result = (ArithmeticExpressionTreeElement*)calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_SUB;
		$result->left = (ArithmeticExpressionTreeElement*)calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->left->type = EXPRESSION_ELEMENT_TYPE_CONSTANT;
		$result->left->element.constant = 0.0;
		$result->right = $right;
	}
|	arithmetic_expression[left] ARITHMETIC_MULT arithmetic_expression[right] {
		$result = (ArithmeticExpressionTreeElement*)calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_MULT;
		$result->left = $left;
		$result->right = $right;
	}
|	arithmetic_expression[left] ARITHMETIC_DIV arithmetic_expression[right] {
		$result = (ArithmeticExpressionTreeElement*)calloc(1, sizeof(ArithmeticExpressionTreeElement));
		$result->type = EXPRESSION_ELEMENT_TYPE_OPERATOR;
		$result->element.op = OPERATOR_DIV;
		$result->left = $left;
		$result->right = $right;
	}
|	ARITHMETIC_LEFT_PAREN arithmetic_expression[mid] ARITHMETIC_RIGHT_PAREN {
		$result = $mid;
	}
*/

%%

#include "gerber_rs274x_scanner.hh"

static int yylex(yy::GerberRS274XParser::semantic_type* yylval, yy::GerberRS274XParser::location_type* yylloc, GerberRS274XScanner& scanner)
{
	return scanner.yylex(yylval, yylloc);
}

void yy::GerberRS274XParser::error(yy::location const& error_loc, std::string const& message)
{
	std::cerr << message;
}