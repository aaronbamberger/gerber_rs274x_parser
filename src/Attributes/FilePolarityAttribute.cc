/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/FilePolarityAttribute.hh"

FilePolarityAttribute::FilePolarityAttribute(ValueWithLocation<Polarity> polarity, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".FilePolarity", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_FILE_POLARITY),
	m_polarity(polarity)
{}

FilePolarityAttribute::~FilePolarityAttribute()
{}
