/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/PinFunctionAttribute.hh"

PinFunctionAttribute::PinFunctionAttribute(ValueWithLocation<std::string> function, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".PF", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_PIN_FUNCTION),
	m_function(function)
{}

PinFunctionAttribute::~PinFunctionAttribute()
{}
