#include "ApertureDefinitionCustom.hh"

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

bool ApertureDefinitionCustom::do_check_semantic_validity(std::string& error_msg)
{
	return false;
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