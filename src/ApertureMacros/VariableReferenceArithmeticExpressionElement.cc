#include "ApertureMacros/VariableReferenceArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>

VariableReferenceArithmeticExpressionElement::VariableReferenceArithmeticExpressionElement(int variable_number) : m_variable_number(variable_number)
{}

VariableReferenceArithmeticExpressionElement::~VariableReferenceArithmeticExpressionElement()
{}

double VariableReferenceArithmeticExpressionElement::do_eval(ApertureMacroVariableEnvironment& variable_env)
{
	return variable_env.get_variable(m_variable_number);
}

std::ostream& VariableReferenceArithmeticExpressionElement::do_print(std::ostream& os) const
{
	os << "Variable Reference: " << m_variable_number << std::endl;
	return os;
}
