#ifndef _LEVEL_POLARITY_H
#define _LEVEL_POLARITY_H

#include "Command.hh"

#include <iostream>
#include <string>

class LevelPolarity : public Command {
public:
	enum class LevelPolarityType {
		LEVEL_POLARITY_DARK,
		LEVEL_POLARITY_CLEAR
	};

	LevelPolarity(LevelPolarityType polarity);
	virtual ~LevelPolarity();

private:
	virtual bool do_check_semantic_validity(std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	LevelPolarityType m_polarity;
};

#endif // _LEVEL_POLARITY_H