#include "LevelPolarity.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>

LevelPolarity::LevelPolarity(Gerber::LevelPolarityType polarity) : m_polarity(polarity)
{}

LevelPolarity::~LevelPolarity()
{}

Gerber::SemanticValidity LevelPolarity::do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        return Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL;
    }

    // Update the level polarity in the graphics state
    graphics_state.set_level_polarity(m_polarity);

    // If level polarity commands are syntactically valid, they are semantically valid
	return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& LevelPolarity::do_print(std::ostream& os) const
{
	os << "Level Polarity: ";
	switch(m_polarity) {
		case Gerber::LevelPolarityType::LEVEL_POLARITY_DARK:
			os << "Dark" << std::endl;
			break;

		case Gerber::LevelPolarityType::LEVEL_POLARITY_CLEAR:
			os << "Clear" << std::endl;
			break;
	}
	return os;
}
