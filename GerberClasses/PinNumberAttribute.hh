#ifndef _PIN_NUMBER_ATTRIBUTE_H
#define _PIN_NUMBER_ATTRIBUTE_H

#include "StandardAttribute.hh"

#include <string>

class PinNumberAttribute {
public:
	PinNumberAttribute(std::string name, std::string component, std::string pin);
	virtual ~PinNumberAttribute();

private:
	std::string m_component;
	std::string m_pin;
};

#endif // _PIN_NUMBER_ATTRIBUTE_H
