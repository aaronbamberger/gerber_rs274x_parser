/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Commands/ApertureDefinition.hh"
#include "location.hh"

#include <iostream>
#include <string>

ApertureDefinition::ApertureDefinition(int aperture_number) : m_aperture_number(aperture_number)
{}

ApertureDefinition::ApertureDefinition(int aperture_number, yy::location aperture_number_location,
    yy::location location) :
        m_aperture_number(aperture_number), m_aperture_number_location(aperture_number_location),
        m_location(location)
{}

ApertureDefinition::~ApertureDefinition()
{}
