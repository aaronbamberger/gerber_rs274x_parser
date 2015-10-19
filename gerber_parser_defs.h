#ifndef GERBER_PARSER_DEFS_H
#define GERBER_PARSER_DEFS_H

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

#endif // GERBER_PARSER_DEFS_H