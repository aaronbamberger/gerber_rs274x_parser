#include "Attributes/ComponentAttribute.hh"

ComponentAttribute::ComponentAttribute(ValueWithLocation<std::string> ref_des, yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".C", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_COMPONENT),
	m_ref_des(ref_des)
{}

ComponentAttribute::~ComponentAttribute()
{}
