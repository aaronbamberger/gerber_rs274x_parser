#ifndef _GENERATION_SOFTWARE_ATTRIBUTE_H
#define _GENERATION_SOFTWARE_ATTRIBUTE_H

#include "StandardAttribute.hh"

#include <string>

class GenerationSoftwareAttribute : public StandardAttribute {
public:
	GenerationSoftwareAttribute(std::string name,
								std::string vendor,
								std::string application);
	virtual ~GenerationSoftwareAttribute();

	void set_version(std::string version);

private:
	std::string m_vendor;
	std::string m_application;
	std::string m_version;
};

#endif // _GENERATION_SOFTWARE_ATTRIBUTE_H
