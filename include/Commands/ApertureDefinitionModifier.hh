/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_DEFINITION_MODIFIER_H
#define _APERTURE_DEFINITION_MODIFIER_H

#include "location.hh"

struct ApertureDefinitionModifier {
    ApertureDefinitionModifier();
    ApertureDefinitionModifier(double value, yy::location location);
    virtual ~ApertureDefinitionModifier();

    double m_value;
    yy::location m_location;
};

#endif // _APERTURE_DEFINITION_MODIFIER_H
