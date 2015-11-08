#include "GCommand.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>

GCommand::GCommand(GCommandType type) : m_type(type)
{}

GCommand::~GCommand()
{}

Gerber::SemanticValidity GCommand::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
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
        os << "Linear Interpolation Mode" << std::endl;
        break;

    case GCommand::GCommandType::G_COMMAND_CW_CIRCULAR_INTERP_MODE:
        os << "Clockwise Circular Interpolation Mode" << std::endl;
        break;

    case GCommand::GCommandType::G_COMMAND_CCW_CIRCULAR_INTERP_MODE:
        os << "Counter-Clockwise Circular Interpolation Mode" << std::endl;
        break;

    case GCommand::GCommandType::G_COMMAND_SINGLE_QUADRANT_MODE:
        os << "Single-Quadrant Mode" << std::endl;
        break;

    case GCommand::GCommandType::G_COMMAND_MULTI_QUADRANT_MODE:
        os << "Multi-Quadrant Mode" << std::endl;
        break;

    case GCommand::GCommandType::G_COMMAND_REGION_MODE_ON:
        os << "Region Mode On" << std::endl;
        break;

    case GCommand::GCommandType::G_COMMAND_REGION_MODE_OFF:
        os << "Region Mode Off" << std::endl;
        break;
	}
	return os;
}
