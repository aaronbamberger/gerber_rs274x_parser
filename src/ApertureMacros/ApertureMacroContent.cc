#include "ApertureMacros/ApertureMacroContent.hh"

#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>
#include <memory>

ApertureMacroContent::ApertureMacroContent()
{}

ApertureMacroContent::~ApertureMacroContent()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroContent::instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    return do_instantiate(variable_env);
}

std::ostream& operator<<(std::ostream& os, const ApertureMacroContent& macro_content)
{
	return macro_content.do_print(os);
}
