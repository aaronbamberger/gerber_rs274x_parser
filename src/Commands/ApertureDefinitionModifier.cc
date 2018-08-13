/*
 * ApertureDefinitionModifier.cc
 *
 *  Created on: Nov 14, 2015
 *      Author: abamberger
 */

#include "Commands/ApertureDefinitionModifier.hh"
#include "location.hh"

ApertureDefinitionModifier::ApertureDefinitionModifier() : m_value(0.0)
{}

ApertureDefinitionModifier::ApertureDefinitionModifier(double value, yy::location location) :
    m_value(value), m_location(location)
{}

ApertureDefinitionModifier::~ApertureDefinitionModifier()
{}
