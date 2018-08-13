#ifndef _FORMAT_SPECIFIER_H
#define _FORMAT_SPECIFIER_H

#include "Commands/Command.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <string>

class FormatSpecifier : public Command {
public:
	FormatSpecifier(int x_num_int_positions, int x_num_dec_positions, int y_num_int_positions, int y_num_dec_positions);
	FormatSpecifier(int x_num_int_positions, int x_num_dec_positions, int y_num_int_positions, int y_num_dec_positions,
	        yy::location x_num_int_positions_location, yy::location x_num_dec_positions_location,
	        yy::location y_num_int_positions_location, yy::location y_num_dec_positions_location,
	        yy::location location);
	~FormatSpecifier();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_x_num_int_positions;
	int m_x_num_dec_positions;
	int m_y_num_int_positions;
	int m_y_num_dec_positions;

	yy::location m_x_num_int_positions_location;
	yy::location m_x_num_dec_positions_location;
	yy::location m_y_num_int_positions_location;
	yy::location m_y_num_dec_positions_location;
	yy::location m_location;
};

#endif // _FORMAT_SPECIFIER_H
