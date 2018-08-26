#ifndef _COMPONENT_ATTRIBUTE_H
#define _COMPONENT_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"

#include <string>

class ComponentAttribute : public StandardAttribute {
public:
	ComponentAttribute(ValueWithLocation<std::string> name, ValueWithLocation<std::string> ref_des);
	virtual ~ComponentAttribute();

private:
	ValueWithLocation<std::string> m_ref_des;
};

#endif // _COMPONENT_ATTRIBUTE_H
