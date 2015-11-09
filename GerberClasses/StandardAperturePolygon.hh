#ifndef _STANDARD_APERTURE_POLYGON_H
#define _STANDARD_APERTURE_POLYGON_H

#include "StandardAperture.hh"
#include "GlobalDefs.hh"

#include <iostream>

class StandardAperturePolygon : public StandardAperture {
public:
	StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle, double hole_diameter);
	StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle);
	StandardAperturePolygon(double diameter, double num_vertices);
	virtual ~StandardAperturePolygon();

private:
	Gerber::SemanticValidity do_check_semantic_validity();
	std::ostream& do_print(std::ostream& os) const;

	double m_diameter;
	double m_num_vertices;
	double m_rotation_angle;
	double m_hole_diameter;
	bool m_has_rotation;
	bool m_has_hole;
};

#endif // _STANDARD_APERTURE_POLYGON_H
