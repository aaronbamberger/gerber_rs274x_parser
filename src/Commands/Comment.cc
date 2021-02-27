/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Commands/Comment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <string>

Comment::Comment(std::string comment) : m_comment(comment)
{}

Comment::Comment(std::string comment, yy::location location) : m_comment(comment), m_location(location)
{}

Comment::~Comment()
{}

Gerber::SemanticValidity Comment::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "No commands are allowed after the end-of-file command has been encountered");
        issue_list.add_issue(issue);
        return issue.severity();
    }

    // Otherwise, if comments are syntactically valid, they are also semantically valid
	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& Comment::do_print(std::ostream& os) const
{
	os << "Comment: " << m_comment << " (@" << m_location <<  ")" << std::endl;
	return os;
}
