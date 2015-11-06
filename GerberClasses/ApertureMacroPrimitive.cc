#include "ApertureMacroPrimitive.hh"

#include <iostream>

ApertureMacroPrimitive::ApertureMacroPrimitive()
{}

ApertureMacroPrimitive::~ApertureMacroPrimitive()
{}

std::ostream& operator<<(std::ostream& os, const ApertureMacroPrimitive& macro_primitive)
{
	return macro_primitive.do_print(os);
}