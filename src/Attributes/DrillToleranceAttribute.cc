#include "Attributes/DrillToleranceAttribute.hh"

DrillToleranceAttribute::DrillToleranceAttribute(ValueWithLocation<double> plus_tolerance,
												 ValueWithLocation<double> minus_tolerance,
												 yy::location name_location) :
	StandardAttribute(ValueWithLocation<std::string>(".DrillTolerance", name_location),
		StandardAttributeType::STANDARD_ATTRIBUTE_DRILL_TOLERANCE),
	m_plus_tolerance(plus_tolerance),
	m_minus_tolerance(minus_tolerance)
{}

DrillToleranceAttribute::~DrillToleranceAttribute()
{}
