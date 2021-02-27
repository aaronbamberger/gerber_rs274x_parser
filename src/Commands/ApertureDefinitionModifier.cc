/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
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
