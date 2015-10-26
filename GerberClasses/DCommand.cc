#include "DCommand.hh"

#include <iostream>

DCommand::DCommand(DCommandType type) : m_type(type)
{}

DCommand::DCommand(DCommandType type, std::unique_ptr<CoordinateData> coord_data) :m_type(type)
{
	// Take ownership of the coordinate data pointer
	m_coord_data = std::move(coord_data);
}

DCommand::~DCommand()
{
	std::cout << "D command destroyed" << std::endl;
}

bool DCommand::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& DCommand::do_print(std::ostream& os) const
{
	os << "D Command: ";
	switch (m_type) {
		case DCommand::DCommandType::D_COMMAND_INTERPOLATE:
			os << "Interpolate" << std::endl;
			break;

		case DCommand::DCommandType::D_COMMAND_MOVE:
			os << "Move" << std::endl;
			break;

		case DCommand::DCommandType::D_COMMAND_FLASH:
			os << "Flash" << std::endl;
			break;
	}

	if (m_coord_data) {
		os << *m_coord_data;
	}

	return os;
}