/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/ProjectIdAttribute.hh"

ProjectIdAttribute::ProjectIdAttribute(ValueWithLocation<std::string> proj_name,
									   ValueWithLocation<std::string> guid,
									   ValueWithLocation<std::string> revision,
									   yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".ProjectId", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_PROJECT_ID),
	m_proj_name(proj_name),
	m_guid(guid),
	m_revision(revision)
{}

ProjectIdAttribute::~ProjectIdAttribute()
{}
