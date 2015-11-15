#include "UnitSpecifier.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>

UnitSpecifier::UnitSpecifier(Gerber::UnitType unit_type) : m_unit_type(unit_type)
{}

UnitSpecifier::UnitSpecifier(Gerber::UnitType unit_type, yy::location location) :
    m_unit_type(unit_type), m_location(location)
{}

UnitSpecifier::~UnitSpecifier()
{}

Gerber::SemanticValidity UnitSpecifier::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "No commands are allowed after the end-of-file command has been encountered");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // It's invalid to attempt to set a unit type of undefined.  This should never happen
    // if the source of this command stream is a parsed gerber file, it could only happen
    // if the command stream was constructed in memory in preparation for writing a file.
    // The undefined unit type is used as an internal marker that the unit specifier command
    // hasn't yet been encountered for the current graphics state
    if (m_unit_type == Gerber::UnitType::UNIT_TYPE_UNDEFINED) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "Attempting to set unit type to undefined.  This probably indicates a bug in the program, not an error in the file.  Please contact the developer with the file that caused this issue");
        return issue.severity();
    }

    // Attempt to set the unit type on the graphics state.  If this fails, it means the unit
    // type has already been set, which is a fatal error
    if (!graphics_state.set_unit_type(m_unit_type)) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "The unit type may only be set once per file");
        issue_list.add_issue(issue);
        return issue.severity();
    }

	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& UnitSpecifier::do_print(std::ostream& os) const
{
	os << "Units: ";
	switch (m_unit_type) {
		case Gerber::UnitType::UNIT_TYPE_IN:
			os << "Inches";
			break;

		case Gerber::UnitType::UNIT_TYPE_MM:
			os << "Millimeters";
			break;

		case Gerber::UnitType::UNIT_TYPE_UNDEFINED:
		    os << "Undefined";
		    break;
	}

	os << " @" << m_location << std::endl;

	return os;
}
