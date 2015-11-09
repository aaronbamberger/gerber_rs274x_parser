#include "ConstantArithmeticExpressionElement.hh"
#include "ApertureMacroVariableEnvironment.hh"

#include <iostream>

ConstantArithmeticExpressionElement::ConstantArithmeticExpressionElement(double constant) : m_constant(constant)
{}

ConstantArithmeticExpressionElement::~ConstantArithmeticExpressionElement()
{}

double ConstantArithmeticExpressionElement::do_eval(ApertureMacroVariableEnvironment& variable_env)
{
	return m_constant;
}

std::ostream& ConstantArithmeticExpressionElement::do_print(std::ostream& os) const
{
	os << "Constant: " << m_constant << std::endl;
	return os;
}
