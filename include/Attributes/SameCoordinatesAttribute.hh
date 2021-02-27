/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _SAME_COORDINATES_ATTRIBUTE
#define _SAME_COORDINATES_ATTRIBUTE

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

#include <string>

class SameCoordinatesAttribute : public StandardAttribute {
public:
	SameCoordinatesAttribute(yy::location name_location = yy::location());
	virtual ~SameCoordinatesAttribute();
	
	void set_ident(ValueWithLocation<std::string> ident);

private:
	ValueWithLocation<std::string> m_ident;
};

#endif // _SAME_COORDINATES_ATTRIBUTE
