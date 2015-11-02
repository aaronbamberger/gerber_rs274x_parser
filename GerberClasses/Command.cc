#include "Command.hh"

#include <iostream>

Command::Command()
{}

Command::~Command()
{}

std::ostream& operator<<(std::ostream& os, const Command& cmd)
{
	return cmd.do_print(os);
}