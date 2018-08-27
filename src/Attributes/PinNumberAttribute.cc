#include "Attributes/PinNumberAttribute.hh"

PinNumberAttribute::PinNumberAttribute(ValueWithLocation<std::string> component,
									   ValueWithLocation<std::string> pin,
									   yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".P", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_PIN_NUMBER),
	m_component(component),
	m_pin(pin)
{}

PinNumberAttribute::~PinNumberAttribute()
{}
