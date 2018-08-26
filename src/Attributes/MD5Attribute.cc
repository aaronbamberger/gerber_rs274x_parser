#include "Attributes/MD5Attribute.hh"

MD5Attribute::MD5Attribute(ValueWithLocation<std::string> name, ValueWithLocation<std::string> md5) :
	StandardAttribute(name), m_md5(md5)
{}

MD5Attribute::~MD5Attribute()
{}
