#include "ApertureDefinitionCustom.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <memory>
#include <list>
#include <string>

ApertureDefinitionCustom::ApertureDefinitionCustom(int aperture_number, char* custom_aperture_name, std::shared_ptr<std::list<double> > modifier_list) : ApertureDefinition(aperture_number),
																																							m_custom_aperture_name(custom_aperture_name),
																																							m_modifier_list(modifier_list)
{}

ApertureDefinitionCustom::ApertureDefinitionCustom(int aperture_number, char* custom_aperture_name) : ApertureDefinition(aperture_number),
																										m_custom_aperture_name(custom_aperture_name)
{}

ApertureDefinitionCustom::~ApertureDefinitionCustom()
{}

Gerber::SemanticValidity ApertureDefinitionCustom::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // TODO: Check that custom aperture macro name is in the aperture macros dictionary

    // Attempt to add this aperture into the aperture dictionary of the graphics state
    // If this fails, it means an aperture with this id has already been defined, which
    // is a fatal error
    auto aperture_def_copy = std::shared_ptr<ApertureDefinition>(new ApertureDefinitionCustom(*this));
    if (!graphics_state.add_aperture_definition(m_aperture_number, aperture_def_copy)) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // We don't need to check the semantic validity of the custom macro this definition is based on,
    // because this was already checked when the custom aperture macro was defined
	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& ApertureDefinitionCustom::do_print(std::ostream& os) const
{
	os << "Custom Aperture Definition: " << m_aperture_number << std::endl;
	os << "Based on Aperture Macro: " << m_custom_aperture_name << std::endl;
	if (m_modifier_list) {
		os << "Modifier List: ";
		for (double modifier : *m_modifier_list) {
			os << modifier << ", ";
		}
		os << std::endl;
	} else {
		os << "No Modifier List" << std::endl;
	}
	return os;
}
