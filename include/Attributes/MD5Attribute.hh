#ifndef _MD5_ATTRIBUTE_H
#define _MD5_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

#include <string>

class MD5Attribute : public StandardAttribute {
public:
	MD5Attribute(ValueWithLocation<std::string> md5, yy::location name_location = yy::location());
	virtual ~MD5Attribute();

private:
	ValueWithLocation<std::string> m_md5;
};

#endif // _MD5_ATTRIBUTE_H
