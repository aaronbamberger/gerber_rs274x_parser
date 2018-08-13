#include "Commands/FormatSpecifier.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <string>
#include <memory>

FormatSpecifier::FormatSpecifier(int x_num_int_positions, int x_num_dec_positions, int y_num_int_positions, int y_num_dec_positions) :
    m_x_num_int_positions(x_num_int_positions), m_x_num_dec_positions(x_num_dec_positions),
    m_y_num_int_positions(y_num_int_positions), m_y_num_dec_positions(y_num_dec_positions)
{}

FormatSpecifier::FormatSpecifier(int x_num_int_positions, int x_num_dec_positions, int y_num_int_positions, int y_num_dec_positions,
    yy::location x_num_int_positions_location, yy::location x_num_dec_positions_location,
    yy::location y_num_int_positions_location, yy::location y_num_dec_positions_location,
    yy::location location) :
        m_x_num_int_positions(x_num_int_positions), m_x_num_dec_positions(x_num_dec_positions),
        m_y_num_int_positions(y_num_int_positions), m_y_num_dec_positions(y_num_dec_positions),
        m_x_num_int_positions_location(x_num_int_positions_location), m_x_num_dec_positions_location(x_num_dec_positions_location),
        m_y_num_int_positions_location(y_num_int_positions_location), m_y_num_dec_positions_location(y_num_dec_positions_location),
        m_location(location)
{}


FormatSpecifier::~FormatSpecifier()
{}

Gerber::SemanticValidity FormatSpecifier::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "No commands are allowed after the end-of-file command has been encountered");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // First, attempt to set the coordinate format of the graphics state.  This will fail
    // if the coordinate format of the graphics state has already been set
    // (which we'll consider a fatal error)
    // TODO: Currently, creating another copy of the format specifier to set in the graphics state
    // I'm not particularly happy with this solution, but I'll have to think about it some more
    std::shared_ptr<FormatSpecifier> format_spec_copy = std::shared_ptr<FormatSpecifier>(new FormatSpecifier(*this));
    if (!graphics_state.set_coord_format(format_spec_copy)) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "The coordinate format may only be set once per file");
        issue_list.add_issue(issue);
        return issue.severity();
    }

	// For any of the fields, a negative number doesn't make sense
	// and is a fatal error
	if (m_x_num_int_positions < 0) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_x_num_int_positions_location,
            "Number of integer positions (X) may not be negative");
	    issue_list.add_issue(issue);
		return issue.severity();
	}

	if (m_x_num_dec_positions < 0) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_x_num_dec_positions_location,
            "Number of decimal positions (X) may not be negative");
        issue_list.add_issue(issue);
        return issue.severity();
	}

	if (m_y_num_int_positions < 0) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_y_num_int_positions_location,
            "Number of integer positions (Y) may not be negative");
        issue_list.add_issue(issue);
        return issue.severity();
	}

	if (m_y_num_dec_positions < 0) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_y_num_dec_positions_location,
            "Number of decimal positions (Y) may not be negative");
        issue_list.add_issue(issue);
        return issue.severity();
	}

	// Per the spec, the coordinate format for X and Y must be the same
	// Since it isn't nonsensical to have different X and Y formats
	// (even though it's prohibited by the spec), this is a warning, not a fatal error
	if ((m_x_num_int_positions != m_y_num_int_positions) || (m_x_num_dec_positions != m_y_num_dec_positions)) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
            m_location,
            "Different coordinate formats for X and Y are outside of the official Gerber specification, but are supported by this implementation");
	    issue_list.add_issue(issue);
	}

	// Also prohibited by the spec, (but not nonsensical), are numbers of integer or decimal places > 6
	if (m_x_num_int_positions > 6) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
            m_x_num_int_positions_location,
            "Number of integer positions (X) > 6 is outside of the official Gerber specification, but is supported by this implementation");
	    issue_list.add_issue(issue);
	}

	if (m_x_num_dec_positions > 6) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
            m_x_num_dec_positions_location,
            "Number of decimal positions (X) > 6 is outside of the official Gerber specification, but is supported by this implementation");
        issue_list.add_issue(issue);
	}

	if (m_y_num_int_positions > 6) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
            m_y_num_int_positions_location,
            "Number of integer positions (Y) > 6 is outside of the official Gerber specification, but is supported by this implementation");
        issue_list.add_issue(issue);
	}

	if (m_y_num_dec_positions > 6) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
            m_y_num_dec_positions_location,
            "Number of decimal positions (Y) > 6 is outside of the official Gerber specification, but is supported by this implementation");
        issue_list.add_issue(issue);
	}

	// Lastly, per the spec, a number of decimal positions < 4 is deprecated
	if (m_x_num_dec_positions < 4) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_DEPRECATED,
            m_x_num_dec_positions_location,
            "Number of decimal positions (X) < 4 is deprecated by the official Gerber specification");
	    issue_list.add_issue(issue);
	}

	if (m_y_num_dec_positions < 4) {
	    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_DEPRECATED,
            m_y_num_dec_positions_location,
            "Number of decimal positions (Y) < 4 is deprecated by the official Gerber specification");
        issue_list.add_issue(issue);
	}	

	// If we get here, we have a semantically valid format specifier
	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& FormatSpecifier::do_print(std::ostream& os) const
{
	os << "Format Specifier (@" << m_location << "):" << std::endl;
	os << "Number of Integer Positions (X): " << m_x_num_int_positions << " @" << m_x_num_int_positions_location << std::endl;
	os << "Number of Decimal Positions (X): " << m_x_num_dec_positions << " @" << m_x_num_dec_positions_location << std::endl;
	os << "Number of Integer Positions (Y): " << m_y_num_int_positions << " @" << m_y_num_int_positions_location << std::endl;
	os << "Number of Decimal Positions (Y): " << m_y_num_dec_positions << " @" << m_y_num_dec_positions_location << std::endl;
	return os;
}
