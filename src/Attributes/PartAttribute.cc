#include "Attributes/PartAttribute.hh"

PartAttribute::PartAttribute(ValueWithLocation<Part> part, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".Part", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_PART),
	m_part(part),
	m_other_field("")
{}

PartAttribute::~PartAttribute()
{}

void PartAttribute::set_other_field(ValueWithLocation<std::string> other_field)
{
	m_other_field = other_field;
}
