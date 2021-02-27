/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _CREATION_DATE_ATTRIBUTE_H
#define _CREATION_DATE_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

#include <string>
#include <cstdint>

// TODO: Consider rewriting this to use a standard date/time library, such as boost::date

class CreationDateAttribute : public StandardAttribute {
public:
	CreationDateAttribute(ValueWithLocation<std::uint16_t> year,
						  ValueWithLocation<std::uint8_t> month,
						  ValueWithLocation<std::uint8_t> day,
						  ValueWithLocation<std::uint8_t> hour,
						  ValueWithLocation<std::uint8_t> minute,
						  ValueWithLocation<std::uint8_t> second,
						  ValueWithLocation<std::int8_t> utc_offset,
						  yy::location name_location = yy::location());
	virtual ~CreationDateAttribute();

private:
	ValueWithLocation<std::uint16_t> m_year;
	ValueWithLocation<std::uint8_t> m_month;
	ValueWithLocation<std::uint8_t> m_day;
	ValueWithLocation<std::uint8_t> m_hour;
	ValueWithLocation<std::uint8_t> m_minute;
	ValueWithLocation<std::uint8_t> m_second;
	ValueWithLocation<std::int8_t> m_utc_offset;
};

#endif // _CREATION_DATE_ATTRIBUTE_H
