#include "Attributes/GenerationSoftwareAttribute.hh"

GenerationSoftwareAttribute::GenerationSoftwareAttribute(ValueWithLocation<std::string> vendor,
														 ValueWithLocation<std::string> application,
														 yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".GenerationSoftware", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_GENERATION_SOFTWARE),
	m_vendor(vendor),
	m_application(application)
{}

GenerationSoftwareAttribute::~GenerationSoftwareAttribute()
{}

void GenerationSoftwareAttribute::set_version(ValueWithLocation<std::string> version)
{
	m_version = version;
}
