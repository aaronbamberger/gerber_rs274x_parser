#ifndef _STANDARD_APERTURE_H
#define _STANDARD_APERTURE_H

#include <iostream>

class StandardAperture {
public:
	StandardAperture();
	virtual ~StandardAperture();

	friend std::ostream& operator<<(std::ostream& os, const StandardAperture& standard_aperture);

private:
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _STANDARD_APERTURE_H