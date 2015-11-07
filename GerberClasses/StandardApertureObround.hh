#ifndef _STANDARD_APERTURE_OBROUND_H
#define _STANDARD_APERTURE_OBROUND_H

#include "StandardAperture.hh"

#include <iostream>

class StandardApertureObround : public StandardAperture {
public:
	StandardApertureObround(double x_size, double y_size, double hole_diameter);
	StandardApertureObround(double x_size, double y_size);
	virtual ~StandardApertureObround();

private:
	std::ostream& do_print(std::ostream& os) const;

	double m_x_size;
	double m_y_size;
	double m_hole_diameter;
	bool m_has_hole;
};

#endif // _STANDARD_APERTURE_OBROUND_H