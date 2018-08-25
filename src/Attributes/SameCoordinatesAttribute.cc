#include "Attributes/SameCoordinatesAttribute.hh"

SameCoordinatesAttribute::SameCoordinatesAttribute(ValueWithLocation<std::string> name) :
	StandardAttribute(name)
{}

SameCoordinatesAttribute::~SameCoordinatesAttribute()
{}

void SameCoordinatesAttribute::set_ident(ValueWithLocation<std::string> ident)
{
	m_ident = ident;
}
