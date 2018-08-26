#include "Attributes/DrillToleranceAttribute.hh"

DrillToleranceAttribute::DrillToleranceAttribute(ValueWithLocation<std::string> name,
												 ValueWithLocation<double> plus_tolerance,
												 ValueWithLocation<double> minus_tolerance) :
	StandardAttribute(name), m_plus_tolerance(plus_tolerance), m_minus_tolerance(minus_tolerance)
{}

DrillToleranceAttribute::~DrillToleranceAttribute()
{}
