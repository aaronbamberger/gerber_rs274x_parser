#include "ApertureMacroPrimitivePolygon.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

ApertureMacroPrimitivePolygon::ApertureMacroPrimitivePolygon(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_vertices,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> diameter,
		std::shared_ptr<ArithmeticExpressionElement> rotation) : m_exposure(exposure),
																	m_num_vertices(num_vertices),
																	m_center_x(center_x),
																	m_center_y(center_y),
																	m_diameter(diameter),
																	m_rotation(rotation)
{}

ApertureMacroPrimitivePolygon::ApertureMacroPrimitivePolygon(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_vertices,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> diameter) : m_exposure(exposure),
																	m_num_vertices(num_vertices),
																	m_center_x(center_x),
																	m_center_y(center_y),
																	m_diameter(diameter)
{}

ApertureMacroPrimitivePolygon::~ApertureMacroPrimitivePolygon()
{}

std::ostream& ApertureMacroPrimitivePolygon::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Polygon" << std::endl;
	os << "Exposure:" << std::endl;
	os << *m_exposure;
	os << "Number of Vertices:" << std::endl;
	os << *m_num_vertices;
	os << "Center (X):" << std::endl;
	os << *m_center_x;
	os << "Center (Y):" << std::endl;
	os << *m_center_y;
	os << "Diamemter:" << std::endl;
	os << *m_diameter;
	os << "Rotation:";
	if (m_rotation) {
		os << std::endl;
		os << *m_rotation;
	} else {
		os << " None" << std::endl;
	}
	return os;
}