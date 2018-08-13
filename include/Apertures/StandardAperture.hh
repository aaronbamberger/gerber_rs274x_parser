#ifndef _STANDARD_APERTURE_H
#define _STANDARD_APERTURE_H

#include "Apertures/Aperture.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

class StandardAperture : public Aperture {
public:
	StandardAperture();
	virtual ~StandardAperture();

	std::shared_ptr<StandardAperture> clone();

	friend std::ostream& operator<<(std::ostream& os, const StandardAperture& standard_aperture);

private:
	virtual std::shared_ptr<StandardAperture> do_clone() = 0;

	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _STANDARD_APERTURE_H
