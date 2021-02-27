/*
* Copyright 2021 Aaron Bamberger
* Licensed under BSD 2-clause license
* See LICENSE file at root of source tree,
* or https://opensource.org/licenses/BSD-2-Clause
*/

#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>

InstantiatedApertureMacroPrimitive::InstantiatedApertureMacroPrimitive()
{}

InstantiatedApertureMacroPrimitive::~InstantiatedApertureMacroPrimitive()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitive::check_semantic_validity(SemanticIssueList& issue_list)
{
    return do_check_semantic_validity(issue_list);
}

std::ostream& operator<<(std::ostream& os, const InstantiatedApertureMacroPrimitive& macro_primitive)
{
    return macro_primitive.do_print(os);
}
