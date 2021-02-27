/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/PinNumberAttribute.hh"

PinNumberAttribute::PinNumberAttribute(ValueWithLocation<std::string> component,
									   ValueWithLocation<std::string> pin,
									   yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".P", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_PIN_NUMBER),
	m_component(component),
	m_pin(pin)
{}

PinNumberAttribute::~PinNumberAttribute()
{}
