/*
 * InstantiatedApertureMacroPrimitive.cpp
 *
 *  Created on: Nov 8, 2015
 *      Author: abamberger
 */

#include "InstantiatedApertureMacroPrimitive.hh"
#include "GlobalDefs.hh"

#include <iostream>

InstantiatedApertureMacroPrimitive::InstantiatedApertureMacroPrimitive()
{}

InstantiatedApertureMacroPrimitive::~InstantiatedApertureMacroPrimitive()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitive::check_semantic_validity()
{
    return do_check_semantic_validity();
}

std::ostream& operator<<(std::ostream& os, const InstantiatedApertureMacroPrimitive& macro_primitive)
{
    return macro_primitive.do_print(os);
}
