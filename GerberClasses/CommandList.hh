#ifndef _COMMAND_LIST_H
#define _COMMAND_LIST_H

#include "Command.hh"

#include <iostream>
#include <memory>
#include <list>

class CommandList {
public:
	CommandList();
	~CommandList();

	void add_command(std::shared_ptr<Command> command);

	void check_semantic_validity();

	friend std::ostream& operator<<(std::ostream& os, const CommandList& cmd_list);

private:
	std::list<std::shared_ptr< Command> > m_list;
};



#endif // _COMMAND_LIST_H
