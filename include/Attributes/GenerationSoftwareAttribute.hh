#ifndef _GENERATION_SOFTWARE_ATTRIBUTE_H
#define _GENERATION_SOFTWARE_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"

#include <string>

class GenerationSoftwareAttribute : public StandardAttribute {
public:
	GenerationSoftwareAttribute(ValueWithLocation<std::string> name,
								ValueWithLocation<std::string> vendor,
								ValueWithLocation<std::string> application);
	virtual ~GenerationSoftwareAttribute();

	void set_version(ValueWithLocation<std::string> version);

private:
	ValueWithLocation<std::string> m_vendor;
	ValueWithLocation<std::string> m_application;
	ValueWithLocation<std::string> m_version;
};

#endif // _GENERATION_SOFTWARE_ATTRIBUTE_H
