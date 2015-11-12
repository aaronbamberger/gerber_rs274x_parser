#include "StandardApertureRectangle.hh"

#include <iostream>
#include <memory>
#include <algorithm>

StandardApertureRectangle::StandardApertureRectangle(double x_size, double y_size, double hole_diameter) : m_x_size(x_size),
																											m_y_size(y_size),
																											m_hole_diameter(hole_diameter),
																											m_has_hole(true)
{}

StandardApertureRectangle::StandardApertureRectangle(double x_size, double y_size) : m_x_size(x_size),
																						m_y_size(y_size),
																						m_hole_diameter(0.0),
																						m_has_hole(false)
{}

StandardApertureRectangle::~StandardApertureRectangle()
{}

Gerber::SemanticValidity StandardApertureRectangle::do_check_semantic_validity()
{
    // Width and height must be > 0
    if (m_x_size <= 0.0) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    if (m_y_size <= 0.0) {
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

        // Hole obstructs entire aperture if its diameter is >= max(x_size, y_size)
        // TODO: This isn't exactly true, but it's close to true, and it's a lot easier
        // than doing the actual math, which I should do at some point
        if (m_hole_diameter >= std::max<double>(m_x_size, m_y_size)) {
            return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
        }
    }

    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::shared_ptr<StandardAperture> StandardApertureRectangle::do_clone()
{
    return std::make_shared<StandardApertureRectangle>(*this);
}

std::ostream& StandardApertureRectangle::do_print(std::ostream& os) const
{
	os << "Standard Aperture: Rectangle" << std::endl;
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
