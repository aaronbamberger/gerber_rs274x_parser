#ifndef _D_COMMAND_H
#define _D_COMMAND_H

#include "Command.hh"
#include "CoordinateData.hh"

#include <iostream>
#include <memory>

class DCommand : public Command {
public:
	enum class DCommandType {
		D_COMMAND_INTERPOLATE,
		D_COMMAND_MOVE,
		D_COMMAND_FLASH
	};

	DCommand(DCommandType type);
	DCommand(DCommandType type, std::unique_ptr<CoordinateData> coord_data);
	virtual ~DCommand();

protected:
	virtual bool do_check_semantic_validity(std::string& error_msg);

private:
	virtual std::ostream& do_print(std::ostream& os) const;

	DCommandType m_type;
	std::unique_ptr<CoordinateData> m_coord_data;
};

#endif // _D_COMMAND_H