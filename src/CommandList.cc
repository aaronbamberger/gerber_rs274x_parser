#include "CommandList.hh"
#include "GlobalDefs.hh"
#include "Commands/Command.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"

#include <memory>
#include <list>
#include <iostream>
#include <string>

CommandList::CommandList()
{}

CommandList::~CommandList()
{}

void CommandList::add_command(std::shared_ptr<Command> command)
{
	m_list.push_back(command);
}

void CommandList::check_semantic_validity()
{
    GraphicsState check_state;
    std::string error_string;
    SemanticIssueList issue_list;
    for (auto& command : m_list) {
        auto semantic_validity = command->check_semantic_validity(check_state, issue_list);
    }
    std::cout << issue_list;

    // TODO: Check command-stream global semantic validity
}

std::ostream& operator<<(std::ostream& os, const CommandList& cmd_list)
{
	for (auto& cmd : cmd_list.m_list) {
		os << *cmd;
	}
	return os;
}
