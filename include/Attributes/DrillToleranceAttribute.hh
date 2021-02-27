/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _DRILL_TOLERANCE_ATTRIBUTE_H
#define _DRILL_TOLERANCE_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"
#include "location.hh"

#include <string>

class DrillToleranceAttribute : public StandardAttribute {
public:
	DrillToleranceAttribute(ValueWithLocation<double> plus_tolerance,
							ValueWithLocation<double> minus_tolerance,
							yy::location name_location = yy::location());
	virtual ~DrillToleranceAttribute();

private:
	ValueWithLocation<double> m_plus_tolerance;
	ValueWithLocation<double> m_minus_tolerance;
};

#endif // _DRILL_TOLERANCE_ATTRIBUTE_H
