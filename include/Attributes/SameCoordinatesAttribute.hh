#ifndef _SAME_COORDINATES_ATTRIBUTE
#define _SAME_COORDINATES_ATTRIBUTE

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"

#include <string>

class SameCoordinatesAttribute : public StandardAttribute {
public:
	SameCoordinatesAttribute(ValueWithLocation<std::string> name);
	virtual ~SameCoordinatesAttribute();
	
	void set_ident(ValueWithLocation<std::string> ident);

private:
	ValueWithLocation<std::string> m_ident;
};

#endif // _SAME_COORDINATES_ATTRIBUTE
