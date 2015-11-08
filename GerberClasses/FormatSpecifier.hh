#ifndef _FORMAT_SPECIFIER_H
#define _FORMAT_SPECIFIER_H

#include "Command.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>

class FormatSpecifier : public Command {
public:
	FormatSpecifier(int x_num_int_positions, int x_num_dec_positions, int y_num_int_positions, int y_num_dec_positions);
	~FormatSpecifier();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_x_num_int_positions;
	int m_x_num_dec_positions;
	int m_y_num_int_positions;
	int m_y_num_dec_positions;
};

#endif // _FORMAT_SPECIFIER_H