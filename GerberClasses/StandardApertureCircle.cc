#include "StandardApertureCircle.hh"

#include <iostream>

StandardApertureCircle::StandardApertureCircle(double diameter, double hole_diameter) : m_diameter(diameter),
																						m_hole_diameter(hole_diameter),
																						m_has_hole(true)
{}

StandardApertureCircle::StandardApertureCircle(double diameter) : m_diameter(diameter),
																	m_has_hole(false)
{}

StandardApertureCircle::~StandardApertureCircle()
{}

std::ostream& StandardApertureCircle::do_print(std::ostream& os) const
{
	os << "Standard Aperture: Circle" << std::endl;
	os << "Diameter: " << m_diameter << std::endl;
	os << "Hole diameter: ";
	if (m_has_hole) {
		os << m_hole_diameter << std::endl;
	} else {
		os << "No Hole" << std::endl;
	}
	return os;
}