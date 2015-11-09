#ifndef _APERTURE_MACRO_PRIMITIVE_H
#define _APERTURE_MACRO_PRIMITIVE_H

#include "ApertureMacroContent.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacroVariableEnvironment.hh"

#include <iostream>
#include <memory>
#include <unordered_map>

class ApertureMacroPrimitive : public ApertureMacroContent {
public:
	ApertureMacroPrimitive();
	virtual ~ApertureMacroPrimitive();

	std::shared_ptr<InstantiatedApertureMacroPrimitive> instantiate(ApertureMacroVariableEnvironment& variable_env);

private:
	virtual std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _APERTURE_MACRO_PRIMITIVE_H
