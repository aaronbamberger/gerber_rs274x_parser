/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/Attribute.hh"

Attribute::Attribute(ValueWithLocation<std::string> name) :
	m_name(name)
{}

Attribute::~Attribute()
{}

ValueWithLocation<std::string>& Attribute::get_name()
{
	return m_name;
}
