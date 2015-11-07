#include "ApertureMacroContent.hh"

#include <iostream>

ApertureMacroContent::ApertureMacroContent()
{}

ApertureMacroContent::~ApertureMacroContent()
{}

std::ostream& operator<<(std::ostream& os, const ApertureMacroContent& macro_content)
{
	return macro_content.do_print(os);
}
