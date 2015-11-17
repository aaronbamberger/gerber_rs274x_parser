#ifndef _STANDARD_APERTURE_POLYGON_H
#define _STANDARD_APERTURE_POLYGON_H

#include "StandardAperture.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "../location.hh"

#include <iostream>
#include <memory>

class StandardAperturePolygon : public StandardAperture {
public:
	StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle, double hole_diameter);
	StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle);
	StandardAperturePolygon(double diameter, double num_vertices);
	StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle, double hole_diameter,
        yy::location diameter_location, yy::location num_vertices_location, yy::location rotation_angle_location,
        yy::location hole_diameter_location, yy::location location);
    StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle,
        yy::location diameter_location, yy::location num_vertices_location, yy::location rotation_angle_location,
        yy::location location);
    StandardAperturePolygon(double diameter, double num_vertices,
        yy::location diameter_location, yy::location num_vertices_location, yy::location location);
	virtual ~StandardAperturePolygon();

private:
	Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
	std::ostream& do_print(std::ostream& os) const;
	std::shared_ptr<StandardAperture> do_clone();

	double m_diameter;
	double m_num_vertices;
	double m_rotation_angle;
	double m_hole_diameter;
	bool m_has_rotation;
	bool m_has_hole;
	yy::location m_diameter_location;
	yy::location m_num_vertices_location;
	yy::location m_rotation_angle_location;
	yy::location m_hole_diameter_location;
	yy::location m_location;
};

#endif // _STANDARD_APERTURE_POLYGON_H
