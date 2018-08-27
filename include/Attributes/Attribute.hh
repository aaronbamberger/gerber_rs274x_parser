#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#include "Util/ValueWithLocation.hh"

#include <string>

class Attribute {
public:
	Attribute(ValueWithLocation<std::string> name);
	virtual ~Attribute();

	ValueWithLocation<std::string>& get_name();

protected:
	ValueWithLocation<std::string> m_name;
};

#endif // _ATTRIBUTE_H
