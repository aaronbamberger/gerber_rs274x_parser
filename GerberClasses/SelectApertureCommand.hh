#ifndef _SELECT_APERTURE_COMMAND_H
#define _SELECT_APERTURE_COMMAND_H

#include "Command.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>

class SelectApertureCommand : public Command {
public:
	SelectApertureCommand(int aperture_num);
	virtual ~SelectApertureCommand();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_aperture_num;
};

#endif // _SELECT_APERTURE_COMMAND_H
