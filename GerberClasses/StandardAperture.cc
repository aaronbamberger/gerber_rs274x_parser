#include "StandardAperture.hh"

StandardAperture::StandardAperture()
{}

StandardAperture::~StandardAperture()
{}

Gerber::SemanticValidity StandardAperture::check_semantic_validity()
{
    return do_check_semantic_validity();
}

std::ostream& operator<<(std::ostream& os, const StandardAperture& standard_aperture)
{
	return standard_aperture.do_print(os);
}
