#ifndef _COMMAND_LIST_H
#define _COMMAND_LIST_H

#include "Command.hh"

#include <iostream>
#include <memory>
#include <list>

class CommandList {
public:
	CommandList();

	void add_command(std::unique_ptr<Command> command);

	friend std::ostream& operator<<(std::ostream& os, const CommandList& cmd_list);

private:
	std::list<std::unique_ptr< Command> > m_list;
};

std::ostream& operator<<(std::ostream& os, const CommandList& cmd_list)
{
	for (auto& cmd : cmd_list.m_list) {
		os << *cmd;
	}
	return os;
}

#endif // _COMMAND_LIST_H