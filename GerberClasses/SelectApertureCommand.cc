#include "SelectApertureCommand.hh"

#include <iostream>
#include <string>

SelectApertureCommand::SelectApertureCommand(int aperture_num) : m_aperture_num(aperture_num)
{}

SelectApertureCommand::~SelectApertureCommand()
{}

bool SelectApertureCommand::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& SelectApertureCommand::do_print(std::ostream& os) const
{
	os << "Select Aperture: " << m_aperture_num << std::endl;
	return os;
}