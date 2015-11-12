#include "ApertureMacro.hh"
#include "ApertureMacroContent.hh"
#include "GlobalDefs.hh"
#include "InstantiatedApertureMacro.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <memory>
#include <string>
#include <list>

ApertureMacro::ApertureMacro(char* macro_name, std::shared_ptr<std::list<std::shared_ptr<ApertureMacroContent> > > macro_content) : m_macro_name(macro_name), m_macro_content(macro_content)
{}

ApertureMacro::~ApertureMacro()
{}

std::string& ApertureMacro::macro_name()
{
    return m_macro_name;
}

std::shared_ptr<InstantiatedApertureMacro> ApertureMacro::instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    auto instantiated_macro = std::make_shared<InstantiatedApertureMacro>();
    for (auto macro_content : *m_macro_content) {
        auto instantiated_content = macro_content->instantiate(variable_env);
        // A null pointer may be returned, which means that what was "instantiated" was a variable
        // definition.  This simply adds the defined variable to the environment, but since there
        // is no aperture primitive to instantiate, nothing is returned
        if (instantiated_content) {
            instantiated_macro->add_instantiated_macro_content(instantiated_content);
        }
    }

    return instantiated_macro;
}

Gerber::SemanticValidity ApertureMacro::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // We can't check the validity of the macro itself until it is instantiated, because we can't
    // evaluate the primitive modifiers in general until they are bound by an aperture definition,
    // so we validate the instantiated aperture when it is used in an aperture definition
    // and we can evaluate the modifiers properly

    // Attempt to add the macro to the aperture template dictionary
    // of the graphics state.  If this fails, it means that a macro with the same name has already
    // been inserted into the template dictionary, which is a fatal error
    if (!graphics_state.add_aperture_macro(std::shared_ptr<ApertureMacro>(new ApertureMacro(*this)))) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& ApertureMacro::do_print(std::ostream& os) const
{
	os << "Aperture Macro: " << m_macro_name << std::endl;
	os << "Macro Contents:" << std::endl;
	int i = 0;
	for (auto macro_content : *m_macro_content) {
		// Type of macro content should be std::shared_ptr<ApertureMacroContent>
		os << "Element " << i++ << ":" << std::endl;
		os << *(macro_content);
	}
	return os;
}
