#include "Attributes/PinNumberAttribute.hh"

PinNumberAttribute::PinNumberAttribute(ValueWithLocation<std::string> name,
									   ValueWithLocation<std::string> component,
									   ValueWithLocation<std::string> pin) :
	StandardAttribute(name), m_component(component), m_pin(pin)
{}

PinNumberAttribute::~PinNumberAttribute()
{}
