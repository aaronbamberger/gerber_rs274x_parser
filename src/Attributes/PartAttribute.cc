#include "Attributes/PartAttribute.hh"

PartAttribute::PartAttribute(ValueWithLocation<std::string> name, ValueWithLocation<Part> part) :
	StandardAttribute(name), m_part(part), m_other_field("")
{}

PartAttribute::~PartAttribute()
{}

void PartAttribute::set_other_field(ValueWithLocation<std::string> other_field)
{
	m_other_field = other_field;
}
