#include "StandardApertureObround.hh"

#include <iostream>

StandardApertureObround::StandardApertureObround(double x_size, double y_size, double hole_diameter) : m_x_size(x_size),
																										m_y_size(y_size),
																										m_hole_diameter(hole_diameter),
																										m_has_hole(true)
{}

StandardApertureObround::StandardApertureObround(double x_size, double y_size) : m_x_size(x_size),
																					m_y_size(y_size),
																					m_has_hole(false)
{}

StandardApertureObround::~StandardApertureObround()
{}

std::ostream& StandardApertureObround::do_print(std::ostream& os) const
{
	os << "Standard Aperture: Obround" << std::endl;
	os << "X Size: " << m_x_size << std::endl;
	os << "Y Size: " << m_y_size << std::endl;
	os << "Hole diameter: ";
	if (m_has_hole) {
		os << m_hole_diameter << std::endl;
	} else {
		os << "No Hole" << std::endl;
	}
	return os;
}