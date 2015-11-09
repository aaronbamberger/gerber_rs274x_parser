/*
 * InstantiatedApertureMacroPrimitive.h
 *
 *  Created on: Nov 8, 2015
 *      Author: abamberger
 */

#ifndef _INSTANTIATED_APERTURE_MACRO_PRIMITIVE_H
#define _INSTANTIATED_APERTURE_MACRO_PRIMITIVE_H

#include "GlobalDefs.hh"

class InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitive();
    virtual ~InstantiatedApertureMacroPrimitive();

    Gerber::SemanticValidity check_semantic_validity();

private:
    virtual Gerber::SemanticValidity do_check_semantic_validity() = 0;
};

#endif // _INSTANTIATED_APERTURE_MACRO_PRIMITIVE_H
