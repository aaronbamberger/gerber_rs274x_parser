#include "Commands/ApertureDefinitionStandard.hh"
#include "Apertures/StandardAperture.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"

#include <iostream>
#include <memory>
#include <string>

ApertureDefinitionStandard::ApertureDefinitionStandard(int aperture_number, std::shared_ptr<StandardAperture> standard_aperture) :
    ApertureDefinition(aperture_number), m_standard_aperture(standard_aperture)
{}

ApertureDefinitionStandard::ApertureDefinitionStandard(int aperture_number, std::shared_ptr<StandardAperture> standard_aperture,
    yy::location aperture_number_location, yy::location location) :
        ApertureDefinition(aperture_number, aperture_number_location, location), m_standard_aperture(standard_aperture)
{}

ApertureDefinitionStandard::~ApertureDefinitionStandard()
{}

Gerber::SemanticValidity ApertureDefinitionStandard::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "No commands are allowed after the end-of-file command has been encountered");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    Gerber::SemanticValidity aperture_validity = m_standard_aperture->check_semantic_validity(issue_list);

    // Only error out here if the standard definition returned a fatal error
    // Else, we'll keep going, and return any warnings or deprecations after
    // checking other stuff that could be fatal
    if (aperture_validity == Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL) {
        return aperture_validity;
    }

    // Attempt to add this aperture into the aperture dictionary of the graphics state
    // If this fails, it means an aperture with this id has already been defined, which
    // is a fatal error
    if (!graphics_state.define_aperture(m_aperture_number, m_standard_aperture->clone())) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "Redefining an aperture ID is prohibited");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    return aperture_validity;
}

std::ostream& ApertureDefinitionStandard::do_print(std::ostream& os) const
{
	os << "Standard Aperture Definition (@" << m_location << "):" << std::endl;
	os << "Aperture ID: " << m_aperture_number << " (@" << m_aperture_number_location << ")" << std::endl;
	os << *m_standard_aperture;
	return os;
}
