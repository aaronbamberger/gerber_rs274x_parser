#ifndef _MD5_ATTRIBUTE_H
#define _MD5_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"

#include <string>

class MD5Attribute : public StandardAttribute {
public:
	MD5Attribute(std::string name, std::string md5);
	virtual ~MD5Attribute();

private:
	std::string m_md5;
}

#endif // _MD5_ATTRIBUTE_H
