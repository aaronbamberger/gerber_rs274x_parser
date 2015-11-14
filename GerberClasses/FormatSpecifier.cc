#include "FormatSpecifier.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>
#include <string>
#include <memory>

FormatSpecifier::FormatSpecifier(int x_num_int_positions, int x_num_dec_positions, int y_num_int_positions, int y_num_dec_positions) :
    m_x_num_int_positions(x_num_int_positions), m_x_num_dec_positions(x_num_dec_positions),
    m_y_num_int_positions(y_num_int_positions), m_y_num_dec_positions(y_num_dec_positions)
{}

FormatSpecifier::FormatSpecifier(int x_num_int_positions, int x_num_dec_positions, int y_num_int_positions, int y_num_dec_positions,
    yy::location x_num_int_positions_location, yy::location x_num_dec_positions_location,
    yy::location y_num_int_positions_location, yy::location y_num_dec_positions_location,
    yy::location location) :
        m_x_num_int_positions(x_num_int_positions), m_x_num_dec_positions(x_num_dec_positions),
        m_y_num_int_positions(y_num_int_positions), m_y_num_dec_positions(y_num_dec_positions),
        m_x_num_int_positions_location(x_num_int_positions_location), m_x_num_dec_positions_location(x_num_dec_positions_location),
        m_y_num_int_positions_location(y_num_int_positions_location), m_y_num_dec_positions_location(y_num_dec_positions_location),
        m_location(location)
{}


FormatSpecifier::~FormatSpecifier()
{}

Gerber::SemanticValidity FormatSpecifier::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // First, attempt to set the coordinate format of the graphics state.  This will fail
    // if the coordinate format of the graphics state has already been set
    // (which we'll consider a fatal error)
    // TODO: Currently, creating another copy of the format specifier to set in the graphics state
    // I'm not particularly happy with this solution, but I'll have to think about it some more
    std::shared_ptr<FormatSpecifier> format_spec_copy = std::shared_ptr<FormatSpecifier>(new FormatSpecifier(*this));
    if (!graphics_state.set_coord_format(format_spec_copy)) {
       return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

	// For any of the fields, a negative number doesn't make sense
	// and is a fatal error
	// TODO: Leaving these as separate checks for now to facilitate different error messages
	if (m_x_num_int_positions < 0) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
	}

	if (m_x_num_dec_positions < 0) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
	}

	if (m_y_num_int_positions < 0) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
	}

	if (m_y_num_dec_positions < 0) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
	}

	// Per the spec, the coordinate format for X and Y must be the same
	// Since it isn't nonsensical to have different X and Y formats
	// (even though it's prohibited by the spec), this is a warning, not a fatal error
	if ((m_x_num_int_positions != m_y_num_int_positions) || (m_x_num_dec_positions != m_y_num_dec_positions)) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
	}

	// Also prohibited by the spec, (but not nonsensical), are numbers of integer or decimal places > 6
	if (m_x_num_int_positions > 6) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
	}

	if (m_x_num_dec_positions > 6) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
	}

	if (m_y_num_int_positions > 6) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
	}

	if (m_y_num_dec_positions > 6) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_WARNING;
	}

	// Lastly, per the spec, a number of decimal positions < 4 is deprecated
	if (m_x_num_dec_positions < 4) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_DEPRECATED;
	}

	if (m_y_num_dec_positions < 4) {
		return Gerber::SemanticValidity::SEMANTIC_VALIDITY_DEPRECATED;
	}	

	// If we get here, we have a semantically valid format specifier
	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& FormatSpecifier::do_print(std::ostream& os) const
{
	os << "Format Specifier (@" << m_location << "):" << std::endl;
	os << "Number of Integer Positions (X): " << m_x_num_int_positions << " @" << m_x_num_int_positions_location << std::endl;
	os << "Number of Decimal Positions (X): " << m_x_num_dec_positions << " @" << m_x_num_dec_positions_location << std::endl;
	os << "Number of Integer Positions (Y): " << m_y_num_int_positions << " @" << m_y_num_int_positions_location << std::endl;
	os << "Number of Decimal Positions (Y): " << m_y_num_dec_positions << " @" << m_y_num_dec_positions_location << std::endl;
	return os;
}
