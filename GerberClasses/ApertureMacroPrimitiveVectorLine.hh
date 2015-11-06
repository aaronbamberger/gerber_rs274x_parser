#ifndef _APERTURE_MACRO_PRIMITIVE_VECTOR_LINE_H
#define _APERTURE_MACRO_PRIMITIVE_VECTOR_LINE_H

#include "ApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

class ApertureMacroPrimitiveVectorLine : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveVectorLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> line_width,
		std::shared_ptr<ArithmeticExpressionElement> start_x,
		std::shared_ptr<ArithmeticExpressionElement> start_y,
		std::shared_ptr<ArithmeticExpressionElement> end_x,
		std::shared_ptr<ArithmeticExpressionElement> end_y,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitiveVectorLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> line_width,
		std::shared_ptr<ArithmeticExpressionElement> start_x,
		std::shared_ptr<ArithmeticExpressionElement> start_y,
		std::shared_ptr<ArithmeticExpressionElement> end_x,
		std::shared_ptr<ArithmeticExpressionElement> end_y);

	virtual ~ApertureMacroPrimitiveVectorLine();

private:
	std::ostream& do_print(std::ostream& os);

	std::shared_ptr<ArithmeticExpressionElement> m_exposure;
	std::shared_ptr<ArithmeticExpressionElement> m_line_width;
	std::shared_ptr<ArithmeticExpressionElement> m_start_x;
	std::shared_ptr<ArithmeticExpressionElement> m_start_y;
	std::shared_ptr<ArithmeticExpressionElement> m_end_x;
	std::shared_ptr<ArithmeticExpressionElement> m_end_y;
	std::shared_ptr<ArithmeticExpressionElement> m_rotation;
};

#endif // _APERTURE_MACRO_PRIMITIVE_VECTOR_LINE_H