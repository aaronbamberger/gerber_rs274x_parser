#include "Comment.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>

Comment::Comment(std::string comment) : m_comment(comment)
{}

Comment::~Comment()
{}

Gerber::SemanticValidity Comment::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Otherwise, if comments are syntactically valid, they are also semantically valid
	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& Comment::do_print(std::ostream& os) const
{
	os << "Comment: " << m_comment << std::endl;
	return os;
}
