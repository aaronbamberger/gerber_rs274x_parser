#ifndef _COMMAND_H
#define _COMMAND_H

#include "GlobalDefs.hh"

#include <string>
#include <iostream>
#include <string>

// Forward declare the GraphicsState class to break a circular dependency
class GraphicsState;

class Command {
public:
	Command();
	virtual ~Command();

	Gerber::SemanticValidity check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg);
	friend std::ostream& operator<<(std::ostream& os, const Command& cmd);	

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg) = 0;
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _COMMAND_H
