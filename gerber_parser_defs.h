#define STARTING_NUM_VARIABLE_DEFS 2
#define STARTING_NUM_PRIMITIVES 2

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

typedef union {
	double constant;
	int variable;
	Operator op;
} ArithmeticExpressionElement;

typedef struct {
	ArithmeticExpressionElementType type;
	ArithmeticExpressionElement element;
	ArithmeticExpressionTreeElement* left;
	ArithmeticExpressionTreeElement* right;
} ArithmeticExpressionTreeElement;

typedef struct {
	int variable_number;
	ArithmeticExpressionTreeElement* expression;
} VariableDefinition;

typedef struct {
	ArithmeticExpressionTreeElement* exposure;
	ArithmeticExpressionTreeElement* diameter;
	ArithmeticExpressionTreeElement* x_coord;
	ArithmeticExpressionTreeElement* y_coord;
	ArithmeticExpressionTreeElement* rotation;
} MacroPrimitiveCircle;

typedef struct {
	ArithmeticExpressionTreeElement* exposure;
	ArithmeticExpressionTreeElement* line_width;
	ArithmeticExpressionTreeElement* x_start;
	ArithmeticExpressionTreeElement* y_start;
	ArithmeticExpressionTreeElement* x_end;
	ArithmeticExpressionTreeElement* y_end;
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

typedef struct {
	ArithmeticExpressionTreeElement* exposure;
	ArithmeticExpressionTreeElement* num_points;
	ArithmeticExpressionTreeElement** x_coords; // Array of expressions
	ArithmeticExpressionTreeElement** y_coords; // Array of expressions
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
	MacroPrimitiveCircle circle;
	MacroPrimitiveVectorLine vector_line;
	MacroPrimitiveCenterLine center_line;
	MacroPrimitiveOutline outline;
	MacroPrimitivePolygon polygon;
	MacroPrimitiveMoire moire;
	MacroPrimitiveThermal thermal;
	const char* comment;
} MacroPrimitiveContents;

typedef struct {
	MacroPrimitiveType type;
	MacroPrimitiveContents primitive;
} MacroPrimitive;

typedef struct {
	int capacity;
	int length;
	VariableDefinition* defs;
} VariableDefinitionList;

typedef struct {
	int capacity;
	int length;
	MacroPrimitive* primitives;
} MacroPrimitiveList;

typedef struct {
	VariableDefinitionList variable_defs;
	MacroPrimitiveList primitives;
} MacroContent;

typedef struct {
	const char* name;
	MacroContent content;
} ApertureMacro;