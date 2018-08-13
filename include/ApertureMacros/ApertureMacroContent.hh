#ifndef _APERTURE_MACRO_CONTENT_H
#define _APERTURE_MACRO_CONTENT_H

#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

class ApertureMacroContent {
public:
	ApertureMacroContent();
	virtual ~ApertureMacroContent();

	std::shared_ptr<InstantiatedApertureMacroPrimitive> instantiate(ApertureMacroVariableEnvironment& variable_env);

	friend std::ostream& operator<<(std::ostream& os, const ApertureMacroContent& macro_content);

private:
	virtual std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env) = 0;

	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _APERTURE_MACRO_CONTENT_H
