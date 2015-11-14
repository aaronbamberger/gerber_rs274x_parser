#include "DCommand.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"
#include "../location.hh"
#include "FormatSpecifier.hh"
#include "UnitSpecifier.hh"

#include <iostream>

DCommand::DCommand(DCommandType type, yy::location location) : m_type(type), m_location(location)
{}

DCommand::DCommand(DCommandType type, std::shared_ptr<CoordinateData> coord_data, yy::location location) :
	m_type(type), m_coord_data(coord_data), m_location(location)
{}

DCommand::~DCommand()
{}

Gerber::SemanticValidity DCommand::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // There are a number of graphics state parameters that start undefined and need to be
    // set before any drawing commands are executed.  If any of the graphics state parameters
    // required for drawing aren't set by the time we encounter drawing commands, it's a fatal error

    // Coordinate format needs to be defined for all drawing commands
    if (!graphics_state.coord_format()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Unit type needs to be defined for all drawing commands
    if (graphics_state.unit_type() == Gerber::UnitType::UNIT_TYPE_UNDEFINED) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Current aperture needs to be defined for interpolate commands if region mode is off,
    // and always needs to be defined for flash commands.  It never needs to be defined for
    // move commands
    if (graphics_state.current_aperture() == -1) {
        switch (m_type) {
        case DCommand::DCommandType::D_COMMAND_INTERPOLATE:
            if (graphics_state.current_region_mode_state() == Gerber::RegionModeState::REGION_MODE_OFF) {
                return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
            }
            break;

        case DCommand::DCommandType::D_COMMAND_FLASH:
            return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
            break;
        }
    }

    // Interpolation mode needs to be defined if this is an interpolate command
    if (m_type == DCommand::DCommandType::D_COMMAND_INTERPOLATE) {
        if (graphics_state.current_interp_mode() == Gerber::InterpolationMode::INTERPOLATION_MODE_UNDEFINED) {
            return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
        }
    }

    // Quadrant mode needs to be defined if this is an interpolate command and we're in one of the circular interpolation modes
    if (m_type == DCommand::DCommandType::D_COMMAND_INTERPOLATE) {
        Gerber::InterpolationMode interp_mode = graphics_state.current_interp_mode();
        if ((interp_mode == Gerber::InterpolationMode::INTERPOLATION_MODE_CW_CIRCULAR) || (interp_mode == Gerber::InterpolationMode::INTERPOLATION_MODE_CCW_CIRCULAR)) {
            if (graphics_state.current_quadrant_mode() == Gerber::QuadrantMode::QUADRANT_MODE_UNDEFINED) {
                return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
            }
        }
    }

	// I and J values are never allowed for move and flash commands, and are only allowed
    // in interpolate commands if we're in one of the circular interpolation modes
    // We'll treat these as warnings, because we can just ignore them if they appear in an
    // invalid context
    switch (m_type) {
    case DCommand::DCommandType::D_COMMAND_MOVE:
    case DCommand::DCommandType::D_COMMAND_FLASH:
        if (m_coord_data->i_valid() || m_coord_data->j_valid()) {
            return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
        }
        break;

    case DCommand::DCommandType::D_COMMAND_INTERPOLATE:
    {
        Gerber::InterpolationMode interp_mode = graphics_state.current_interp_mode();
        if ((interp_mode != Gerber::InterpolationMode::INTERPOLATION_MODE_CW_CIRCULAR) && (interp_mode != Gerber::InterpolationMode::INTERPOLATION_MODE_CCW_CIRCULAR)) {
            if (m_coord_data->i_valid() || m_coord_data->j_valid()) {
                return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
            }
        }
    }
    break;
    }

    // Flash commands aren't allowed when region mode is on.  We'll treat these as warnings
    // and just ignore flash commands while region mode is on
    if ((m_type == DCommand::DCommandType::D_COMMAND_FLASH) && (graphics_state.current_region_mode_state() == Gerber::RegionModeState::REGION_MODE_ON)) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
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

	os << " @" << m_location << std::endl;

	if (m_coord_data) {
		os << *m_coord_data;
	}

	return os;
}
