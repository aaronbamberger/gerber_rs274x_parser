/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Commands/LevelPolarity.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <string>

LevelPolarity::LevelPolarity(Gerber::LevelPolarityType polarity) : m_polarity(polarity)
{}

LevelPolarity::LevelPolarity(Gerber::LevelPolarityType polarity, yy::location location) :
    m_polarity(polarity), m_location(location)
{}

LevelPolarity::~LevelPolarity()
{}

Gerber::SemanticValidity LevelPolarity::do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list)
{
    // No commands are allowed after the end-of-file command has been encountered
    if (graphics_state.file_complete()) {
        SemanticIssue issue(Gerber::SemanticValidity::SEMANTIC_VALIDITY_FATAL,
            m_location,
            "No commands are allowed after the end-of-file command has been encountered");
        issue_list.add_issue(issue);
        return issue.severity();
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
			os << "Dark";
			break;

		case Gerber::LevelPolarityType::LEVEL_POLARITY_CLEAR:
			os << "Clear";
			break;
	}

	os << " (@" << m_location << ")" << std::endl;

	return os;
}
