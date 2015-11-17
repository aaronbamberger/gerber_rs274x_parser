/*
 * Aperture.cc
 *
 *  Created on: Nov 11, 2015
 *      Author: abamberger
 */

#include "Aperture.hh"
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
