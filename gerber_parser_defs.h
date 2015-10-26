#ifndef GERBER_PARSER_DEFS_H
#define GERBER_PARSER_DEFS_H

#include <stdbool.h>

typedef enum {
	OPERATOR_ADD,
	OPERATOR_SUB,
	OPERATOR_MULT,
	OPERATOR_DIV
} Operator;

typedef enum {
	MACRO_PRIMITIVE_TYPE_CIRCLE,
	MACRO_PRIMITIVE_TYPE_VECTOR_LINE,
	MACRO_PRIMITIVE_TYPE_CENTER_LINE,
	MACRO_PRIMITIVE_TYPE_OUTLINE,
	MACRO_PRIMITIVE_TYPE_POLYGON,
	MACRO_PRIMITIVE_TYPE_MOIRE,
	MACRO_PRIMITIVE_TYPE_THERMAL,
	MACRO_PRIMITIVE_TYPE_COMMENT
} MacroPrimitiveType;

typedef enum {
	EXPRESSION_ELEMENT_TYPE_CONSTANT,
	EXPRESSION_ELEMENT_TYPE_VARIABLE,
	EXPRESSION_ELEMENT_TYPE_OPERATOR
} ArithmeticExpressionElementType;

typedef enum {
	MACRO_CONTENT_VAR_DEF,
	MACRO_CONTENT_PRIMITIVE
} MacroContentType;

typedef enum {
	D_CODE_INTERPOLATE,
	D_CODE_MOVE,
	D_CODE_FLASH
} DCodeType;

typedef enum {
	G_CODE_LINEAR_INTERP_MODE,
	G_CODE_CW_CIRCULAR_INTERP_MODE,
	G_CODE_CCW_CIRCULAR_INTERP_MODE,
	G_CODE_SINGLE_QUADRANT_MODE,
	G_CODE_MULTI_QUADRANT_MODE,
	G_CODE_REGION_MODE_ON,
	G_CODE_REGION_MODE_OFF
} GCodeType;

typedef enum {
	COMMAND_TYPE_D_CODE,
	COMMAND_TYPE_SELECT_APERTURE,
	COMMAND_TYPE_G_CODE,
	COMMAND_TYPE_COMMENT,
	COMMAND_TYPE_END_OF_FILE,
	COMMAND_TYPE_FORMAT_SPECIFIER,
	COMMAND_TYPE_UNITS,
	COMMAND_TYPE_APERTURE_DEFINITION,
	COMMAND_TYPE_APERTURE_MACRO,
	COMMAND_TYPE_STEP_AND_REPEAT,
	COMMAND_TYPE_LEVEL_POLARITY
} CommandType;

typedef enum {
	UNIT_TYPE_IN,
	UNIT_TYPE_MM
} UnitType;

typedef enum {
	LEVEL_POLARITY_CLEAR,
	LEVEL_POLARITY_DARK
} LevelPolarity;

typedef enum {
	STANDARD_APERTURE_CIRCLE,
	STANDARD_APERTURE_RECTANGLE,
	STANDARD_APERTURE_OBROUND,
	STANDARD_APERTURE_POLYGON
} StandardApertureType;

typedef enum {
	APERTURE_DEFINITION_TYPE_STANDARD,
	APERTURE_DEFINITION_TYPE_CUSTOM
} ApertureDefinitionType;

typedef union {
	double constant;
	int variable;
	Operator op;
} ArithmeticExpressionElement;

typedef struct _ArithmeticExpressionTreeElement {
	ArithmeticExpressionElementType type;
	ArithmeticExpressionElement element;
	struct _ArithmeticExpressionTreeElement* left;
	struct _ArithmeticExpressionTreeElement* right;
} ArithmeticExpressionTreeElement;

typedef struct {
	int variable_number;
	ArithmeticExpressionTreeElement* expression;
} VariableDefinition;

typedef struct {
	ArithmeticExpressionTreeElement* exposure;
	ArithmeticExpressionTreeElement* diameter;
	ArithmeticExpressionTreeElement* center_x;
	ArithmeticExpressionTreeElement* center_y;
	ArithmeticExpressionTreeElement* rotation;
} MacroPrimitiveCircle;

typedef struct {
	ArithmeticExpressionTreeElement* exposure;
	ArithmeticExpressionTreeElement* line_width;
	ArithmeticExpressionTreeElement* start_x;
	ArithmeticExpressionTreeElement* start_y;
	ArithmeticExpressionTreeElement* end_x;
	ArithmeticExpressionTreeElement* end_y;
	ArithmeticExpressionTreeElement* rotation;
} MacroPrimitiveVectorLine;

typedef struct {
	ArithmeticExpressionTreeElement* exposure;
	ArithmeticExpressionTreeElement* rect_width;
	ArithmeticExpressionTreeElement* rect_height;
	ArithmeticExpressionTreeElement* center_x;
	ArithmeticExpressionTreeElement* center_y;
	ArithmeticExpressionTreeElement* rotation;
} MacroPrimitiveCenterLine;

typedef struct _ExpressionCoord {
	struct _ExpressionCoord* next;
	ArithmeticExpressionTreeElement* coord_x;
	ArithmeticExpressionTreeElement* coord_y;
} ExpressionCoord;

typedef struct {
	ExpressionCoord* head;
	ExpressionCoord* tail;
} ExpressionCoordList;

typedef struct {
	ArithmeticExpressionTreeElement* exposure;
	ArithmeticExpressionTreeElement* num_points;
	ExpressionCoordList* coords;
	ArithmeticExpressionTreeElement* rotation;
} MacroPrimitiveOutline;

typedef struct {
	ArithmeticExpressionTreeElement* exposure;
	ArithmeticExpressionTreeElement* num_vertices;
	ArithmeticExpressionTreeElement* center_x;
	ArithmeticExpressionTreeElement* center_y;
	ArithmeticExpressionTreeElement* diameter;
	ArithmeticExpressionTreeElement* rotation;
} MacroPrimitivePolygon;

typedef struct {
	ArithmeticExpressionTreeElement* center_x;
	ArithmeticExpressionTreeElement* center_y;
	ArithmeticExpressionTreeElement* outer_diameter;
	ArithmeticExpressionTreeElement* ring_thickness;
	ArithmeticExpressionTreeElement* ring_gap;
	ArithmeticExpressionTreeElement* max_rings;
	ArithmeticExpressionTreeElement* crosshair_thickness;
	ArithmeticExpressionTreeElement* crosshair_length;
	ArithmeticExpressionTreeElement* rotation;
} MacroPrimitiveMoire;

typedef struct {
	ArithmeticExpressionTreeElement* center_x;
	ArithmeticExpressionTreeElement* center_y;
	ArithmeticExpressionTreeElement* outer_diameter;
	ArithmeticExpressionTreeElement* inner_diameter;
	ArithmeticExpressionTreeElement* gap_thickness;
	ArithmeticExpressionTreeElement* rotation;
} MacroPrimitiveThermal;

typedef union {
	MacroPrimitiveCircle* circle;
	MacroPrimitiveVectorLine* vector_line;
	MacroPrimitiveCenterLine* center_line;
	MacroPrimitiveOutline* outline;
	MacroPrimitivePolygon* polygon;
	MacroPrimitiveMoire* moire;
	MacroPrimitiveThermal* thermal;
	const char* comment;
} MacroPrimitiveContents;

typedef struct {
	MacroPrimitiveType type;
	MacroPrimitiveContents primitive;
} MacroPrimitive;

typedef union {
	VariableDefinition* var_def;
	MacroPrimitive* primitive;
} MacroContent;

typedef struct _MacroContentElement {
	struct _MacroContentElement* next;
	MacroContentType type;
	MacroContent content;
} MacroContentElement;

typedef struct {
	MacroContentElement* head;
	MacroContentElement* tail;
} MacroContentList;

typedef struct {
	const char* name;
	MacroContentList* content_list;
} ApertureMacro;

/*
typedef struct {
	int x;
	int y;
	int i;
	int j;
	bool x_valid;
	bool y_valid;
	bool i_valid;
	bool j_valid;
} CoordinateData;

typedef struct {
	DCodeType type;
	CoordinateData* coord_data;
} DCommand;
*/

typedef struct {
	int num_int_positions;
	int num_dec_positions;
} FormatSpecifier;

typedef struct {
	int x_num_repeats;
	int y_num_repeats;
	double x_step_distance;
	double y_step_distance;
} StepAndRepeat;

typedef struct {
	double diameter;
	double hole_diameter;
	bool has_hole;
} StandardApertureCircle;

typedef struct {
	double x_size;
	double y_size;
	double hole_diameter;
	bool has_hole;
} StandardApertureRectangle;

typedef struct {
	double x_size;
	double y_size;
	double hole_diameter;
	bool has_hole;
} StandardApertureObround;

typedef struct {
	double diameter;
	double num_vertices;
	double rotation;
	double hole_diameter;
	bool has_rotation;
	bool has_hole;
} StandardAperturePolygon;

typedef union {
	StandardApertureCircle* circle;
	StandardApertureRectangle* rectangle;
	StandardApertureObround* obround;
	StandardAperturePolygon* polygon;
} StandardApertureContents;

typedef struct {
	StandardApertureType type;
	StandardApertureContents contents;
} StandardAperture;

typedef union {
	StandardAperture* standard;
	const char* custom_name;
} ApertureDefinitionContents;

typedef struct {
	ApertureDefinitionType type;
	int aperture_number;
	ApertureDefinitionContents aperture;
} ApertureDefinition;

/*
typedef union {
	DCommand* d_command;
	int aperture;
	GCodeType g_command;
	const char* comment;
	FormatSpecifier* format_specifier;
	UnitType units;
	ApertureDefinition* aperture_definition; 
	ApertureMacro* aperture_macro;
	StepAndRepeat* step_and_repeat;
	LevelPolarity level_polarity;
} CommandContents;
*/

/*
typedef struct _Command {
	CommandType type;
	CommandContents contents;
	struct _Command* next;
} Command;

typedef struct {
	Command* head;
	Command* tail;
} CommandList;
*/

#endif // GERBER_PARSER_DEFS_H