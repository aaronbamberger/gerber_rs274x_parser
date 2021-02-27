/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Commands/Command.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"

#include <iostream>
#include <string>

Command::Command()
{}

Command::~Command()
{}

Gerber::SemanticValidity Command::check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    return do_check_semantic_validity(graphics_state, issue_list);
}

std::ostream& operator<<(std::ostream& os, const Command& cmd)
{
	return cmd.do_print(os);
}
