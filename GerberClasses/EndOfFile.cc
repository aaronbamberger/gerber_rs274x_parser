#include "EndOfFile.hh"

#include <iostream>
#include <string>

EndOfFile::EndOfFile()
{}

EndOfFile::~EndOfFile()
{}

bool EndOfFile::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& EndOfFile::do_print(std::ostream& os) const
{
	os << "End of File" << std::endl;
	return os;
}