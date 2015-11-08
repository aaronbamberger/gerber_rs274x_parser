#include "Command.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>

Command::Command()
{}

Command::~Command()
{}

Gerber::SemanticValidity Command::check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    return do_check_semantic_validity(graphics_state, error_msg);
}

std::ostream& operator<<(std::ostream& os, const Command& cmd)
{
	return cmd.do_print(os);
}
