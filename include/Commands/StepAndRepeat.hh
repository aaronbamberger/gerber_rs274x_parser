/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _STEP_AND_REPEAT_H
#define _STEP_AND_REPEAT_H

#include "Commands/Command.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>

class StepAndRepeat : public Command {
public:
	StepAndRepeat(int x_num_repeats, int y_num_repeats, double x_step_distance, double y_step_distance);
	StepAndRepeat(int x_num_repeats, int y_num_repeats, double x_step_distance, double y_step_distance,
        yy::location x_num_repeats_location, yy::location y_num_repeats_location, yy::location x_step_distance_location,
        yy::location y_step_distance_locatio, yy::location location);
	StepAndRepeat();
	StepAndRepeat(yy::location location);
	virtual ~StepAndRepeat();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_x_num_repeats;
	int m_y_num_repeats;
	double m_x_step_distance;
	double m_y_step_distance;
	yy::location m_x_num_repeats_location;
	yy::location m_y_num_repeats_location;
	yy::location m_x_step_distance_location;
	yy::location m_y_step_distance_location;
	yy::location m_location;
};

#endif // _STEP_AND_REPEAT_H
