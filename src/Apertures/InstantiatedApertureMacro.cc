/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Apertures/InstantiatedApertureMacro.hh"
#include "GlobalDefs.hh"

#include <memory>

InstantiatedApertureMacro::InstantiatedApertureMacro()
{}

InstantiatedApertureMacro::~InstantiatedApertureMacro()
{}

void InstantiatedApertureMacro::add_instantiated_macro_content(std::shared_ptr<InstantiatedApertureMacroPrimitive> instantiated_primitive)
{
    m_macro_content.push_back(instantiated_primitive);
}

Gerber::SemanticValidity InstantiatedApertureMacro::do_check_semantic_validity(SemanticIssueList& issue_list)
{
    // TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}
