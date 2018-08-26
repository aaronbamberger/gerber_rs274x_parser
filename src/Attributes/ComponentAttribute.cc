#include "Attributes/ComponentAttribute.hh"

ComponentAttribute::ComponentAttribute(ValueWithLocation<std::string> name, ValueWithLocation<std::string> ref_des) :
	StandardAttribute(name), m_ref_des(ref_des)
{}

ComponentAttribute::~ComponentAttribute()
{}
