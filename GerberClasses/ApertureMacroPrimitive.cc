#include "ApertureMacroPrimitive.hh"
#include "ApertureMacroVariableEnvironment.hh"

#include <iostream>
#include <memory>
#include <unordered_map>

ApertureMacroPrimitive::ApertureMacroPrimitive()
{}

ApertureMacroPrimitive::~ApertureMacroPrimitive()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroPrimitive::instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    return do_instantiate(variable_env);
}
