#include "Attributes/PinFunctionAttribute.hh"

PinFunctionAttribute::PinFunctionAttribute(ValueWithLocation<std::string> function, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".PF", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_PIN_FUNCTION),
	m_function(function)
{}

PinFunctionAttribute::~PinFunctionAttribute()
{}
