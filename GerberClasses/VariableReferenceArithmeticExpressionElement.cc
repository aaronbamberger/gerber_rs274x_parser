#include "VariableReferenceArithmeticExpressionElement.hh"

#include <iostream>

VariableReferenceArithmeticExpressionElement::VariableReferenceArithmeticExpressionElement(int variable_number) : m_variable_number(variable_number)
{}

VariableReferenceArithmeticExpressionElement::~VariableReferenceArithmeticExpressionElement()
{}

double VariableReferenceArithmeticExpressionElement::do_eval()
{
	//TODO: Need to do the variable lookup with some sort of passed-in variable table
	return 0.0;
}

std::ostream& VariableReferenceArithmeticExpressionElement::do_print(std::ostream& os) const
{
	os << "Variable Reference: " << m_variable_number << std::endl;
	return os;
}