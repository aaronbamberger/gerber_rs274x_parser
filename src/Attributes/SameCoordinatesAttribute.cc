#include "Attributes/SameCoordinatesAttribute.hh"

SameCoordinatesAttribute::SameCoordinatesAttribute(yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".SameCoordinates", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_SAME_COORDINATES)
{}

SameCoordinatesAttribute::~SameCoordinatesAttribute()
{}

void SameCoordinatesAttribute::set_ident(ValueWithLocation<std::string> ident)
{
	m_ident = ident;
}
