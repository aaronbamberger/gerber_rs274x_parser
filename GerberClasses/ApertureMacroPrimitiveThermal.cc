#include "ApertureMacroPrimitiveThermal.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

ApertureMacroPrimitiveThermal::ApertureMacroPrimitiveThermal(std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
		std::shared_ptr<ArithmeticExpressionElement> inner_diameter,
		std::shared_ptr<ArithmeticExpressionElement> gap_thickness,
		std::shared_ptr<ArithmeticExpressionElement> rotation) : m_center_x(center_x),
																	m_center_y(center_y),
																	m_outer_diameter(outer_diameter),
																	m_inner_diameter(inner_diameter),
																	m_gap_thickness(gap_thickness),
																	m_rotation(rotation)
{}

ApertureMacroPrimitiveThermal::ApertureMacroPrimitiveThermal(std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
		std::shared_ptr<ArithmeticExpressionElement> inner_diameter,
		std::shared_ptr<ArithmeticExpressionElement> gap_thickness) : m_center_x(center_x),
																	m_center_y(center_y),
																	m_outer_diameter(outer_diameter),
																	m_inner_diameter(inner_diameter),
																	m_gap_thickness(gap_thickness)
{}

ApertureMacroPrimitiveThermal::~ApertureMacroPrimitiveThermal()
{}

std::ostream& ApertureMacroPrimitiveThermal::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Thermal" << std::endl;
	os << "Center (X):" << std::endl;
	os << *m_center_x;
	os << "Center (Y):" << std::endl;
	os << *m_center_y;
	os << "Outer Diameter:" << std::endl;
	os << *m_outer_diameter;
	os << "Inner Diameter:" << std::endl;
	os << *m_inner_diameter;
	os << "Gap Thickness:" << std::endl;
	os << *m_gap_thickness;
	os << "Rotation:";
	if (m_rotation) {
		os << std::endl;
		os << *m_rotation;
	} else {
		os << " None" << std::endl;
	}
	return os;
}