#include "StandardApertureCircle.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

StandardApertureCircle::StandardApertureCircle(double diameter, double hole_diameter) : m_diameter(diameter),
																						m_hole_diameter(hole_diameter),
																						m_has_hole(true)
{}

StandardApertureCircle::StandardApertureCircle(double diameter) : m_diameter(diameter),
                                                                    m_hole_diameter(0.0),
																	m_has_hole(false)
{}

StandardApertureCircle::~StandardApertureCircle()
{}

Gerber::SemanticValidity StandardApertureCircle::do_check_semantic_validity()
{
    // Only for standard circle apertures, a diameter of zero is valid.  This is used
    // for informational purposes, and to attach attributes
    if (m_diameter < 0.0) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // If the aperture has a hole, it must have a diameter >= 0, and the hole must not be bigger
    // than the aperture itself.  We'll warn for holes of diameter 0 (since it's not invalid per
    // the spec, but it's redundant, since you can just omit the hole), and we'll return a fatal
    // error if the hole is bigger than the aperture, because this creates a zero size aperture
    // in an improper way
    if (m_has_hole) {
        if (m_hole_diameter < 0.0) {
            return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
        } else if (m_hole_diameter == 0.0) {
            return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
        }

        if (m_hole_diameter >= m_diameter) {
            return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
        }
    }

    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::shared_ptr<StandardAperture> StandardApertureCircle::do_clone()
{
    return std::make_shared<StandardApertureCircle>(*this);
}

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
