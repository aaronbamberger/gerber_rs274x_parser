/*
 * InstantiatedApertureMacroPrimitive.cpp
 *
 *  Created on: Nov 8, 2015
 *      Author: abamberger
 */

#include "InstantiatedApertureMacroPrimitive.hh"
#include "GlobalDefs.hh"

InstantiatedApertureMacroPrimitive::InstantiatedApertureMacroPrimitive()
{}

InstantiatedApertureMacroPrimitive::~InstantiatedApertureMacroPrimitive()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitive::check_semantic_validity()
{
    return do_check_semantic_validity();
}
