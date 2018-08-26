#include "Attributes/PinFunctionAttribute.hh"

PinFunctionAttribute::PinFunctionAttribute(ValueWithLocation<std::string> name, ValueWithLocation<std::string> function) :
	StandardAttribute(name), m_function(function)
{}

PinFunctionAttribute::~PinFunctionAttribute()
{}
