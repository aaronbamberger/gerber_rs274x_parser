#include "ApertureDefinitionStandard.hh"
#include "StandardAperture.hh"

#include <iostream>
#include <memory>
#include <string>

ApertureDefinitionStandard::ApertureDefinitionStandard(int aperture_number, std::shared_ptr<StandardAperture> standard_aperture) : ApertureDefinition(aperture_number),
																																	m_standard_aperture(standard_aperture)
{}

ApertureDefinitionStandard::~ApertureDefinitionStandard()
{}

bool ApertureDefinitionStandard::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& ApertureDefinitionStandard::do_print(std::ostream& os) const
{
	os << "Standard Aperture Definition: " << m_aperture_number << std::endl;
	os << *m_standard_aperture;
	return os;
}