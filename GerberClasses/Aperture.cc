/*
 * Aperture.cc
 *
 *  Created on: Nov 11, 2015
 *      Author: abamberger
 */

#include "Aperture.hh"
#include "GlobalDefs.hh"

Aperture::Aperture()
{}

Aperture::~Aperture()
{}

Gerber::SemanticValidity Aperture::check_semantic_validity()
{
    return do_check_semantic_validity();
}
