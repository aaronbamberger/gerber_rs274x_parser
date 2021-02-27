/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Commands/DCommand.hh"
#include "Commands/FormatSpecifier.hh"
#include "Commands/UnitSpecifier.hh"
#include "SemanticIssueList.hh"
#include "SemanticIssue.hh"
#include "GraphicsState.hh"
#include "location.hh"
#include "GlobalDefs.hh"

#include <iostream>

DCommand::DCommand(DCommandType type, yy::location location) : m_type(type), m_location(location)
{}

DCommand::DCommand(DCommandType type, std::shared_ptr<CoordinateData> coord_data, yy::location location) :
	m_type(type), m_coord_data(coord_data), m_location(location)
{}

DCommand::~DCommand()
{}

Gerber::SemanticValidity DCommand::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "No commands are allowed after the end-of-file command has been encountered");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // There are a number of graphics state parameters that start undefined and need to be
    // set before any drawing commands are executed.  If any of the graphics state parameters
    // required for drawing aren't set by the time we encounter drawing commands, it's a fatal error

    // Coordinate format needs to be defined for all drawing commands
    if (!graphics_state.coord_format()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "Drawing commands require the coordinate format (FS Command) to be set prior to use");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // Unit type needs to be defined for all drawing commands
    if (graphics_state.unit_type() == Gerber::UnitType::UNIT_TYPE_UNDEFINED) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "Drawing commands require the unit type (MO Command) to be set prior to use");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // Current aperture needs to be defined for interpolate commands if region mode is off,
    // and always needs to be defined for flash commands.  It never needs to be defined for
    // move commands
    if (graphics_state.current_aperture() == -1) {
        switch (m_type) {
        case DCommand::DCommandType::D_COMMAND_INTERPOLATE:
            if (graphics_state.current_region_mode_state() == Gerber::RegionModeState::REGION_MODE_OFF) {
                SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
                    m_location,
                    "The current aperture must be defined prior to use of an interpolate command if region mode is off");
                issue_list.add_issue(issue);
                return issue.severity();
            }
            break;

        case DCommand::DCommandType::D_COMMAND_FLASH:
            SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
                m_location,
                "The current aperture must be defined prior to use of a flash command");
            issue_list.add_issue(issue);
            return issue.severity();
            break;
        }
    }

    // Interpolation mode needs to be defined if this is an interpolate command
    if (m_type == DCommand::DCommandType::D_COMMAND_INTERPOLATE) {
        if (graphics_state.current_interp_mode() == Gerber::InterpolationMode::INTERPOLATION_MODE_UNDEFINED) {
            SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
                m_location,
                "The interpolation mode (G01/G02/G03 Commands) must be defined prior to use of an interpolate command");
            issue_list.add_issue(issue);
            return issue.severity();
        }
    }

    // Quadrant mode needs to be defined if this is an interpolate command and we're in one of the circular interpolation modes
    if (m_type == DCommand::DCommandType::D_COMMAND_INTERPOLATE) {
        Gerber::InterpolationMode interp_mode = graphics_state.current_interp_mode();
        if ((interp_mode == Gerber::InterpolationMode::INTERPOLATION_MODE_CW_CIRCULAR) || (interp_mode == Gerber::InterpolationMode::INTERPOLATION_MODE_CCW_CIRCULAR)) {
            if (graphics_state.current_quadrant_mode() == Gerber::QuadrantMode::QUADRANT_MODE_UNDEFINED) {
                SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
                    m_location,
                    "The quadrant mode (G74/G75 Commands) must be defined prior to use of an interpolate command with one of the circular interpolation modes (G02/G03 Commands) set");
                issue_list.add_issue(issue);
                return issue.severity();
            }
        }
    }

    if (m_coord_data) {
        // If there's coordinate data, validate the coordinate data itself before doing any validation
        // that requires information about the D command
        if (m_coord_data->check_semantic_validity(graphics_state, issue_list) == Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL) {
            return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
        }

        // I and J values are never allowed for move and flash commands, and are only allowed
        // in interpolate commands if we're in one of the circular interpolation modes
        // We'll treat these as warnings, because we can just ignore them if they appear in an
        // invalid context
        switch (m_type) {
        case DCommand::DCommandType::D_COMMAND_MOVE:
        case DCommand::DCommandType::D_COMMAND_FLASH:
            if (m_coord_data->i_valid() || m_coord_data->j_valid()) {
                yy::location warning_loc;
                if (m_coord_data->i_valid() && m_coord_data->j_valid()) {
                    warning_loc = m_coord_data->ij_loc();
                } else if (m_coord_data->i_valid()) {
                    warning_loc = m_coord_data->i_loc();
                } else  if (m_coord_data->j_valid()) {
                    warning_loc = m_coord_data->j_loc();
                }

                SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
                    warning_loc,
                    "Use of Center Offsets (I/J Coordinates) is meaningless for move and flash commands, and is invalid. I/J coordinates will be ignored");
                issue_list.add_issue(issue);
            }
            break;

        case DCommand::DCommandType::D_COMMAND_INTERPOLATE:
        {
            Gerber::InterpolationMode interp_mode = graphics_state.current_interp_mode();
            if ((interp_mode != Gerber::InterpolationMode::INTERPOLATION_MODE_CW_CIRCULAR) && (interp_mode != Gerber::InterpolationMode::INTERPOLATION_MODE_CCW_CIRCULAR)) {
                if (m_coord_data->i_valid() || m_coord_data->j_valid()) {
                    yy::location warning_loc;
                    if (m_coord_data->i_valid() && m_coord_data->j_valid()) {
                        warning_loc = m_coord_data->ij_loc();
                    } else if (m_coord_data->i_valid()) {
                        warning_loc = m_coord_data->i_loc();
                    } else  if (m_coord_data->j_valid()) {
                        warning_loc = m_coord_data->j_loc();
                    }

                    SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
                        warning_loc,
                        "Use of Center Offsets (I/J Coordinates) is meaningless for interpolation commands in linear interpolation mode, and is invalid.  I/J coordinates will be ignored");
                    issue_list.add_issue(issue);
                }
            }
        }
        break;
        }
    }

    // Flash commands aren't allowed when region mode is on.  We'll treat these as warnings
    // and just ignore flash commands while region mode is on
    if ((m_type == DCommand::DCommandType::D_COMMAND_FLASH) && (graphics_state.current_region_mode_state() == Gerber::RegionModeState::REGION_MODE_ON)) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING,
            m_location,
            "Flash commands are meaningless when region mode is on, and are invalid.  Flash command will be ignored");
        issue_list.add_issue(issue);
    }

    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& DCommand::do_print(std::ostream& os) const
{
	os << "D Command: ";
	switch (m_type) {
    case DCommand::DCommandType::D_COMMAND_INTERPOLATE:
        os << "Interpolate";
        break;

    case DCommand::DCommandType::D_COMMAND_MOVE:
        os << "Move";
        break;

    case DCommand::DCommandType::D_COMMAND_FLASH:
        os << "Flash";
        break;
	}

	os << " (@" << m_location << ")" << std::endl;

	if (m_coord_data) {
		os << *m_coord_data;
	}

	return os;
}
