#include "StandardApertureCircle.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "../location.hh"

#include <iostream>
#include <memory>

StandardApertureCircle::StandardApertureCircle(double diameter, double hole_diameter) :
    m_diameter(diameter), m_hole_diameter(hole_diameter), m_has_hole(true)
{}

StandardApertureCircle::StandardApertureCircle(double diameter) :
    m_diameter(diameter), m_hole_diameter(0.0), m_has_hole(false)
{}

StandardApertureCircle::StandardApertureCircle(double diameter, double hole_diameter,
    yy::location diameter_location, yy::location hole_diameter_location, yy::location location) :
        m_diameter(diameter), m_hole_diameter(hole_diameter), m_has_hole(true),
        m_diameter_location(diameter_location), m_hole_diameter_location(hole_diameter_location),
        m_location(location)
{}

StandardApertureCircle::StandardApertureCircle(double diameter, yy::location diameter_location,
    yy::location location) :
        m_diameter(diameter), m_hole_diameter(0.0), m_has_hole(false),
        m_diameter_location(diameter_location), m_location(location)
{}

StandardApertureCircle::~StandardApertureCircle()
{}

Gerber::SemanticValidity StandardApertureCircle::do_check_semantic_validity(SemanticIssueList& issue_list)
{
    // Only for standard circle apertures, a diameter of zero is valid.  This is used
    // for informational purposes, and to attach attributes
    if (m_diameter < 0.0) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_diameter_location,
            "Diameter for circle-type standard aperture must be >= 0");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // If the aperture has a hole, it must have a diameter >= 0, and the hole must not be bigger
    // than the aperture itself.  We'll warn for holes of diameter 0 (since it's not invalid per
    // the spec, but it's redundant, since you can just omit the hole), and we'll return a fatal
    // error if the hole is bigger than the aperture, because this creates a zero size aperture
    // in an improper way
    if (m_has_hole) {
        if (m_hole_diameter < 0.0) {
            SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
                m_hole_diameter_location,
                "Hole diameter for circle-type standard aperture must be >= 0");
            issue_list.add_issue(issue);
            return issue.severity();
        } else if (m_hole_diameter == 0.0) {
            SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
                m_hole_diameter_location,
                "Hole diameter of 0 for circle-type standard aperture is redundant (hole diameter can be omitted)");
            issue_list.add_issue(issue);
        }

        if (m_hole_diameter >= m_diameter) {
            SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
                m_hole_diameter_location,
                "Hole in circle-type standard aperture must not be larger than the aperture itself");
            issue_list.add_issue(issue);
            return issue.severity();
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
	os << "Standard Aperture: Circle (@" << m_location << ")" << std::endl;
	os << "Diameter: " << m_diameter << " (@" << m_diameter_location << ")" << std::endl;
	os << "Hole diameter: ";
	if (m_has_hole) {
		os << m_hole_diameter << " (@" << m_hole_diameter_location << ")" << std::endl;
	} else {
		os << "No Hole" << std::endl;
	}
	return os;
}
