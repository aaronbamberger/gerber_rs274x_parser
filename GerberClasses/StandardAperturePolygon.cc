#include "StandardAperturePolygon.hh"

#include <iostream>

StandardAperturePolygon::StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle, double hole_diameter) : m_diameter(diameter),
																																		m_num_vertices(num_vertices),
																																		m_rotation_angle(rotation_angle),
																																		m_hole_diameter(hole_diameter),
																																		m_has_rotation(true),
																																		m_has_hole(true)
{}

StandardAperturePolygon::StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle) : m_diameter(diameter),
																												m_num_vertices(num_vertices),
																												m_rotation_angle(rotation_angle),
																												m_has_rotation(true),
																												m_has_hole(false)
{}

StandardAperturePolygon::StandardAperturePolygon(double diameter, double num_vertices) : m_diameter(diameter),
																							m_num_vertices(num_vertices),
																							m_has_rotation(false),
																							m_has_hole(false)
{}

StandardAperturePolygon::~StandardAperturePolygon()
{}

std::ostream& StandardAperturePolygon::do_print(std::ostream& os) const
{
	os << "Standard Aperture: Polygon" << std::endl;
	os << "Diameter: " << m_diameter << std::endl;
	os << "Number of Vertices: " << m_num_vertices << std::endl;

	os << "Rotation angle: ";
	if (m_has_rotation) {
		os << m_rotation_angle << std::endl;
	} else {
		os << "No Rotation" << std::endl;
	}

	os << "Hole diameter: ";
	if (m_has_hole) {
		os << m_hole_diameter << std::endl;
	} else {
		os << "No Hole" << std::endl;
	}
	
	return os;
}