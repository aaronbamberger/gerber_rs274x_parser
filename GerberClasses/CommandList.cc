#include "CommandList.hh"
#include "../GraphicsState.hh"
#include "GlobalDefs.hh"
#include "Command.hh"

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
    for (auto& command : m_list) {
        auto semantic_validity = command->check_semantic_validity(check_state, error_string);
        switch (semantic_validity) {
        case Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK:
            std::cout << "Validity OK" << std::endl;
            break;

        case Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING:
            std::cout << "Validity Warning" << std::endl;
            break;

        case Gerber::SemanticValidity::SEMANTIC_VALIDITY_DEPRECATED:
            std::cout << "Validity Deprecated" << std::endl;
            break;

        case Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL:
            std::cout << "Validity Fatal" << std::endl;
            break;
        }
    }

    // TODO: Check command-stream global semantic validity
}

std::ostream& operator<<(std::ostream& os, const CommandList& cmd_list)
{
	for (auto& cmd : cmd_list.m_list) {
		os << *cmd;
	}
	return os;
}
