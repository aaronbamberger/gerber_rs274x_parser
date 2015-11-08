#include "ApertureDefinitionStandard.hh"
#include "StandardAperture.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <memory>
#include <string>

ApertureDefinitionStandard::ApertureDefinitionStandard(int aperture_number, std::shared_ptr<StandardAperture> standard_aperture) : ApertureDefinition(aperture_number),
																																	m_standard_aperture(standard_aperture)
{}

ApertureDefinitionStandard::~ApertureDefinitionStandard()
{}

Gerber::SemanticValidity ApertureDefinitionStandard::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // TODO: Check validity of standard aperture

    // Attempt to add this aperture into the aperture dictionary of the graphics state
    // If this fails, it means an aperture with this id has already been defined, which
    // is a fatal error
    auto aperture_def_copy = std::shared_ptr<ApertureDefinition>(new ApertureDefinitionStandard(*this));
    if (!graphics_state.add_aperture_definition(m_aperture_number, aperture_def_copy)) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // We don't need to check the semantic validity of the custom macro this definition is based on,
    // because this was already checked when the custom aperture macro was defined
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& ApertureDefinitionStandard::do_print(std::ostream& os) const
{
	os << "Standard Aperture Definition: " << m_aperture_number << std::endl;
	os << *m_standard_aperture;
	return os;
}
