/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Attributes/CreationDateAttribute.hh"

CreationDateAttribute::CreationDateAttribute(ValueWithLocation<std::uint16_t> year,
											 ValueWithLocation<std::uint8_t> month,
											 ValueWithLocation<std::uint8_t> day,
							 				 ValueWithLocation<std::uint8_t> hour,
						 					 ValueWithLocation<std::uint8_t> minute,
						 					 ValueWithLocation<std::uint8_t> second,
						 					 ValueWithLocation<std::int8_t> utc_offset,
											 yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".CreationDate", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_CREATION_DATE),
	m_year(year),
	m_month(month),
	m_day(day),
	m_hour(hour),
	m_minute(minute),
	m_second(second),
	m_utc_offset(utc_offset)
{}

CreationDateAttribute::~CreationDateAttribute()
{}

