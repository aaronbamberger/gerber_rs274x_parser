#ifndef _FORMAT_SPECIFIER_H
#define _FORMAT_SPECIFIER_H

#include "Command.hh"

#include <iostream>
#include <string>

class FormatSpecifier : public Command {
public:
	FormatSpecifier(int num_int_positions, int num_dec_positions);
	~FormatSpecifier();

private:
	virtual bool do_check_semantic_validity(std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_num_int_positions;
	int m_num_dec_positions;
};

#endif // _FORMAT_SPECIFIER_H