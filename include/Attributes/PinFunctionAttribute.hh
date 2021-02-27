/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _PIN_FUNCTION_ATTRIBUTE_H
#define _PIN_FUNCTION_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"

#include <string>

class PinFunctionAttribute : public StandardAttribute {
public:
	PinFunctionAttribute(ValueWithLocation<std::string> function, yy::location name_location = yy::location());
	virtual ~PinFunctionAttribute();

private:
	ValueWithLocation<std::string> m_function;
};

#endif // _PIN_FUNCTION_ATTRIBUTE_H
