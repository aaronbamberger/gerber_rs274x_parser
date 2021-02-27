/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Apertures/Aperture.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

Aperture::Aperture()
{}

Aperture::~Aperture()
{}

Gerber::SemanticValidity Aperture::check_semantic_validity(SemanticIssueList& issue_list)
{
    return do_check_semantic_validity(issue_list);
}
