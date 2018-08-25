#ifndef _STANDARD_ATTRIBUTE_H
#define _STANDARD_ATTRIBUTE_H

#include "Attributes/Attribute.hh"
#include "Util/ValueWithLocation.hh"

#include <string>

class StandardAttribute : public Attribute {
public:
	StandardAttribute(ValueWithLocation<std::string> name);
	virtual ~StandardAttribute();
};

#endif // _STANDARD_ATTRIBUTE_H
