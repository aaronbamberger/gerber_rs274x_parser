#include "ApertureMacro.hh"
#include "ApertureMacroContent.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <memory>
#include <string>
#include <list>

ApertureMacro::ApertureMacro(char* macro_name, std::shared_ptr<std::list<std::shared_ptr<ApertureMacroContent> > > macro_content_list) : m_macro_name(macro_name), m_macro_content_list(macro_content_list)
{}

ApertureMacro::~ApertureMacro()
{}

Gerber::SemanticValidity ApertureMacro::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // TODO: Check semantic validity of aperture macro

	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& ApertureMacro::do_print(std::ostream& os) const
{
	os << "Aperture Macro: " << m_macro_name << std::endl;
	os << "Macro Contents:" << std::endl;
	int i = 0;
	for (auto macro_content : *m_macro_content_list) {
		// Type of macro content should be std::shared_ptr<ApertureMacroContent>
		os << "Element " << i++ << ":" << std::endl;
		os << *(macro_content);
	}
	return os;
}
