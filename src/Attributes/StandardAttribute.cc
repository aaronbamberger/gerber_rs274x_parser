#include "Attributes/StandardAttribute.hh"

StandardAttribute::StandardAttribute(ValueWithLocation<std::string> name, StandardAttributeType type) :
	Attribute(name), m_type(type)
{}

StandardAttribute::~StandardAttribute()
{}

StandardAttribute::StandardAttributeType StandardAttribute::get_type()
{
	return m_type;
}
