#include "FormatSpecifier.hh"

#include <iostream>
#include <string>

FormatSpecifier::FormatSpecifier(int num_int_positions, int num_dec_positions) : m_num_int_positions(num_int_positions),
																					m_num_dec_positions(num_dec_positions)
{}

FormatSpecifier::~FormatSpecifier()
{}

bool FormatSpecifier::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& FormatSpecifier::do_print(std::ostream& os) const
{
	os << "Format Specifier:" << std::endl;
	os << "Number of Integer Positions: " << m_num_int_positions << std::endl;
	os << "Number of Decimal Positions: " << m_num_dec_positions << std::endl;
	return os;
}