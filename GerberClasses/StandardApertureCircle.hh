#ifndef _STANDARD_APERTURE_CIRCLE_H
#define _STANDARD_APERTURE_CIRCLE_H

#include "StandardAperture.hh"

#include <iostream>

class StandardApertureCircle : public StandardAperture {
public:
	StandardApertureCircle(double diameter, double hole_diameter);
	StandardApertureCircle(double diameter);
	virtual ~StandardApertureCircle();

private:
	std::ostream& do_print(std::ostream& os) const;

	double m_diameter;
	double m_hole_diameter;
	bool m_has_hole;
};

#endif // _STANDARD_APERTURE_CIRCLE_H
