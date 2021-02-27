/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _USER_ATTRIBUTE_H
#define _USER_ATTRIBUTE_H

#include "Attributes/Attribute.hh"

#include <string>
#include <list>

class UserAttribute : public Attribute {
public:
	UserAttribute(std::string name);
	virtual ~UserAttribute();

private:
	std::list<std::string> m_values;
};	

#endif // _USER_ATTRIBUTE_H
