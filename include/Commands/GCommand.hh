/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _G_COMMAND_H
#define _G_COMMAND_H

#include "Commands/Command.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>

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
	GCommand(GCommandType type, yy::location location);
	virtual ~GCommand();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	void update_graphics_state(GraphicsState& graphics_state);

	GCommandType m_type;
	yy::location m_location;
};

#endif // _G_COMMAND_H
