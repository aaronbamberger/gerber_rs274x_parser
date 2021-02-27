/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/GenerationSoftwareAttribute.hh"

GenerationSoftwareAttribute::GenerationSoftwareAttribute(ValueWithLocation<std::string> vendor,
														 ValueWithLocation<std::string> application,
														 yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".GenerationSoftware", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_GENERATION_SOFTWARE),
	m_vendor(vendor),
	m_application(application)
{}

GenerationSoftwareAttribute::~GenerationSoftwareAttribute()
{}

void GenerationSoftwareAttribute::set_version(ValueWithLocation<std::string> version)
{
	m_version = version;
}
