/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/StandardAttribute.hh"

StandardAttribute::StandardAttribute(ValueWithLocation<std::string> name, StandardAttributeType type) :
	Attribute(name), m_type(type)
{}

StandardAttribute::~StandardAttribute()
{}

StandardAttribute::StandardAttributeType StandardAttribute::get_type()
{
	return m_type;
}
