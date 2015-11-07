#include "ApertureMacroPrimitiveComment.hh"

#include <iostream>
#include <string>

ApertureMacroPrimitiveComment::ApertureMacroPrimitiveComment(char* comment) : m_comment(comment)
{}

ApertureMacroPrimitiveComment::~ApertureMacroPrimitiveComment()
{}

std::ostream& ApertureMacroPrimitiveComment::do_print(std::ostream& os) const
{
	os << "Macro Primitive Comment: " << m_comment << std::endl;
	return os;
}