#include "SelectApertureCommand.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>
#include <cstdint>

SelectApertureCommand::SelectApertureCommand(int aperture_num) : m_aperture_num(aperture_num)
{}

SelectApertureCommand::~SelectApertureCommand()
{}

Gerber::SemanticValidity SelectApertureCommand::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Select aperture commands are not allowed when region mode is on.
    // If a select aperture command is encountered while region mode is on,
    // we consider it a fatal error
    if (graphics_state.current_region_mode_state() == Gerber::RegionModeState::REGION_MODE_ON) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Per the spec, the allowed range of aperture numbers is [10, INT32_MAX].  We'll treat numbers
    // outside of that range as fatal errors, as the gerber spec reserves them
    if ((m_aperture_num < 10) || (m_aperture_num > INT32_MAX)) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Attempt to update the current aperture in the graphics state.  This will fail
    // if the aperture isn't in the aperture dictionary of the graphics state
    // (which is true if the aperture we're attempting to switch to hasn't been defined yet)
    // This is a fatal error
    if (!graphics_state.set_current_aperture(m_aperture_num)) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& SelectApertureCommand::do_print(std::ostream& os) const
{
	os << "Select Aperture: " << m_aperture_num << std::endl;
	return os;
}
