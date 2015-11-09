#ifndef _APERTURE_MACRO_CONTENT_H
#define _APERTURE_MACRO_CONTENT_H

#include "GlobalDefs.hh"

#include <iostream>

class ApertureMacroContent {
public:
	ApertureMacroContent();
	virtual ~ApertureMacroContent();

	friend std::ostream& operator<<(std::ostream& os, const ApertureMacroContent& macro_content);

private:
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _APERTURE_MACRO_CONTENT_H
