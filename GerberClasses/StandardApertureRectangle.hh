#ifndef _STANDARD_APERTURE_RECTANGLE_H
#define _STANDARD_APERTURE_RECTANGLE_H

#include "StandardAperture.hh"
#include "GlobalDefs.hh"

#include <iostream>

class StandardApertureRectangle : public StandardAperture {
public:
	StandardApertureRectangle(double x_size, double y_size, double hole_diameter);
	StandardApertureRectangle(double x_size, double y_size);
	virtual ~StandardApertureRectangle();

private:
	Gerber::SemanticValidity do_check_semantic_validity();
	std::ostream& do_print(std::ostream& os) const;

	double m_x_size;
	double m_y_size;
	double m_hole_diameter;
	bool m_has_hole;
};

#endif // _STANDARD_APERTURE_RECTANGLE_H
