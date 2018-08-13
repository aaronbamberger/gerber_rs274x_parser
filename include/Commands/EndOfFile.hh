#ifndef _END_OF_FILE_H
#define _END_OF_FILE_H

#include "Commands/Command.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>

class EndOfFile : public Command {
public:
	EndOfFile();
	EndOfFile(yy::location location);
	~EndOfFile();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	yy::location m_location;
};

#endif // _END_OF_FILE_H
