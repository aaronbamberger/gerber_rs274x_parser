/*
 * ApertureMacroVariableEnvironment.cc
 *
 *  Created on: Nov 8, 2015
 *      Author: abamberger
 */

#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

ApertureMacroVariableEnvironment::ApertureMacroVariableEnvironment()
{}

ApertureMacroVariableEnvironment::~ApertureMacroVariableEnvironment()
{}

void ApertureMacroVariableEnvironment::set_variable(int var_num, double value)
{
    // Variables are allowed to be reassigned, so we first attempt to clear the old
    // variable definition from the map, and then insert the new value.
    // It would be better to either insert or update in one operation,
    // so once we have access to c++17's insert_or_assign we should update to that
    m_variable_env.erase(var_num);
    m_variable_env.insert(std::make_pair(var_num, value));
}

double ApertureMacroVariableEnvironment::get_variable(int var_num)
{
    // Per the spec, variables that aren't explicitly set are read as 0
    auto var = m_variable_env.find(var_num);
    if (var != m_variable_env.end()) {
        return var->second;
    } else {
        return 0.0;
    }
}
