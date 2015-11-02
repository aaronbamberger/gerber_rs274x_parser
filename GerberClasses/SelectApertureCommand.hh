#ifndef _SELECT_APERTURE_COMMAND_H
#define _SELECT_APERTURE_COMMAND_H

#include "Command.hh"

#include <iostream>
#include <string>

class SelectApertureCommand : public Command {
public:
	SelectApertureCommand(int aperture_num);
	virtual ~SelectApertureCommand();

private:
	virtual bool do_check_semantic_validity(std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_aperture_num;
};

#endif // _SELECT_APERTURE_COMMAND_H