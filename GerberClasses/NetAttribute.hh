#ifndef _NET_ATTRIBUTE_H
#define _NET_ATTRIBUTE_H

#include "StandardAttribute.hh"

#include <string>
#include <list>

class NetAttribute : public StandardAttribute {
public:
	NetAttribute(std::string name, std::string net_name);
	virtual ~NetAttribute();

	void add_net_name(std::string net_name);

private:
	std::list<std::string> m_net_names;
};

#endif // _NET_ATTRIBUTE_H
