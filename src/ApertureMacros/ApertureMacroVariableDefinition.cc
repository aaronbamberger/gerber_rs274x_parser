#include "ApertureMacros/ApertureMacroVariableDefinition.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

ApertureMacroVariableDefinition::ApertureMacroVariableDefinition(int var_num, std::shared_ptr<ArithmeticExpressionElement> var_value) : m_var_num(var_num), m_var_value(var_value)
{}

ApertureMacroVariableDefinition::~ApertureMacroVariableDefinition()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroVariableDefinition::do_instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    // Evaluate the variable
    double var_value = m_var_value->eval(variable_env);

    // Insert the evaluated variable into the environment
    variable_env.set_variable(m_var_num, var_value);

    // Return a null pointer, the only purpose of instantiating a variable definition
    // is to insert the variable value into the environment
    return std::shared_ptr<InstantiatedApertureMacroPrimitive>(nullptr);
}

std::ostream& ApertureMacroVariableDefinition::do_print(std::ostream& os) const
{
	os << "Variable Definition: $" << m_var_num << std::endl;
	os << "Value:" << std::endl;
	os << *m_var_value;
	return os;
}
