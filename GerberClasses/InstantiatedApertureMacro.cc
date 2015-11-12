/*
 * InstantiatedApertureMacro.cc
 *
 *  Created on: Nov 11, 2015
 *      Author: abamberger
 */

#include "InstantiatedApertureMacro.hh"
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

Gerber::SemanticValidity InstantiatedApertureMacro::do_check_semantic_validity()
{
    // TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}
