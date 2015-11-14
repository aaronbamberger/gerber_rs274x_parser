/*
 * ApertureDefinitionModifier.hh
 *
 *  Created on: Nov 14, 2015
 *      Author: abamberger
 */

#ifndef _APERTURE_DEFINITION_MODIFIER_H
#define _APERTURE_DEFINITION_MODIFIER_H

#include "../location.hh"

struct ApertureDefinitionModifier {
    ApertureDefinitionModifier();
    ApertureDefinitionModifier(double value, yy::location location);
    virtual ~ApertureDefinitionModifier();

    double m_value;
    yy::location m_location;
};

#endif // _APERTURE_DEFINITION_MODIFIER_H
