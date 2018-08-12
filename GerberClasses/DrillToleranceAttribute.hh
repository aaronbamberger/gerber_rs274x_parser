#ifndef _DRILL_TOLERANCE_ATTRIBUTE_H
#define _DRILL_TOLERANCE_ATTRIBUTE_H

#include "StandardAttribute.hh"

#include <string>

class DrillToleranceAttribute : public StandardAttribute {
public:
	DrillToleranceAttribute(std::string name, double plus_tolerance, double minus_tolerance);
	virtual ~DrillToleranceAttribute();

private:
	double m_plus_tolerance;
	double m_minus_tolerance;
};

#endif // _DRILL_TOLERANCE_ATTRIBUTE_H
