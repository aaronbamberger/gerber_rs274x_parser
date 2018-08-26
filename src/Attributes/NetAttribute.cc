#include "Attributes/NetAttribute.hh"

NetAttribute::NetAttribute(ValueWithLocation<std::string> name, ValueWithLocation<std::string> net_name) :
	StandardAttribute(name)
{
	m_net_names.push_back(net_name);
}

NetAttribute::~NetAttribute()
{}

void NetAttribute::add_net_name(ValueWithLocation<std::string> net_name)
{
	m_net_names.push_back(net_name);
}
