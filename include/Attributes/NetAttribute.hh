#ifndef _NET_ATTRIBUTE_H
#define _NET_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"

#include <string>
#include <list>

class NetAttribute : public StandardAttribute {
public:
	NetAttribute(ValueWithLocation<std::string> name, ValueWithLocation<std::string> net_name);
	virtual ~NetAttribute();

	void add_net_name(ValueWithLocation<std::string> net_name);

private:
	std::list<ValueWithLocation<std::string> > m_net_names;
};

#endif // _NET_ATTRIBUTE_H
