/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/MD5Attribute.hh"

MD5Attribute::MD5Attribute(ValueWithLocation<std::string> md5, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".MD5", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_MD5),
	m_md5(md5)
{}

MD5Attribute::~MD5Attribute()
{}
