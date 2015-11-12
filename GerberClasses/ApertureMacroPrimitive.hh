#ifndef _APERTURE_MACRO_PRIMITIVE_H
#define _APERTURE_MACRO_PRIMITIVE_H

#include "ApertureMacroContent.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacroVariableEnvironment.hh"

#include <iostream>

class ApertureMacroPrimitive : public ApertureMacroContent {
public:
	ApertureMacroPrimitive();
	virtual ~ApertureMacroPrimitive();

private:
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _APERTURE_MACRO_PRIMITIVE_H
