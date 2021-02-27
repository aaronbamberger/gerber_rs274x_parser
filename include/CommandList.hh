/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _COMMAND_LIST_H
#define _COMMAND_LIST_H

#include "Commands/Command.hh"

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
