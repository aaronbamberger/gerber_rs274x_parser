#ifndef _APERTURE_MACRO_PRIMITIVE_H
#define _APERTURE_MACRO_PRIMITIVE_H

#include <iostream>

class ApertureMacroPrimitive {
public:
	ApertureMacroPrimitive();
	virtual ~ApertureMacroPrimitive();

	friend std::ostream& operator<<(std::ostream& os, const ApertureMacroPrimitive& macro_primitive);

private:
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _APERTURE_MACRO_PRIMITIVE_H