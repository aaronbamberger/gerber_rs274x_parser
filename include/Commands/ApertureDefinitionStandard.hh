/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_DEFINITION_STANDARD_H
#define _APERTURE_DEFINITION_STANDARD_H

#include "Commands/ApertureDefinition.hh"
#include "Apertures/StandardAperture.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"

#include <iostream>
#include <memory>

class ApertureDefinitionStandard : public ApertureDefinition {
public:
	ApertureDefinitionStandard(int aperture_number, std::shared_ptr<StandardAperture> standard_aperture);
	ApertureDefinitionStandard(int aperture_number, std::shared_ptr<StandardAperture> standard_aperture,
        yy::location aperture_number_location, yy::location location);
	virtual ~ApertureDefinitionStandard();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	std::shared_ptr<StandardAperture> m_standard_aperture;
};

#endif // _APERTURE_DEFINITION_STANDARD_H
