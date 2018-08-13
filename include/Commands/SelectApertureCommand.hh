#ifndef _SELECT_APERTURE_COMMAND_H
#define _SELECT_APERTURE_COMMAND_H

#include "Commands/Command.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>

class SelectApertureCommand : public Command {
public:
	SelectApertureCommand(int aperture_num);
	SelectApertureCommand(int aperture_num, yy::location aperture_num_location, yy::location location);
	virtual ~SelectApertureCommand();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_aperture_num;
	yy::location m_aperture_num_location;
	yy::location m_location;
};

#endif // _SELECT_APERTURE_COMMAND_H
