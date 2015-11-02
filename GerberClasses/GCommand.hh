#ifndef _G_COMMAND_H
#define _G_COMMAND_H

#include "Command.hh"

#include <iostream>
#include <string>

class GCommand : public Command {
public:
	enum class GCommandType {
		G_COMMAND_LINEAR_INTERP_MODE,
		G_COMMAND_CW_CIRCULAR_INTERP_MODE,
		G_COMMAND_CCW_CIRCULAR_INTERP_MODE,
		G_COMMAND_SINGLE_QUADRANT_MODE,
		G_COMMAND_MULTI_QUADRANT_MODE,
		G_COMMAND_REGION_MODE_ON,
		G_COMMAND_REGION_MODE_OFF
	};

	GCommand(GCommandType type);
	virtual ~GCommand();

private:
	virtual bool do_check_semantic_validity(std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	GCommandType m_type;
};

#endif // _G_COMMAND_H