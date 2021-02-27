/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Commands/ApertureDefinitionCustom.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "Commands/ApertureMacro.hh"
#include "Commands/ApertureDefinitionModifier.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <memory>
#include <list>
#include <string>

ApertureDefinitionCustom::ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name, std::shared_ptr<std::list<ApertureDefinitionModifier> > modifier_list) :
    ApertureDefinition(aperture_number), m_custom_aperture_name(custom_aperture_name), m_modifier_list(modifier_list)
{}

ApertureDefinitionCustom::ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name) :
    ApertureDefinition(aperture_number), m_custom_aperture_name(custom_aperture_name)
{}

ApertureDefinitionCustom::ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name, std::shared_ptr<std::list<ApertureDefinitionModifier> > modifier_list,
    yy::location aperture_number_location, yy::location aperture_name_location, yy::location modifier_list_location, yy::location location) :
        ApertureDefinition(aperture_number, aperture_number_location, location), m_custom_aperture_name(custom_aperture_name), m_modifier_list(modifier_list),
        m_aperture_name_location(aperture_name_location), m_modifier_list_location(modifier_list_location)
{}

ApertureDefinitionCustom::ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name,
    yy::location aperture_number_location, yy::location aperture_name_location, yy::location location) :
        ApertureDefinition(aperture_number, aperture_number_location, location), m_custom_aperture_name(custom_aperture_name),
        m_aperture_name_location(aperture_name_location)
{}

ApertureDefinitionCustom::~ApertureDefinitionCustom()
{}

Gerber::SemanticValidity ApertureDefinitionCustom::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // TODO: Implement adding issues to issue list

    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Check to see if the aperture macro that this definition is referencing has been
    // added to the aperture macro template dictionary in the graphics state.
    // If it hasn't it's a fatal error
    if (!graphics_state.check_aperture_macro(m_custom_aperture_name)) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Initialize the variable environment with the contents of the modifier list
    ApertureMacroVariableEnvironment variable_env;
    int variable_num = 1;
    for (auto modifier : *m_modifier_list) {
        // TODO: Insert variable location as well
        variable_env.set_variable(variable_num++, modifier.m_value);
    }
    // Lookup the macro from the aperture template dictionary
    auto aperture_macro = graphics_state.lookup_aperture_macro(m_custom_aperture_name);
    // Instantiate the aperture macro
    auto instantiated_aperture = aperture_macro->instantiate(variable_env);

    // Attempt to add this aperture into the aperture dictionary of the graphics state
    // If this fails, it means an aperture with this id has already been defined, which
    // is a fatal error
    if (!graphics_state.define_aperture(m_aperture_number, instantiated_aperture)) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // We don't need to check the semantic validity of the custom macro this definition is based on,
    // because this was already checked when the custom aperture macro was defined
	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& ApertureDefinitionCustom::do_print(std::ostream& os) const
{
	os << "Custom Aperture Definition: (@" << m_location << ")" << std::endl;
	os << "Aperture ID: " << m_aperture_number << " (@" << m_aperture_number_location << ")" << std::endl;
	os << "Based on Aperture Macro: " << m_custom_aperture_name << " (@" << m_aperture_name_location << ")" << std::endl;
	if (m_modifier_list) {
		os << "Modifier List: ";
		for (auto modifier : *m_modifier_list) {
			os << modifier.m_value << " (@" << modifier.m_location << ")" << ", ";
		}
		os << std::endl;
	} else {
		os << "No Modifier List" << std::endl;
	}
	return os;
}
