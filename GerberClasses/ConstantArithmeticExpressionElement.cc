#include "ConstantArithmeticExpressionElement.hh"
#include "../GraphicsState.hh"

ConstantArithmeticExpressionElement::ConstantArithmeticExpressionElement(double constant) : m_constant(constant)
{}

ConstantArithmeticExpressionElement::~ConstantArithmeticExpressionElement()
{}

double ConstantArithmeticExpressionElement::eval(const GraphicsState& graphics_state)
{
	return m_constant;
}

std::ostream& ConstantArithmeticExpressionElement::do_print(std::ostream& os) const
{
	os << "Constant: " << m_constant << std::endl;
	return os;
}