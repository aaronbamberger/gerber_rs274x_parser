/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_MACRO_PRIMITIVE_H
#define _APERTURE_MACRO_PRIMITIVE_H

#include "ApertureMacros/ApertureMacroContent.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>

class ApertureMacroPrimitive : public ApertureMacroContent {
public:
	ApertureMacroPrimitive();
	virtual ~ApertureMacroPrimitive();

private:
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _APERTURE_MACRO_PRIMITIVE_H
