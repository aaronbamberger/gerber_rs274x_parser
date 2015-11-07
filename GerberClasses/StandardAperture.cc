#include "StandardAperture.hh"

StandardAperture::StandardAperture()
{}

StandardAperture::~StandardAperture()
{}

std::ostream& operator<<(std::ostream& os, const StandardAperture& standard_aperture)
{
	return standard_aperture.do_print(os);
}