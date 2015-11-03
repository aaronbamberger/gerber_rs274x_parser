#include "ConstantArithmeticExpressionElement.hh"

#include <iostream>

ConstantArithmeticExpressionElement::ConstantArithmeticExpressionElement(double constant) : m_constant(constant)
{}

ConstantArithmeticExpressionElement::~ConstantArithmeticExpressionElement()
{}

double ConstantArithmeticExpressionElement::do_eval()
{
	return m_constant;
}

std::ostream& ConstantArithmeticExpressionElement::do_print(std::ostream& os) const
{
	os << "Constant: " << m_constant << std::endl;
	return os;
}