/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _ATTRIBUTE_H
#define _ATTRIBUTE_H

#include "Util/ValueWithLocation.hh"

#include <string>

class Attribute {
public:
	Attribute(ValueWithLocation<std::string> name);
	virtual ~Attribute();

	ValueWithLocation<std::string>& get_name();

protected:
	ValueWithLocation<std::string> m_name;
};

#endif // _ATTRIBUTE_H
