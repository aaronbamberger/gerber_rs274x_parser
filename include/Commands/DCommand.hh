#ifndef _D_COMMAND_H
#define _D_COMMAND_H

#include "Commands/Command.hh"
#include "CoordinateData.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <memory>
#include <string>

class DCommand : public Command {
public:
	enum class DCommandType {
		D_COMMAND_INTERPOLATE,
		D_COMMAND_MOVE,
		D_COMMAND_FLASH
	};

	DCommand(DCommandType type, yy::location location);
	DCommand(DCommandType type, std::shared_ptr<CoordinateData> coord_data, yy::location location);
	virtual ~DCommand();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	DCommandType m_type;
	std::shared_ptr<CoordinateData> m_coord_data;
	yy::location m_location;
};

#endif // _D_COMMAND_H
