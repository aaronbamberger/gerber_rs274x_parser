#include "StandardAperturePolygon.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>
#include <cmath>

StandardAperturePolygon::StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle, double hole_diameter) :
    m_diameter(diameter), m_num_vertices(num_vertices), m_rotation_angle(rotation_angle), m_hole_diameter(hole_diameter),
    m_has_rotation(true), m_has_hole(true)
{}

StandardAperturePolygon::StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle) :
    m_diameter(diameter), m_num_vertices(num_vertices), m_rotation_angle(rotation_angle), m_hole_diameter(0.0),
    m_has_rotation(true), m_has_hole(false)
{}

StandardAperturePolygon::StandardAperturePolygon(double diameter, double num_vertices) :
    m_diameter(diameter), m_num_vertices(num_vertices), m_rotation_angle(0.0), m_hole_diameter(0.0),
    m_has_rotation(false), m_has_hole(false)
{}

StandardAperturePolygon::StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle, double hole_diameter,
    yy::location diameter_location, yy::location num_vertices_location, yy::location rotation_angle_location,
    yy::location hole_diameter_location, yy::location location) :
        m_diameter(diameter), m_num_vertices(num_vertices), m_rotation_angle(rotation_angle), m_hole_diameter(hole_diameter),
        m_has_rotation(true), m_has_hole(true), m_diameter_location(diameter_location), m_num_vertices_location(num_vertices_location),
        m_rotation_angle_location(rotation_angle_location), m_hole_diameter_location(hole_diameter_location), m_location(location)
{}

StandardAperturePolygon::StandardAperturePolygon(double diameter, double num_vertices, double rotation_angle,
    yy::location diameter_location, yy::location num_vertices_location, yy::location rotation_angle_location,
    yy::location location) :
        m_diameter(diameter), m_num_vertices(num_vertices), m_rotation_angle(rotation_angle), m_hole_diameter(0.0),
        m_has_rotation(true), m_has_hole(false), m_diameter_location(diameter_location), m_num_vertices_location(num_vertices_location),
        m_rotation_angle_location(rotation_angle_location), m_location(location)
{}

StandardAperturePolygon::StandardAperturePolygon(double diameter, double num_vertices,
    yy::location diameter_location, yy::location num_vertices_location, yy::location location) :
        m_diameter(diameter), m_num_vertices(num_vertices), m_rotation_angle(0.0), m_hole_diameter(0.0),
        m_has_rotation(false), m_has_hole(false), m_diameter_location(diameter_location), m_num_vertices_location(num_vertices_location),
        m_location(location)
{}

StandardAperturePolygon::~StandardAperturePolygon()
{}

Gerber::SemanticValidity StandardAperturePolygon::do_check_semantic_validity()
{
    // Outer diameter must be > 0
    if (m_diameter <= 0.0) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Per spec, the number of vertices must be [3, 12].  We'll return a fatal error if the number
    // isn't an integer, or is < 3, because those don't make sense, but we'll just return a warning
    // if it's > 12, since that still makes sense, it just violates the spec
    // Check if the number of vertices is integral
    double dummy;
    if (std::modf(m_num_vertices, &dummy) != 0.0) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Check range of number of vertices
    if (m_num_vertices < 3.0) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    } else if (m_num_vertices > 12.0) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
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

        // Hole obstructs entire aperture if its diameter is >= the outer diameter of the polygon
        if (m_hole_diameter >= m_diameter) {
            return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
        }
    }

    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::shared_ptr<StandardAperture> StandardAperturePolygon::do_clone()
{
    return std::make_shared<StandardAperturePolygon>(*this);
}

std::ostream& StandardAperturePolygon::do_print(std::ostream& os) const
{
	os << "Standard Aperture: Polygon (@" << m_location << ")" << std::endl;
	os << "Diameter: " << m_diameter << " (@" << m_diameter_location << ")" << std::endl;
	os << "Number of Vertices: " << m_num_vertices << " (@" << m_num_vertices_location << ")" << std::endl;

	os << "Rotation angle: ";
	if (m_has_rotation) {
		os << m_rotation_angle << " (@" << m_rotation_angle_location << ")" << std::endl;
	} else {
		os << "No Rotation" << std::endl;
	}

	os << "Hole diameter: ";
	if (m_has_hole) {
		os << m_hole_diameter << " (@" << m_hole_diameter_location << ")" << std::endl;
	} else {
		os << "No Hole" << std::endl;
	}
	
	return os;
}
