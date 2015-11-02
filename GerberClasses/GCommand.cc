#include "GCommand.hh"

#include <iostream>
#include <string>

GCommand::GCommand(GCommandType type) : m_type(type)
{}

GCommand::~GCommand()
{}

bool GCommand::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& GCommand::do_print(std::ostream& os) const
{
	os << "G Command: ";
	switch (m_type) {
		case GCommand::GCommandType::G_COMMAND_LINEAR_INTERP_MODE:
			os << "Linear Interpolation Mode" << std::endl;
			break;

		case GCommand::GCommandType::G_COMMAND_CW_CIRCULAR_INTERP_MODE:
			os << "Clockwise Circular Interpolation Mode" << std::endl;
			break;

		case GCommand::GCommandType::G_COMMAND_CCW_CIRCULAR_INTERP_MODE:
			os << "Counter-Clockwise Circular Interpolation Mode" << std::endl;
			break;

		case GCommand::GCommandType::G_COMMAND_SINGLE_QUADRANT_MODE:
			os << "Single-Quadrant Mode" << std::endl;
			break;

		case GCommand::GCommandType::G_COMMAND_MULTI_QUADRANT_MODE:
			os << "Multi-Quadrant Mode" << std::endl;
			break;

		case GCommand::GCommandType::G_COMMAND_REGION_MODE_ON:
			os << "Region Mode On" << std::endl;
			break;

		case GCommand::GCommandType::G_COMMAND_REGION_MODE_OFF:
			os << "Region Mode Off" << std::endl;
			break;
	}
	return os;
}