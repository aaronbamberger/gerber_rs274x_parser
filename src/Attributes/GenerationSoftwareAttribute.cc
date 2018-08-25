#include "Attributes/GenerationSoftwareAttribute.hh"

GenerationSoftwareAttribute::GenerationSoftwareAttribute(ValueWithLocation<std::string> name,
														 ValueWithLocation<std::string> vendor,
														 ValueWithLocation<std::string> application) :
	StandardAttribute(name), m_vendor(vendor), m_application(application)
{}

GenerationSoftwareAttribute::~GenerationSoftwareAttribute()
{}

void GenerationSoftwareAttribute::set_version(ValueWithLocation<std::string> version)
{
	m_version = version;
}
