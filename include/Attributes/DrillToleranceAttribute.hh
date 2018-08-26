#ifndef _DRILL_TOLERANCE_ATTRIBUTE_H
#define _DRILL_TOLERANCE_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"

#include <string>

class DrillToleranceAttribute : public StandardAttribute {
public:
	DrillToleranceAttribute(ValueWithLocation<std::string> name,
							ValueWithLocation<double> plus_tolerance,
							ValueWithLocation<double> minus_tolerance);
	virtual ~DrillToleranceAttribute();

private:
	ValueWithLocation<double> m_plus_tolerance;
	ValueWithLocation<double> m_minus_tolerance;
};

#endif // _DRILL_TOLERANCE_ATTRIBUTE_H
