#include "UnitSpecifier.hh"

#include <iostream>
#include <string>

UnitSpecifier::UnitSpecifier(UnitType unit_type) : m_unit_type(unit_type)
{}

UnitSpecifier::~UnitSpecifier()
{}

bool UnitSpecifier::do_check_semantic_validity(std::string& error_msg)
{
	return false;
}

std::ostream& UnitSpecifier::do_print(std::ostream& os) const
{
	os << "Units: ";
	switch (m_unit_type) {
		case UnitType::UNIT_TYPE_IN:
			os << "Inches" << std::endl;
			break;

		case UnitType::UNIT_TYPE_MM:
			os << "Millimeters" << std::endl;
			break;
	}
	return os;
}