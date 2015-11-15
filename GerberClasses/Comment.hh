#ifndef _COMMENT_H
#define _COMMENT_H

#include "Command.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>
#include <string>

class Comment : public Command {
public:
	Comment(std::string comment);
	Comment(std::string comment, yy::location location);
	~Comment();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	std::string m_comment;
	yy::location m_location;
};

#endif // _COMMENT_H
