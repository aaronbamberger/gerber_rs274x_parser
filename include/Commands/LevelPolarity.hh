#ifndef _LEVEL_POLARITY_H
#define _LEVEL_POLARITY_H

#include "Commands/Command.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>

class LevelPolarity : public Command {
public:
	LevelPolarity(Gerber::LevelPolarityType polarity);
	LevelPolarity(Gerber::LevelPolarityType polarity, yy::location location);
	virtual ~LevelPolarity();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	Gerber::LevelPolarityType m_polarity;
	yy::location m_location;
};

#endif // _LEVEL_POLARITY_H
