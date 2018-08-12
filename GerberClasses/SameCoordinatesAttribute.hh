#ifndef _SAME_COORDINATES_ATTRIBUTE
#define _SAME_COORDINATES_ATTRIBUTE

#include "StandardAttribute.hh"

#include <string>

class SameCoordinatesAttribute : public StandardAttribute {
public:
	SameCoordinatesAttribute(std::string name);
	virtual ~SameCoordinatesAttribute();
	
	void set_ident(std::string ident);

private:
	std::string m_ident;
};

#endif // _SAME_COORDINATES_ATTRIBUTE
