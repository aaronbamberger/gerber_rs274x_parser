#ifndef _COMPONENT_ATTRIBUTE_H
#define _COMPONENT_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"

#include <string>

class ComponentAttribute : public StandardAttribute {
public:
	ComponentAttribute(std::string name, std::string ref_des);
	virtual ~ComponentAttribute();

private:
	std::string m_ref_des;
};

#endif // _COMPONENT_ATTRIBUTE_H
