#include "Comment.hh"

#include <iostream>
#include <string>

Comment::Comment(char* comment) : m_comment(comment)
{}

Comment::~Comment()
{}

bool Comment::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& Comment::do_print(std::ostream& os) const
{
	os << "Comment: " << m_comment << std::endl;
	return os;
}