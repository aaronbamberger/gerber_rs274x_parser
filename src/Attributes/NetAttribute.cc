/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/NetAttribute.hh"

NetAttribute::NetAttribute(ValueWithLocation<std::string> net_name, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".N", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_NET)
{
	m_net_names.push_back(net_name);
}

NetAttribute::~NetAttribute()
{}

void NetAttribute::add_net_name(ValueWithLocation<std::string> net_name)
{
	m_net_names.push_back(net_name);
}
