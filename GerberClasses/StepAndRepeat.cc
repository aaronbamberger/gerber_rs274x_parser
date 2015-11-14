#include "StepAndRepeat.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>
#include <string>

StepAndRepeat::StepAndRepeat(int x_num_repeats, int y_num_repeats, double x_step_distance, double y_step_distance) :
    m_x_num_repeats(x_num_repeats), m_y_num_repeats(y_num_repeats), m_x_step_distance(x_step_distance),
    m_y_step_distance(y_step_distance)
{}

StepAndRepeat::StepAndRepeat(int x_num_repeats, int y_num_repeats, double x_step_distance, double y_step_distance,
    yy::location x_num_repeats_location, yy::location y_num_repeats_location, yy::location x_step_distance_location,
    yy::location y_step_distance_location, yy::location location) :
        m_x_num_repeats(x_num_repeats), m_y_num_repeats(y_num_repeats), m_x_step_distance(x_step_distance),
        m_y_step_distance(y_step_distance), m_x_num_repeats_location(x_num_repeats_location),
        m_y_num_repeats_location(y_num_repeats_location), m_x_step_distance_location(x_step_distance_location),
        m_y_step_distance_location(y_step_distance_location), m_location(location)
{}

StepAndRepeat::StepAndRepeat() : m_x_num_repeats(1), m_y_num_repeats(1), m_x_step_distance(0.0), m_y_step_distance(0.0)
{}

StepAndRepeat::StepAndRepeat(yy::location location) : m_x_num_repeats(1), m_y_num_repeats(1),
    m_x_step_distance(0.0), m_y_step_distance(0.0), m_location(location)
{}

StepAndRepeat::~StepAndRepeat()
{}

Gerber::SemanticValidity StepAndRepeat::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Copy the new step and repeat settings into the graphics state
    graphics_state.set_step_and_repeat(std::shared_ptr<StepAndRepeat>(new StepAndRepeat(*this)));

    // Repeats in both the x and y directions must be >= 1, otherwise it's a fatal error
    if (m_x_num_repeats < 1) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    if (m_y_num_repeats < 1) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Likewise, step distance in both the x and y direction must be >= 0, otherwise it's a fatal error
    if (m_x_step_distance < 0.0) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    if (m_y_step_distance  < 0.0) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& StepAndRepeat::do_print(std::ostream& os) const
{
	os << "Step and Repeat: (@" << m_location << ")" << std::endl;

	if (m_x_num_repeats > 1) {
	    os << "Number of Repeats (X): " << m_x_num_repeats << " (@" << m_x_num_repeats_location << ")" << std::endl;
	    os << "Step Distance (X): " << m_x_step_distance << " (@" << m_x_step_distance_location << ")" << std::endl;
	}

	if (m_y_num_repeats > 1) {
        os << "Number of Repeats (Y): " << m_y_num_repeats << " (@" << m_y_num_repeats_location << ")" << std::endl;
        os << "Step Distance (Y): " << m_y_step_distance << " (@" << m_y_step_distance_location << ")" << std::endl;
	}

	return os;
}
