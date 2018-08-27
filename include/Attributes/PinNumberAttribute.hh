#ifndef _PIN_NUMBER_ATTRIBUTE_H
#define _PIN_NUMBER_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

#include <string>

class PinNumberAttribute : public StandardAttribute {
public:
	PinNumberAttribute(ValueWithLocation<std::string> component,
					   ValueWithLocation<std::string> pin,
					   yy::location name_location = yy::location());
	virtual ~PinNumberAttribute();

private:
	ValueWithLocation<std::string> m_component;
	ValueWithLocation<std::string> m_pin;
};

#endif // _PIN_NUMBER_ATTRIBUTE_H
