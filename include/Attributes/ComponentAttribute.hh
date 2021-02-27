/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _COMPONENT_ATTRIBUTE_H
#define _COMPONENT_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

#include <string>

class ComponentAttribute : public StandardAttribute {
public:
	ComponentAttribute(ValueWithLocation<std::string> ref_des, yy::location name_location = yy::location());
	virtual ~ComponentAttribute();

private:
	ValueWithLocation<std::string> m_ref_des;
};

#endif // _COMPONENT_ATTRIBUTE_H
