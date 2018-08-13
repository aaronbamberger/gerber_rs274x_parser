#ifndef _STANDARD_ATTRIBUTE_H
#define _STANDARD_ATTRIBUTE_H

#include "Attributes/Attribute.hh"

#include <string>

class StandardAttribute : public Attribute {
public:
	StandardAttribute(std::string name);
	virtual ~StandardAttribute();
};

#endif // _STANDARD_ATTRIBUTE_H
