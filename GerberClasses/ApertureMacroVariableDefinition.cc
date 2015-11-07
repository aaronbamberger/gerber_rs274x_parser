#include "ApertureMacroVariableDefinition.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

ApertureMacroVariableDefinition::ApertureMacroVariableDefinition(int var_num, std::shared_ptr<ArithmeticExpressionElement> var_value) : m_var_num(var_num), m_var_value(var_value)
{}

ApertureMacroVariableDefinition::~ApertureMacroVariableDefinition()
{}

std::ostream& ApertureMacroVariableDefinition::do_print(std::ostream& os) const
{
	os << "Variable Definition: $" << m_var_num << std::endl;
	os << "Value:" << std::endl;
	os << *m_var_value;
	return os;
}