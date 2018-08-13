#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#include <string>

class Attribute {
public:
	Attibute(std::string name);
	virtual ~Attribute();

protected:
	std::string m_name;
};

#endif // _ATTRIBUTE_H
