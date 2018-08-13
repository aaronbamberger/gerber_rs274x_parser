#include "Commands/EndOfFile.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <string>

EndOfFile::EndOfFile()
{}

EndOfFile::EndOfFile(yy::location location) : m_location(location)
{}

EndOfFile::~EndOfFile()
{}

Gerber::SemanticValidity EndOfFile::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // Seeing an end of file while region mode is on is a fatal error
    if (graphics_state.current_region_mode_state() == Gerber::RegionModeState::REGION_MODE_ON) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "An End-of-File command is not allowed when in region mode (regions must be closed before the file is terminated)");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // Attempt to set end-of-file on the graphics state.  This will fail if an end-of-file
    // command has already been encountered, which is a fatal error
    if (!graphics_state.set_file_complete()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "Multiple End-of-File commands per file are invalid.  Each file must contain exactly 1 End-of-File command, only at the end of the file");
        issue_list.add_issue(issue);
        return issue.severity();
    }

	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& EndOfFile::do_print(std::ostream& os) const
{
	os << "End of File @" << m_location << std::endl;
	return os;
}
