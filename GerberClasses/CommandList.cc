#include "CommandList.hh"

#include <memory>
#include <list>

CommandList::CommandList()
{}

void CommandList::add_command(std::unique_ptr<Command> command)
{
	m_list.push_back(std::move(command));
}