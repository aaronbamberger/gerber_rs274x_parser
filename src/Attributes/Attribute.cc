#include "Attributes/Attribute.hh"

Attribute::Attribute(ValueWithLocation<std::string> name) :
	m_name(name)
{}

Attribute::~Attribute()
{}

ValueWithLocation<std::string>& Attribute::get_name()
{
	return m_name;
}
