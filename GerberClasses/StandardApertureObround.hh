#ifndef _STANDARD_APERTURE_OBROUND_H
#define _STANDARD_APERTURE_OBROUND_H

#include "StandardAperture.hh"
#include "GlobalDefs.hh"
#include "../location.hh"

#include <iostream>
#include <memory>

class StandardApertureObround : public StandardAperture {
public:
    StandardApertureObround(double x_size, double y_size, double hole_diameter);
    StandardApertureObround(double x_size, double y_size);
	StandardApertureObround(double x_size, double y_size, double hole_diameter,
        yy::location x_size_location, yy::location y_size_location,
        yy::location hole_diameter_location, yy::location location);
	StandardApertureObround(double x_size, double y_size,
        yy::location x_size_location, yy::location y_size_location, yy::location location);
	virtual ~StandardApertureObround();

private:
	Gerber::SemanticValidity do_check_semantic_validity();
	std::ostream& do_print(std::ostream& os) const;
	std::shared_ptr<StandardAperture> do_clone();

	double m_x_size;
	double m_y_size;
	double m_hole_diameter;
	bool m_has_hole;
	yy::location m_x_size_location;
	yy::location m_y_size_location;
	yy::location m_hole_diameter_location;
	yy::location m_location;
};

#endif // _STANDARD_APERTURE_OBROUND_H
