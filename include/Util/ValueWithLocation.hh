#ifndef _VALUE_WITH_LOCATION_H
#define _VALUE_WITH_LOCATION_H

#include "location.hh"

template <typename T>
class ValueWithLocation
{
public:
	ValueWithLocation();
	ValueWithLocation(T value, yy::location location = yy::location());
	virtual ~ValueWithLocation();

	T& get_value();

private:
	yy::location m_location;
	T m_value;
};

#endif // _VALUE_WITH_LOCATION_H
