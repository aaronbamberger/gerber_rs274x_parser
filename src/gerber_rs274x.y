%code requires {
	#include "CommandList.hh"
	#include "Commands/Command.hh"
	#include "Commands/DCommand.hh"
	#include "Commands/GCommand.hh"
	#include "CoordinateData.hh"
	#include "Commands/SelectApertureCommand.hh"
	#include "ApertureMacros/ConstantArithmeticExpressionElement.hh"
	#include "ApertureMacros/VariableReferenceArithmeticExpressionElement.hh"
	#include "ApertureMacros/BinaryOperationArithmeticExpressionElement.hh"
	#include "Commands/ApertureMacro.hh"
	#include "ApertureMacros/ApertureMacroContent.hh"
	#include "ApertureMacros/ApertureMacroVariableDefinition.hh"
	#include "ApertureMacros/ApertureMacroPrimitive.hh"
	#include "ApertureMacros/ApertureMacroPrimitiveCircle.hh"
	#include "ApertureMacros/ApertureMacroPrimitiveVectorLine.hh"
	#include "ApertureMacros/ApertureMacroPrimitiveCenterLine.hh"
	#include "ApertureMacros/ApertureMacroPrimitiveOutline.hh"
	#include "ApertureMacros/ApertureMacroPrimitivePolygon.hh"
	#include "ApertureMacros/ApertureMacroPrimitiveMoire.hh"
	#include "ApertureMacros/ApertureMacroPrimitiveThermal.hh"
	#include "ApertureMacros/ApertureMacroPrimitiveComment.hh"
	#include "Apertures/StandardAperture.hh"
	#include "Apertures/StandardApertureCircle.hh"
	#include "Apertures/StandardApertureRectangle.hh"
	#include "Apertures/StandardApertureObround.hh"
	#include "Apertures/StandardAperturePolygon.hh"
	#include "Commands/ApertureDefinition.hh"
	#include "Commands/ApertureDefinitionStandard.hh"
	#include "Commands/ApertureDefinitionCustom.hh"
	#include "Commands/LevelPolarity.hh"
	#include "Commands/UnitSpecifier.hh"
	#include "Commands/StepAndRepeat.hh"
	#include "Commands/FormatSpecifier.hh"
	#include "Commands/Comment.hh"
	#include "Commands/EndOfFile.hh"
	#include "Point.hh"
    #include "GlobalDefs.hh"
    #include "Commands/ApertureDefinitionModifier.hh"
	#include "Util/ValueWithLocation.hh"
	#include "Attributes/PartAttribute.hh"
	#include "Attributes/FileFunctionAttribute.hh"
	#include "Attributes/FilePolarityAttribute.hh"
	#include "Attributes/SameCoordinatesAttribute.hh"
	#include "Attributes/CreationDateAttribute.hh"
	#include "Attributes/GenerationSoftwareAttribute.hh"
	#include "Attributes/ProjectIdAttribute.hh"
	#include "Attributes/MD5Attribute.hh"
	#include "Attributes/AperFunctionAttribute.hh"
	#include "Attributes/DrillToleranceAttribute.hh"
	#include "Attributes/FlashTextAttribute.hh"
	#include "Attributes/NetAttribute.hh"
	#include "Attributes/PinNumberAttribute.hh"
	#include "Attributes/PinFunctionAttribute.hh"
	#include "Attributes/ComponentAttribute.hh"


	#include <memory>
	#include <utility>
	#include <list>
    #include <string>

	// Forward declare the scanner class so we can use it in the function prototypes
	class GerberRS274XScanner;
}

%code {
	static int yylex(yy::GerberRS274XParser::semantic_type* yylval, yy::location* yylloc, GerberRS274XScanner& scanner);
}

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
%token <std::string> COMMENT_STRING
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
%token <Gerber::UnitType> UNIT_SPECIFIER
%token END_OF_DATA_BLOCK
%token EXT_CMD_DELIMITER
%token APERTURE_DEFINITION
%token <int> APERTURE_NUMBER
%token STANDARD_APERTURE_TYPE_CIRCLE
%token STANDARD_APERTURE_TYPE_RECTANGLE
%token STANDARD_APERTURE_TYPE_OBROUND
%token STANDARD_APERTURE_TYPE_POLYGON
%token <std::string> CUSTOM_APERTURE_NAME
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
%token <Gerber::LevelPolarityType> LEVEL_POLARITY
%token FILE_ATTRIBUTE
%token APERTURE_ATTRIBUTE
%token OBJECT_ATTRIBUTE
%token DELETE_ATTRIBUTE
%token <std::string> ATTRIBUTE_FIELD_STRING
%token <unsigned long> ATTRIBUTE_FIELD_INT
%token <double> ATTRIBUTE_FIELD_DECIMAL
%token <StandardAttribute::StandardAttributeType> STANDARD_ATTRIBUTE_NAME
%token <std::string> USER_ATTRIBUTE_NAME
%token <PartAttribute::Part> PART_ATTRIBUTE_PART
%token <FileFunctionAttribute::FileFunction> FILE_FUNCTION_ATTRIBUTE_FUNCTION
%token <FileFunctionAttribute::LayerType> FILE_FUNCTION_ATTRIBUTE_LAYER_TYPE
%token <FileFunctionAttribute::CopperType> FILE_FUNCTION_ATTRIBUTE_COPPER_TYPE
%token <FileFunctionAttribute::DrillType> FILE_FUNCTION_ATTRIBUTE_DRILL_TYPE
%token <FileFunctionAttribute::DrillRouteType> FILE_FUNCTION_ATTRIBUTE_DRILL_ROUTE_TYPE
%token <FileFunctionAttribute::EdgePlateType> FILE_FUNCTION_ATTRIBUTE_EDGE_PLATE_TYPE
%token <FilePolarityAttribute::Polarity> FILE_POLARITY_ATTRIBUTE_POLARITY
%token <AperFunctionAttribute::AperFunction> APER_FUNCTION_ATTRIBUTE_FUNCTION
%token <AperFunctionAttribute::ViaDrillType> APER_FUNCTION_ATTRIBUTE_VIA_DRILL_TYPE
%token <AperFunctionAttribute::ComponentDrillType> APER_FUNCTION_ATTRIBUTE_COMPONENT_DRILL_TYPE
%token <AperFunctionAttribute::MechanicalDrillType> APER_FUNCTION_ATTRIBUTE_MECHANICAL_DRILL_TYPE
%token <AperFunctionAttribute::PadDefinitionType> APER_FUNCTION_ATTRIBUTE_PAD_DEFINITION_TYPE
%token <AperFunctionAttribute::FiducialType> APER_FUNCTION_ATTRIBUTE_FIDUCIAL_TYPE
%token <FlashTextAttribute::TextType> FLASH_TEXT_ATTRIBUTE_TEXT_TYPE
%token <FlashTextAttribute::TextOrientation> FLASH_TEXT_ATTRIBUTE_TEXT_ORIENTATION

%left ARITHMETIC_ADD ARITHMETIC_SUB
%left ARITHMETIC_MULT ARITHMETIC_DIV
%precedence UNARY_MINUS

%type <std::shared_ptr<ApertureMacro> > aperture_macro
%type <Point<std::shared_ptr<ArithmeticExpressionElement> > > expression_coord
%type <std::shared_ptr<std::list<Point<std::shared_ptr<ArithmeticExpressionElement> > > > > expression_coord_list
%type <std::shared_ptr<std::list<std::shared_ptr<ApertureMacroContent> > > > macro_content_list
%type <std::shared_ptr<ApertureMacroPrimitive> > macro_primitive
%type <std::shared_ptr<ApertureMacroPrimitiveCircle> > macro_primitive_circle
%type <std::shared_ptr<ApertureMacroPrimitiveVectorLine> > macro_primitive_vector_line
%type <std::shared_ptr<ApertureMacroPrimitiveCenterLine> > macro_primitive_center_line
%type <std::shared_ptr<ApertureMacroPrimitiveOutline> > macro_primitive_outline
%type <std::shared_ptr<ApertureMacroPrimitivePolygon> > macro_primitive_polygon
%type <std::shared_ptr<ApertureMacroPrimitiveMoire> > macro_primitive_moire
%type <std::shared_ptr<ApertureMacroPrimitiveThermal> > macro_primitive_thermal
%type <std::shared_ptr<ApertureMacroPrimitiveComment> > macro_primitive_comment
%type <std::shared_ptr<ArithmeticExpressionElement> > arithmetic_expression
%type <std::shared_ptr<ApertureMacroContent> > macro_content_element
%type <std::shared_ptr<ApertureMacroVariableDefinition> > variable_definition
%type <std::shared_ptr<CoordinateData> > coordinate_data
%type <std::shared_ptr<Command> > interpolate_cmd
%type <std::shared_ptr<Command> > move_cmd
%type <std::shared_ptr<Command> > flash_cmd
%type <std::shared_ptr<StandardAperture> > standard_aperture
%type <std::shared_ptr<StandardApertureCircle> > standard_aperture_circle
%type <std::shared_ptr<StandardApertureRectangle> > standard_aperture_rectangle
%type <std::shared_ptr<StandardApertureObround> > standard_aperture_obround
%type <std::shared_ptr<StandardAperturePolygon> > standard_aperture_polygon
%type <ApertureDefinitionModifier> aperture_definition_modifier_with_location
%type <std::shared_ptr<ApertureDefinition> > aperture_definition
%type <std::shared_ptr<std::list<ApertureDefinitionModifier> > > aperture_definition_modifier_list
%type <std::shared_ptr<FormatSpecifier> > format_specifier
%type <std::shared_ptr<StepAndRepeat> > step_and_repeat
%type <std::shared_ptr<Command> > command
%type <std::shared_ptr<CommandList> > command_list

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
		$command = std::make_shared<SelectApertureCommand>($[APERTURE_NUMBER], @[APERTURE_NUMBER], @command);
	}
|	G_CMD_TYPE_LINEAR_INTERP_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_LINEAR_INTERP_MODE, @command);
	}
|	G_CMD_TYPE_CW_CIRC_INTERP_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_CW_CIRCULAR_INTERP_MODE, @command);
	}
|	G_CMD_TYPE_CCW_CIRC_INTERP_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_CCW_CIRCULAR_INTERP_MODE, @command);
	}
|	G_CMD_TYPE_REGION_MODE_ON END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_REGION_MODE_ON, @command);
	}
|	G_CMD_TYPE_REGION_MODE_OFF END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_REGION_MODE_OFF, @command);
	}
|	G_CMD_TYPE_MULTI_QUADRANT_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_MULTI_QUADRANT_MODE, @command);
	}
|	G_CMD_TYPE_SINGLE_QUADRANT_MODE END_OF_DATA_BLOCK {
		$command = std::make_shared<GCommand>(GCommand::GCommandType::G_COMMAND_SINGLE_QUADRANT_MODE, @command);
	}
|	COMMENT_START COMMENT_STRING END_OF_DATA_BLOCK {
		$command = std::make_shared<Comment>($[COMMENT_STRING], @command);
	}
|	END_OF_FILE END_OF_DATA_BLOCK {
		$command = std::make_shared<EndOfFile>(@command);
	}
|	format_specifier {
		$command = $[format_specifier];
	}
|	EXT_CMD_DELIMITER UNIT_SPECIFIER END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$command = std::make_shared<UnitSpecifier>($[UNIT_SPECIFIER], @command);
	}
|	aperture_definition {
		$command = $[aperture_definition];
	}
|	aperture_macro {
		$command = $[aperture_macro];
	}
|	step_and_repeat {
		$command = $[step_and_repeat];
	}
| 	EXT_CMD_DELIMITER LEVEL_POLARITY END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$command = std::make_shared<LevelPolarity>($[LEVEL_POLARITY], @command);
	}

aperture_definition:
	EXT_CMD_DELIMITER APERTURE_DEFINITION APERTURE_NUMBER standard_aperture END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[aperture_definition] = std::make_shared<ApertureDefinitionStandard>($[APERTURE_NUMBER], $[standard_aperture],
            @[APERTURE_NUMBER], @[aperture_definition]);
	}
|	EXT_CMD_DELIMITER APERTURE_DEFINITION APERTURE_NUMBER CUSTOM_APERTURE_NAME aperture_definition_modifier_list END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[aperture_definition] = std::make_shared<ApertureDefinitionCustom>($[APERTURE_NUMBER], $[CUSTOM_APERTURE_NAME], $[aperture_definition_modifier_list],
		    @[APERTURE_NUMBER], @[CUSTOM_APERTURE_NAME], @[aperture_definition_modifier_list], @[aperture_definition]);
	}
|	EXT_CMD_DELIMITER APERTURE_DEFINITION APERTURE_NUMBER CUSTOM_APERTURE_NAME END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[aperture_definition] = std::make_shared<ApertureDefinitionCustom>($[APERTURE_NUMBER], $[CUSTOM_APERTURE_NAME],
            @[APERTURE_NUMBER], @[CUSTOM_APERTURE_NAME], @[aperture_definition]);
	}

aperture_definition_modifier_list[result]:
	aperture_definition_modifier_list[list] aperture_definition_modifier_with_location[new_elem] {
		$list->push_back($[new_elem]);
		$result = $list;
	}
|	aperture_definition_modifier_with_location[new_elem] {
		$result = std::make_shared<std::list<ApertureDefinitionModifier> >();
		$result->push_back($[new_elem]);
	}

aperture_definition_modifier_with_location[result]:
    APERTURE_DEFINITION_MODIFIER[modifier] {
        $result = ApertureDefinitionModifier($modifier, @modifier);
    }

standard_aperture:
	standard_aperture_circle {
		$[standard_aperture] = $[standard_aperture_circle];
	}
|	standard_aperture_rectangle {
		$[standard_aperture] = $[standard_aperture_rectangle];
	}
|	standard_aperture_obround {
		$[standard_aperture] = $[standard_aperture_obround];
	}
|	standard_aperture_polygon {
		$[standard_aperture] = $[standard_aperture_polygon];
	}

standard_aperture_circle:
	STANDARD_APERTURE_TYPE_CIRCLE APERTURE_DEFINITION_MODIFIER[diameter] APERTURE_DEFINITION_MODIFIER[hole_diameter] {
		$[standard_aperture_circle] = std::make_shared<StandardApertureCircle>($diameter, $[hole_diameter],
            @diameter, @[hole_diameter], @[standard_aperture_circle]);
	}
|	STANDARD_APERTURE_TYPE_CIRCLE APERTURE_DEFINITION_MODIFIER[diameter] {
		$[standard_aperture_circle] = std::make_shared<StandardApertureCircle>($diameter, @diameter,
            @[standard_aperture_circle]);
	}

standard_aperture_rectangle:
	STANDARD_APERTURE_TYPE_RECTANGLE APERTURE_DEFINITION_MODIFIER[x_size] APERTURE_DEFINITION_MODIFIER[y_size] APERTURE_DEFINITION_MODIFIER[hole_diameter] {
		$[standard_aperture_rectangle] = std::make_shared<StandardApertureRectangle>($[x_size], $[y_size], $[hole_diameter],
            @[x_size], @[y_size], @[hole_diameter], @[standard_aperture_rectangle]);
	}
|	STANDARD_APERTURE_TYPE_RECTANGLE APERTURE_DEFINITION_MODIFIER[x_size] APERTURE_DEFINITION_MODIFIER[y_size] {
		$[standard_aperture_rectangle] = std::make_shared<StandardApertureRectangle>($[x_size], $[y_size],
            @[x_size], @[y_size], @[standard_aperture_rectangle]);
	}

standard_aperture_obround:
	STANDARD_APERTURE_TYPE_OBROUND APERTURE_DEFINITION_MODIFIER[x_size] APERTURE_DEFINITION_MODIFIER[y_size] APERTURE_DEFINITION_MODIFIER[hole_diameter] {
		$[standard_aperture_obround] = std::make_shared<StandardApertureObround>($[x_size], $[y_size], $[hole_diameter],
            @[x_size], @[y_size], @[hole_diameter], @[standard_aperture_obround]);
	}
|	STANDARD_APERTURE_TYPE_OBROUND APERTURE_DEFINITION_MODIFIER[x_size] APERTURE_DEFINITION_MODIFIER[y_size] {
		$[standard_aperture_obround] = std::make_shared<StandardApertureObround>($[x_size], $[y_size],
            @[x_size], @[y_size], @[standard_aperture_obround]);
	}

standard_aperture_polygon:
	STANDARD_APERTURE_TYPE_POLYGON APERTURE_DEFINITION_MODIFIER[diameter] APERTURE_DEFINITION_MODIFIER[num_vertices] APERTURE_DEFINITION_MODIFIER[rotation] APERTURE_DEFINITION_MODIFIER[hole_diameter] {
		$[standard_aperture_polygon] = std::make_shared<StandardAperturePolygon>($diameter, $[num_vertices], $rotation, $[hole_diameter],
            @diameter, @[num_vertices], @rotation, @[hole_diameter], @[standard_aperture_polygon]);
	}
|	STANDARD_APERTURE_TYPE_POLYGON APERTURE_DEFINITION_MODIFIER[diameter] APERTURE_DEFINITION_MODIFIER[num_vertices] APERTURE_DEFINITION_MODIFIER[rotation] {
		$[standard_aperture_polygon] = std::make_shared<StandardAperturePolygon>($diameter, $[num_vertices], $rotation,
            @diameter, @[num_vertices], @rotation, @[standard_aperture_polygon]);
	}
|	STANDARD_APERTURE_TYPE_POLYGON APERTURE_DEFINITION_MODIFIER[diameter] APERTURE_DEFINITION_MODIFIER[num_vertices] {
		$[standard_aperture_polygon] = std::make_shared<StandardAperturePolygon>($diameter, $[num_vertices],
            @diameter, @[num_vertices], @[standard_aperture_polygon]);
	}

step_and_repeat:
	EXT_CMD_DELIMITER STEP_AND_REPEAT_START X_REPEATS Y_REPEATS X_STEP_DISTANCE Y_STEP_DISTANCE END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[step_and_repeat] = std::make_shared<StepAndRepeat>($[X_REPEATS], $[Y_REPEATS], $[X_STEP_DISTANCE], $[Y_STEP_DISTANCE],
            @[X_REPEATS], @[Y_REPEATS], @[X_STEP_DISTANCE], @[Y_STEP_DISTANCE], @[step_and_repeat]);
	}
|	EXT_CMD_DELIMITER STEP_AND_REPEAT_START END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[step_and_repeat] = std::make_shared<StepAndRepeat>(@[step_and_repeat]);
	}

format_specifier:
	EXT_CMD_DELIMITER COORD_FORMAT COORD_FORMAT_NUM_INT_POSITIONS[x_int_positions] COORD_FORMAT_NUM_DEC_POSITIONS[x_dec_positions] COORD_FORMAT_NUM_INT_POSITIONS[y_int_positions] COORD_FORMAT_NUM_DEC_POSITIONS[y_dec_positions] END_OF_DATA_BLOCK EXT_CMD_DELIMITER {
		$[format_specifier] = std::make_shared<FormatSpecifier>($[x_int_positions], $[x_dec_positions], $[y_int_positions], $[y_dec_positions],
            @[x_int_positions], @[x_dec_positions], @[y_int_positions], @[y_dec_positions], @[format_specifier]);
	}

interpolate_cmd:
	coordinate_data D_CMD_TYPE_INTERPOLATE END_OF_DATA_BLOCK {
		$[interpolate_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_INTERPOLATE,
            $[coordinate_data], @[interpolate_cmd]);
	}
|	D_CMD_TYPE_INTERPOLATE END_OF_DATA_BLOCK {
		$[interpolate_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_INTERPOLATE,
            @[interpolate_cmd]);
	}

move_cmd:
	coordinate_data D_CMD_TYPE_MOVE END_OF_DATA_BLOCK {
		$[move_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_MOVE,
            $[coordinate_data], @[move_cmd]);
	}
|	D_CMD_TYPE_MOVE END_OF_DATA_BLOCK {
		$[move_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_MOVE,
		    @[move_cmd]);
	}

flash_cmd:
	coordinate_data D_CMD_TYPE_FLASH END_OF_DATA_BLOCK {
		$[flash_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_FLASH,
            $[coordinate_data], @[flash_cmd]);
	}
|	D_CMD_TYPE_FLASH END_OF_DATA_BLOCK {
		$[flash_cmd] = std::make_shared<DCommand>(DCommand::DCommandType::D_COMMAND_FLASH,
            @[flash_cmd]);
	}

coordinate_data:
	X_COORDINATE {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], 0, 0, 0,
            true, false, false, false,
		    @[X_COORDINATE], yy::location(), yy::location(), yy::location());
	}
|	Y_COORDINATE {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, $[Y_COORDINATE], 0, 0,
            false, true, false, false,
            yy::location(), @[Y_COORDINATE], yy::location(), yy::location());
	}
|	X_COORDINATE Y_COORDINATE {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], $[Y_COORDINATE], 0, 0,
            true, true, false, false,
            @[X_COORDINATE], @[Y_COORDINATE], yy::location(), yy::location());
	}
|	I_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, 0, $[I_OFFSET], 0,
            false, false, true, false,
            yy::location(), yy::location(), @[I_OFFSET], yy::location());
	}
|	X_COORDINATE I_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], 0, $[I_OFFSET], 0,
            true, false, true, false,
            @[X_COORDINATE], yy::location(), @[I_OFFSET], yy::location());
	}
|	Y_COORDINATE I_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, $[Y_COORDINATE], $[I_OFFSET], 0,
            false, true, true, false,
            yy::location(), @[Y_COORDINATE], @[I_OFFSET], yy::location());
	}
|	X_COORDINATE Y_COORDINATE I_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], $[Y_COORDINATE], $[I_OFFSET],
            0, true, true, true, false,
            @[X_COORDINATE], @[Y_COORDINATE], @[I_OFFSET], yy::location());
	}
|	J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, 0, 0, $[J_OFFSET],
            false, false, false, true,
            yy::location(), yy::location(), yy::location(), @[J_OFFSET]);
	}
|	X_COORDINATE J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], 0, 0, $[J_OFFSET],
            true, false, false, true,
            @[X_COORDINATE], yy::location(), yy::location(), @[J_OFFSET]);
	}
|	Y_COORDINATE J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, $[Y_COORDINATE], 0, $[J_OFFSET],
            false, true, false, true,
            yy::location(), @[Y_COORDINATE], yy::location(), @[J_OFFSET]);
	}
|	X_COORDINATE Y_COORDINATE J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], $[Y_COORDINATE], 0, $[J_OFFSET],
            true, true, false, true,
            @[X_COORDINATE], @[Y_COORDINATE], yy::location(), @[J_OFFSET]);
	}
|	I_OFFSET J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, 0, $[I_OFFSET], $[J_OFFSET],
            false, false, true, true,
            yy::location(), yy::location(), @[I_OFFSET], @[J_OFFSET]);
	}
|	X_COORDINATE I_OFFSET J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], 0, $[I_OFFSET], $[J_OFFSET],
            true, false, true, true,
            @[X_COORDINATE], yy::location(), @[I_OFFSET], @[J_OFFSET]);
	}
|	Y_COORDINATE I_OFFSET J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>(0, $[Y_COORDINATE], $[I_OFFSET], $[J_OFFSET],
            false, true, true, true,
            yy::location(), @[Y_COORDINATE], @[I_OFFSET], @[J_OFFSET]);
	}
|	X_COORDINATE Y_COORDINATE I_OFFSET J_OFFSET {
		$[coordinate_data] = std::make_shared<CoordinateData>($[X_COORDINATE], $[Y_COORDINATE], $[I_OFFSET], $[J_OFFSET],
            true, true, true, true,
            @[X_COORDINATE], @[Y_COORDINATE], @[I_OFFSET], @[J_OFFSET]);
	}

aperture_macro:
	EXT_CMD_DELIMITER APERTURE_MACRO CUSTOM_APERTURE_NAME END_OF_DATA_BLOCK macro_content_list EXT_CMD_DELIMITER {
		$[aperture_macro] = std::make_shared<ApertureMacro>($[CUSTOM_APERTURE_NAME], $[macro_content_list], @[aperture_macro]);
	}

macro_content_list[result]:
	macro_content_list[list] macro_content_element[new_elem] {
		$list->push_back($[new_elem]);
		$result = $list;
	}
|	macro_content_element[new_elem] {
		$result = std::make_shared<std::list<std::shared_ptr<ApertureMacroContent> > >();
		$result->push_back($[new_elem]);
	}

macro_content_element:
	variable_definition {
		$[macro_content_element] = $[variable_definition];
	}
|	macro_primitive {
		$[macro_content_element] = $[macro_primitive];
	}

macro_primitive:
	macro_primitive_comment END_OF_DATA_BLOCK {
		$[macro_primitive] = $[macro_primitive_comment];
	}
|	macro_primitive_circle END_OF_DATA_BLOCK {
		$[macro_primitive] = $[macro_primitive_circle];
	}
|	macro_primitive_vector_line END_OF_DATA_BLOCK {
		$[macro_primitive] = $[macro_primitive_vector_line];
	}
|	macro_primitive_center_line END_OF_DATA_BLOCK {
		$[macro_primitive] = $[macro_primitive_center_line];
	}
|	macro_primitive_outline END_OF_DATA_BLOCK {
		$[macro_primitive] = $[macro_primitive_outline];
	}
|	macro_primitive_polygon END_OF_DATA_BLOCK {
		$[macro_primitive] = $[macro_primitive_polygon];
	}
|	macro_primitive_moire END_OF_DATA_BLOCK {
		$[macro_primitive] = $[macro_primitive_moire];
	}
|	macro_primitive_thermal END_OF_DATA_BLOCK {
		$[macro_primitive] = $[macro_primitive_thermal];
	}

macro_primitive_comment:
	APERTURE_COMMENT_START APERTURE_COMMENT_CONTENT {
		$[macro_primitive_comment] = std::make_shared<ApertureMacroPrimitiveComment>($[APERTURE_COMMENT_CONTENT]);
	}

macro_primitive_circle:
	APERTURE_PRIMITIVE_TYPE_CIRCLE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[diameter] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[rotation] {
		$[macro_primitive_circle] = std::make_shared<ApertureMacroPrimitiveCircle>($exposure, $diameter, $[center_x], $[center_y], $rotation);
	}
|	APERTURE_PRIMITIVE_TYPE_CIRCLE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[diameter] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] {
		$[macro_primitive_circle] = std::make_shared<ApertureMacroPrimitiveCircle>($exposure, $diameter, $[center_x], $[center_y]);
	}

macro_primitive_vector_line:
	APERTURE_PRIMITIVE_TYPE_VECTOR_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[line_width] AM_DELIM arithmetic_expression[start_x] AM_DELIM arithmetic_expression[start_y] AM_DELIM arithmetic_expression[end_x] AM_DELIM arithmetic_expression[end_y] AM_DELIM arithmetic_expression[rotation] {
		$[macro_primitive_vector_line] = std::make_shared<ApertureMacroPrimitiveVectorLine>($exposure, $[line_width], $[start_x], $[start_y], $[end_x], $[end_y], $rotation);
	}
|	APERTURE_PRIMITIVE_TYPE_VECTOR_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[line_width] AM_DELIM arithmetic_expression[start_x] AM_DELIM arithmetic_expression[start_y] AM_DELIM arithmetic_expression[end_x] AM_DELIM arithmetic_expression[end_y] {
		$[macro_primitive_vector_line] = std::make_shared<ApertureMacroPrimitiveVectorLine>($exposure, $[line_width], $[start_x], $[start_y], $[end_x], $[end_y]);
	}

macro_primitive_center_line:
	APERTURE_PRIMITIVE_TYPE_CENTER_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[rect_width] AM_DELIM arithmetic_expression[rect_height] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[rotation] {
		$[macro_primitive_center_line] = std::make_shared<ApertureMacroPrimitiveCenterLine>($exposure, $[rect_width], $[rect_height], $[center_x], $[center_y], $rotation,
            @exposure, @[rect_width], @[rect_height], @[center_x], @[center_y], @rotation, @[macro_primitive_center_line]);
	}
|	APERTURE_PRIMITIVE_TYPE_CENTER_LINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[rect_width] AM_DELIM arithmetic_expression[rect_height] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] {
		$[macro_primitive_center_line] = std::make_shared<ApertureMacroPrimitiveCenterLine>($exposure, $[rect_width], $[rect_height], $[center_x], $[center_y],
            @exposure, @[rect_width], @[rect_height], @[center_x], @[center_y], @[macro_primitive_center_line]);
	}

macro_primitive_outline:
	APERTURE_PRIMITIVE_TYPE_OUTLINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_points] expression_coord_list[coords] AM_DELIM arithmetic_expression[rotation] {
		$[macro_primitive_outline] = std::make_shared<ApertureMacroPrimitiveOutline>($exposure, $[num_points], $coords, $rotation);
	}
|	APERTURE_PRIMITIVE_TYPE_OUTLINE AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_points] expression_coord_list[coords] {
		$[macro_primitive_outline] = std::make_shared<ApertureMacroPrimitiveOutline>($exposure, $[num_points], $coords);
	}

macro_primitive_polygon:
	APERTURE_PRIMITIVE_TYPE_POLYGON AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_vertices] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[diameter] AM_DELIM arithmetic_expression[rotation] {
		$[macro_primitive_polygon] = std::make_shared<ApertureMacroPrimitivePolygon>($exposure, $[num_vertices], $[center_x], $[center_y], $diameter, $rotation);
	}
|	APERTURE_PRIMITIVE_TYPE_POLYGON AM_DELIM arithmetic_expression[exposure] AM_DELIM arithmetic_expression[num_vertices] AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[diameter] {
		$[macro_primitive_polygon] = std::make_shared<ApertureMacroPrimitivePolygon>($exposure, $[num_vertices], $[center_x], $[center_y], $diameter);
	}

macro_primitive_moire:
	APERTURE_PRIMITIVE_TYPE_MOIRE AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[ring_thickness] AM_DELIM arithmetic_expression[ring_gap] AM_DELIM arithmetic_expression[max_rings] AM_DELIM arithmetic_expression[crosshair_thickness] AM_DELIM arithmetic_expression[crosshair_length] AM_DELIM arithmetic_expression[rotation] {
		$[macro_primitive_moire] = std::make_shared<ApertureMacroPrimitiveMoire>($[center_x], $[center_y], $[outer_diameter], $[ring_thickness], $[ring_gap], $[max_rings], $[crosshair_thickness], $[crosshair_length], $rotation);
	}
|	APERTURE_PRIMITIVE_TYPE_MOIRE AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[ring_thickness] AM_DELIM arithmetic_expression[ring_gap] AM_DELIM arithmetic_expression[max_rings] AM_DELIM arithmetic_expression[crosshair_thickness] AM_DELIM arithmetic_expression[crosshair_length] {
		$[macro_primitive_moire] = std::make_shared<ApertureMacroPrimitiveMoire>($[center_x], $[center_y], $[outer_diameter], $[ring_thickness], $[ring_gap], $[max_rings], $[crosshair_thickness], $[crosshair_length]);
	}

macro_primitive_thermal:
	APERTURE_PRIMITIVE_TYPE_THERMAL AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[inner_diameter] AM_DELIM arithmetic_expression[gap_thickness] AM_DELIM arithmetic_expression[rotation] {
		$[macro_primitive_thermal] = std::make_shared<ApertureMacroPrimitiveThermal>($[center_x], $[center_y], $[outer_diameter], $[inner_diameter], $[gap_thickness], $rotation);
	}
|	APERTURE_PRIMITIVE_TYPE_THERMAL AM_DELIM arithmetic_expression[center_x] AM_DELIM arithmetic_expression[center_y] AM_DELIM arithmetic_expression[outer_diameter] AM_DELIM arithmetic_expression[inner_diameter] AM_DELIM arithmetic_expression[gap_thickness] {
		$[macro_primitive_thermal] = std::make_shared<ApertureMacroPrimitiveThermal>($[center_x], $[center_y], $[outer_diameter], $[inner_diameter], $[gap_thickness]);
	}

expression_coord_list[result]:
	expression_coord_list[list] expression_coord[new_elem] {
		$list->push_back($[new_elem]);
		$result = $list;
	}
|	expression_coord[new_elem] {
		$result = std::make_shared<std::list<Point<std::shared_ptr<ArithmeticExpressionElement> > > >();
		$result->push_back($[new_elem]);
	}

expression_coord:
	AM_DELIM arithmetic_expression[coord_x] AM_DELIM arithmetic_expression[coord_y] {
		$[expression_coord] = Point<std::shared_ptr<ArithmeticExpressionElement> >($[coord_x], $[coord_y]);
	}

variable_definition:
	VARIABLE_DEFINITION arithmetic_expression END_OF_DATA_BLOCK {
		$[variable_definition] = std::make_shared<ApertureMacroVariableDefinition>($[VARIABLE_DEFINITION], $[arithmetic_expression]);
	}

arithmetic_expression[result]:
	ARITHMETIC_CONSTANT {
		$result = std::make_shared<ConstantArithmeticExpressionElement>($[ARITHMETIC_CONSTANT]);
	}
|	ARITHMETIC_VAR_REFERENCE {
		$result = std::make_shared<VariableReferenceArithmeticExpressionElement>($[ARITHMETIC_VAR_REFERENCE]);
	}
|	arithmetic_expression[left] ARITHMETIC_ADD arithmetic_expression[right] {
		$result = std::make_shared<BinaryOperationArithmeticExpressionElement>(BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_ADD, $left, $right);
	}
|	arithmetic_expression[left] ARITHMETIC_SUB arithmetic_expression[right] {
		$result = std::make_shared<BinaryOperationArithmeticExpressionElement>(BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_SUB, $left, $right);
	}
|	ARITHMETIC_SUB arithmetic_expression[right] %prec UNARY_MINUS {
		auto left = std::make_shared<ConstantArithmeticExpressionElement>(0.0);
		$result = std::make_shared<BinaryOperationArithmeticExpressionElement>(BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_SUB, left, $right);
	}
|	arithmetic_expression[left] ARITHMETIC_MULT arithmetic_expression[right] {
		$result = std::make_shared<BinaryOperationArithmeticExpressionElement>(BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_MULT, $left, $right);
	}
|	arithmetic_expression[left] ARITHMETIC_DIV arithmetic_expression[right] {
		$result = std::make_shared<BinaryOperationArithmeticExpressionElement>(BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_DIV, $left, $right);
	}
|	ARITHMETIC_LEFT_PAREN arithmetic_expression[mid] ARITHMETIC_RIGHT_PAREN {
		$result = $mid;
	}

%%

#include "gerber_rs274x_scanner.hh"

static int yylex(yy::GerberRS274XParser::semantic_type* yylval, yy::location* yylloc, GerberRS274XScanner& scanner)
{
	return scanner.yylex(yylval, yylloc);
}

void yy::GerberRS274XParser::error(yy::location const& error_loc, std::string const& message)
{
	std::cerr << message;
}
