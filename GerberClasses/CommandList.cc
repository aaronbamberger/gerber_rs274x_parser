#include "CommandList.hh"

#include <memory>
#include <list>
#include <iostream>

CommandList::CommandList()
{}

void CommandList::add_command(std::shared_ptr<Command> command)
{
	m_list.push_back(command);
}

std::ostream& operator<<(std::ostream& os, const CommandList& cmd_list)
{
	for (auto& cmd : cmd_list.m_list) {
		os << *cmd;
	}
	return os;
}