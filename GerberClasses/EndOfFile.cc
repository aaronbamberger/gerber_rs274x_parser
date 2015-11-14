#include "EndOfFile.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>
#include <string>

EndOfFile::EndOfFile()
{}

EndOfFile::EndOfFile(yy::location location) : m_location(location)
{}

EndOfFile::~EndOfFile()
{}

Gerber::SemanticValidity EndOfFile::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // Seeing an end of file while region mode is on is a fatal error
    if (graphics_state.current_region_mode_state() == Gerber::RegionModeState::REGION_MODE_ON) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Attempt to set end-of-file on the graphics state.  This will fail if an end-of-file
    // command has already been encountered, which is a fatal error
    if (!graphics_state.set_file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& EndOfFile::do_print(std::ostream& os) const
{
	os << "End of File @" << m_location << std::endl;
	return os;
}
