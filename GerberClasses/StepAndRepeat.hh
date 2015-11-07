#ifndef _STEP_AND_REPEAT_H
#define _STEP_AND_REPEAT_H

#include "Command.hh"

#include <iostream>
#include <string>

class StepAndRepeat : public Command {
public:
	StepAndRepeat(int x_num_repeats, int y_num_repeats, double x_step_distance, double y_step_distance);
	StepAndRepeat();
	virtual ~StepAndRepeat();

private:
	virtual bool do_check_semantic_validity(std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_x_num_repeats;
	int m_y_num_repeats;
	double m_x_step_distance;
	double m_y_step_distance;
};

#endif // _STEP_AND_REPEAT_H