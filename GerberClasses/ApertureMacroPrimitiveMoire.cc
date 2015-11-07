#include "ApertureMacroPrimitiveMoire.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

ApertureMacroPrimitiveMoire::ApertureMacroPrimitiveMoire(std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
		std::shared_ptr<ArithmeticExpressionElement> ring_thickness,
		std::shared_ptr<ArithmeticExpressionElement> ring_gap,
		std::shared_ptr<ArithmeticExpressionElement> max_rings,
		std::shared_ptr<ArithmeticExpressionElement> crosshair_thickness,
		std::shared_ptr<ArithmeticExpressionElement> crosshair_length,
		std::shared_ptr<ArithmeticExpressionElement> rotation) : m_center_x(center_x),
																	m_center_y(center_y),
																	m_outer_diameter(outer_diameter),
																	m_ring_thickness(ring_thickness),
																	m_ring_gap(ring_gap),
																	m_max_rings(max_rings),
																	m_crosshair_thickness(crosshair_thickness),
																	m_crosshair_length(crosshair_length),
																	m_rotation(rotation)
{}

ApertureMacroPrimitiveMoire::ApertureMacroPrimitiveMoire(std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
		std::shared_ptr<ArithmeticExpressionElement> ring_thickness,
		std::shared_ptr<ArithmeticExpressionElement> ring_gap,
		std::shared_ptr<ArithmeticExpressionElement> max_rings,
		std::shared_ptr<ArithmeticExpressionElement> crosshair_thickness,
		std::shared_ptr<ArithmeticExpressionElement> crosshair_length) : m_center_x(center_x),
																	m_center_y(center_y),
																	m_outer_diameter(outer_diameter),
																	m_ring_thickness(ring_thickness),
																	m_ring_gap(ring_gap),
																	m_max_rings(max_rings),
																	m_crosshair_thickness(crosshair_thickness),
																	m_crosshair_length(crosshair_length)
{}

ApertureMacroPrimitiveMoire::~ApertureMacroPrimitiveMoire()
{}

std::ostream& ApertureMacroPrimitiveMoire::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Moire" << std::endl;
	os << "Center (X):" << std::endl;
	os << *m_center_x;
	os << "Center (Y):" << std::endl;
	os << *m_center_y;
	os << "Outer Diameter:" << std::endl;
	os << *m_outer_diameter;
	os << "Ring Thickness:" << std::endl;
	os << *m_ring_thickness;
	os << "Ring Gap:" << std::endl;
	os << *m_ring_gap;
	os << "Max Rings:" << std::endl;
	os << *m_max_rings;
	os << "Crosshair Thickness:" << std::endl;
	os << *m_crosshair_thickness;
	os << "Crosshair Length:" << std::endl;
	os << *m_crosshair_length;
	os << "Rotation:";
	if (m_rotation) {
		os << std::endl;
		os << *m_rotation;
	} else {
		os << " None" << std::endl;
	}
	return os;
}