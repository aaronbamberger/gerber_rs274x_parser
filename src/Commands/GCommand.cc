/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Commands/GCommand.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "SemanticIssue.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <string>

GCommand::GCommand(GCommandType type) : m_type(type)
{}

GCommand::GCommand(GCommandType type, yy::location location) : m_type(type), m_location(location)
{}

GCommand::~GCommand()
{}

Gerber::SemanticValidity GCommand::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "No commands are allowed after the end-of-file command has been encountered");
        issue_list.add_issue(issue);
        return issue.severity();
    }

	// Update the graphics state.  This is important for correctly checking the semantic validity
    // of later commands, as their semantic validity depends on the ordering of commands that
    // affect the graphics state
    update_graphics_state(graphics_state);

    // G commands by themselves are always semantically valid
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

void GCommand::update_graphics_state(GraphicsState& graphics_state)
{
    switch (m_type) {
    case GCommand::GCommandType::G_COMMAND_LINEAR_INTERP_MODE:
        graphics_state.set_interp_mode(Gerber::InterpolationMode::INTERPOLATION_MODE_LINEAR);
        break;

    case GCommand::GCommandType::G_COMMAND_CW_CIRCULAR_INTERP_MODE:
        graphics_state.set_interp_mode(Gerber::InterpolationMode::INTERPOLATION_MODE_CW_CIRCULAR);
        break;

    case GCommand::GCommandType::G_COMMAND_CCW_CIRCULAR_INTERP_MODE:
        graphics_state.set_interp_mode(Gerber::InterpolationMode::INTERPOLATION_MODE_CCW_CIRCULAR);
        break;

    case GCommand::GCommandType::G_COMMAND_SINGLE_QUADRANT_MODE:
        graphics_state.set_quadrant_mode(Gerber::QuadrantMode::QUADRANT_MODE_SINGLE);
        break;

    case GCommand::GCommandType::G_COMMAND_MULTI_QUADRANT_MODE:
        graphics_state.set_quadrant_mode(Gerber::QuadrantMode::QUADRANT_MODE_MULTI);
        break;

    case GCommand::GCommandType::G_COMMAND_REGION_MODE_ON:
        graphics_state.set_region_mode_state(Gerber::RegionModeState::REGION_MODE_ON);
        break;

    case GCommand::GCommandType::G_COMMAND_REGION_MODE_OFF:
        graphics_state.set_region_mode_state(Gerber::RegionModeState::REGION_MODE_OFF);
        break;
    }
}

std::ostream& GCommand::do_print(std::ostream& os) const
{
	os << "G Command: ";
	switch (m_type) {
    case GCommand::GCommandType::G_COMMAND_LINEAR_INTERP_MODE:
        os << "Linear Interpolation Mode";
        break;

    case GCommand::GCommandType::G_COMMAND_CW_CIRCULAR_INTERP_MODE:
        os << "Clockwise Circular Interpolation Mode";
        break;

    case GCommand::GCommandType::G_COMMAND_CCW_CIRCULAR_INTERP_MODE:
        os << "Counter-Clockwise Circular Interpolation Mode";
        break;

    case GCommand::GCommandType::G_COMMAND_SINGLE_QUADRANT_MODE:
        os << "Single-Quadrant Mode";
        break;

    case GCommand::GCommandType::G_COMMAND_MULTI_QUADRANT_MODE:
        os << "Multi-Quadrant Mode";
        break;

    case GCommand::GCommandType::G_COMMAND_REGION_MODE_ON:
        os << "Region Mode On";
        break;

    case GCommand::GCommandType::G_COMMAND_REGION_MODE_OFF:
        os << "Region Mode Off";
        break;
	}

	os << " @" << m_location << std::endl;

	return os;
}
