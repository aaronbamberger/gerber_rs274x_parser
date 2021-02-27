/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/PartAttribute.hh"

PartAttribute::PartAttribute(ValueWithLocation<Part> part, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".Part", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_PART),
	m_part(part),
	m_other_field("")
{}

PartAttribute::~PartAttribute()
{}

void PartAttribute::set_other_field(ValueWithLocation<std::string> other_field)
{
	m_other_field = other_field;
}
