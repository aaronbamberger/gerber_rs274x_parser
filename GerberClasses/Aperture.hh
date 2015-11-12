/*
 * Aperture.hh
 *
 *  Created on: Nov 11, 2015
 *      Author: abamberger
 */

#ifndef _APERTURE_H
#define _APERTURE_H

#include "GlobalDefs.hh"

class Aperture {
public:
    Aperture();
    virtual ~Aperture();

    Gerber::SemanticValidity check_semantic_validity();

private:
    virtual Gerber::SemanticValidity do_check_semantic_validity() = 0;
};

#endif // _APERTURE_H
