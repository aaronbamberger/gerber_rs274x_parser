#ifndef _CREATION_DATE_ATTRIBUTE_H
#define _CREATION_DATE_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"

#include <string>
#include <cstdint>

// TODO: Consider rewriting this to use a standard date/time library, such as boost::date

class CreationDateAttribute : public StandardAttribute {
public:
	CreationDateAttribute(std::string name,
					      std::uint16_t year,
						  std::uint8_t month,
						  std::uint8_t day,
						  std::uint8_t hour,
						  std::uint8_t minute,
						  std::uint8_t second,
						  std::int8_t utc_offset);
	virtual ~CreationDateAttribute();

private:
	std::uint16_t m_year;
	std::uint8_t m_month;
	std::uint8_t m_day;
	std::uint8_t m_hour;
	std::uint8_t m_minute;
	std::uint8_t m_second;
	std::int8_t m_utc_offset;
};

#endif // _CREATION_DATE_ATTRIBUTE_H
