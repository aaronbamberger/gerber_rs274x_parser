#include "StandardAperture.hh"

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
