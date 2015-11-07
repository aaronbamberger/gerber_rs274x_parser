#include "LevelPolarity.hh"

#include <iostream>
#include <string>

LevelPolarity::LevelPolarity(LevelPolarityType polarity) : m_polarity(polarity)
{}

LevelPolarity::~LevelPolarity()
{}

bool LevelPolarity::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& LevelPolarity::do_print(std::ostream& os) const
{
	os << "Level Polarity: ";
	switch(m_polarity) {
		case LevelPolarityType::LEVEL_POLARITY_DARK:
			os << "Dark" << std::endl;
			break;

		case LevelPolarityType::LEVEL_POLARITY_CLEAR:
			os << "Clear" << std::endl;
			break;
	}
	return os;
}