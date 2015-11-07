#include "StepAndRepeat.hh"

#include <iostream>
#include <string>

StepAndRepeat::StepAndRepeat(int x_num_repeats, int y_num_repeats, double x_step_distance, double y_step_distance) : m_x_num_repeats(x_num_repeats),
																														m_y_num_repeats(y_num_repeats),
																														m_x_step_distance(x_step_distance),
																														m_y_step_distance(y_step_distance)
{}

StepAndRepeat::StepAndRepeat() : m_x_num_repeats(1),
									m_y_num_repeats(1),
									m_x_step_distance(0.0),
									m_y_step_distance(0.0)
{}

StepAndRepeat::~StepAndRepeat()
{}

bool StepAndRepeat::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& StepAndRepeat::do_print(std::ostream& os) const
{
	os << "Step and Repeat:" << std::endl;
	os << "Number of Repeats (X): " << m_x_num_repeats << std::endl;
	os << "Number of Repeats (Y): " << m_y_num_repeats << std::endl;
	os << "Step Distance (X): " << m_x_step_distance << std::endl;
	os << "Step Distance (Y): " << m_y_step_distance << std::endl;
	return os;
}