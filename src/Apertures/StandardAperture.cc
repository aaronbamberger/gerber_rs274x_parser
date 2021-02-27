/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "Apertures/StandardAperture.hh"

#include <memory>

StandardAperture::StandardAperture()
{}

StandardAperture::~StandardAperture()
{}

std::shared_ptr<StandardAperture> StandardAperture::clone()
{
    return do_clone();
}

std::ostream& operator<<(std::ostream& os, const StandardAperture& standard_aperture)
{
	return standard_aperture.do_print(os);
}
