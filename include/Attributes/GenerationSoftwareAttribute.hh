/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _GENERATION_SOFTWARE_ATTRIBUTE_H
#define _GENERATION_SOFTWARE_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

#include <string>

class GenerationSoftwareAttribute : public StandardAttribute {
public:
	GenerationSoftwareAttribute(ValueWithLocation<std::string> vendor,
								ValueWithLocation<std::string> application,
								yy::location name_location = yy::location());
	virtual ~GenerationSoftwareAttribute();

	void set_version(ValueWithLocation<std::string> version);

private:
	ValueWithLocation<std::string> m_vendor;
	ValueWithLocation<std::string> m_application;
	ValueWithLocation<std::string> m_version;
};

#endif // _GENERATION_SOFTWARE_ATTRIBUTE_H
