#ifndef _STANDARD_APERTURE_H
#define _STANDARD_APERTURE_H

#include "GlobalDefs.hh"

#include <iostream>

class StandardAperture {
public:
	StandardAperture();
	virtual ~StandardAperture();

	Gerber::SemanticValidity check_semantic_validity();

	friend std::ostream& operator<<(std::ostream& os, const StandardAperture& standard_aperture);

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity() = 0;
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _STANDARD_APERTURE_H
