/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _PIN_NUMBER_ATTRIBUTE_H
#define _PIN_NUMBER_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

#include <string>

class PinNumberAttribute : public StandardAttribute {
public:
	PinNumberAttribute(ValueWithLocation<std::string> component,
					   ValueWithLocation<std::string> pin,
					   yy::location name_location = yy::location());
	virtual ~PinNumberAttribute();

private:
	ValueWithLocation<std::string> m_component;
	ValueWithLocation<std::string> m_pin;
};

#endif // _PIN_NUMBER_ATTRIBUTE_H
