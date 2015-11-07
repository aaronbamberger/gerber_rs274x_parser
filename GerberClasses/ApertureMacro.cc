#include "ApertureMacro.hh"
#include "ApertureMacroContent.hh"

#include <iostream>
#include <memory>
#include <string>
#include <list>

ApertureMacro::ApertureMacro(char* macro_name, std::shared_ptr<std::list<std::shared_ptr<ApertureMacroContent> > > macro_content_list) : m_macro_name(macro_name), m_macro_content_list(macro_content_list)
{}

ApertureMacro::~ApertureMacro()
{}

bool ApertureMacro::do_check_semantic_validity(std::string& error_msg)
{
	return false;
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