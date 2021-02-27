/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Commands/SelectApertureCommand.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <string>
#include <cstdint>
#include <climits>

SelectApertureCommand::SelectApertureCommand(int aperture_num) : m_aperture_num(aperture_num)
{}

SelectApertureCommand::SelectApertureCommand(int aperture_num, yy::location aperture_num_location, yy::location location) :
    m_aperture_num(aperture_num), m_aperture_num_location(aperture_num_location), m_location(location)
{}

SelectApertureCommand::~SelectApertureCommand()
{}

Gerber::SemanticValidity SelectApertureCommand::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "No commands are allowed after the end-of-file command has been encountered");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // Select aperture commands are not allowed when region mode is on.
    // If a select aperture command is encountered while region mode is on,
    // we consider it a fatal error
    if (graphics_state.current_region_mode_state() == Gerber::RegionModeState::REGION_MODE_ON) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "Select aperture commands are not allowed when region mode is on");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // Per the spec, the allowed range of aperture numbers is [10, INT32_MAX].  We'll treat numbers
    // under 10 as fatal errors, as the gerber spec reserves them, but numbers above INT32_MAX as
    // warnings if the current platform's int max is greater than 32-bit int max, as we can
    // therefore handle aperture numbers greater than INT32_MAX.  If INT_MAX < INT32_MAX on this
    // platform, then an aperture number > INT_MAX will wrap negative, and will get treated
    // as a fatal error
    if (m_aperture_num < 10) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_aperture_num_location,
            "Aperture IDs below 10 are reserved by the Gerber specification, and are not allowed");
        issue_list.add_issue(issue);
        return issue.severity();
    } else if ((INT_MAX > INT32_MAX) && (m_aperture_num > INT32_MAX)) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
            m_aperture_num_location,
            "Aperture IDs above 2,147,483,647 (INT32_MAX) are outside of the official Gerber specification, however this implementation supports them");
        issue_list.add_issue(issue);
    }

    // Attempt to update the current aperture in the graphics state.  This will fail
    // if the aperture isn't in the aperture dictionary of the graphics state
    // (which is true if the aperture we're attempting to switch to hasn't been defined yet)
    // This is a fatal error
    if (!graphics_state.set_current_aperture(m_aperture_num)) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_aperture_num_location,
            "It is invalid to select an aperture which hasn't been previously defined by an AD command");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& SelectApertureCommand::do_print(std::ostream& os) const
{
	os << "Select Aperture: " << m_aperture_num << " @" << m_location << std::endl;
	return os;
}
