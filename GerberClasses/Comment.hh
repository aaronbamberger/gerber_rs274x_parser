#ifndef _COMMENT_H
#define _COMMENT_H

#include "Command.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>

class Comment : public Command {
public:
	Comment(char* comment);
	~Comment();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	std::string m_comment;
};

#endif // _COMMENT_H
