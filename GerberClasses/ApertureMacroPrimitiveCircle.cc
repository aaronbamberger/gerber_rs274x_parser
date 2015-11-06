#include "ApertureMacroPrimitiveCircle.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

ApertureMacroPrimitiveCircle::ApertureMacroPrimitiveCircle(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> diameter,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> rotation) : m_exposure(exposure),
																	m_diameter(diameter),
																	m_center_x(center_x),
																	m_center_y(center_y),
																	m_rotation(rotation)
{}

ApertureMacroPrimitiveCircle::ApertureMacroPrimitiveCircle(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> diameter,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y) : m_exposure(exposure),
																	m_diameter(diameter),
																	m_center_x(center_x),
																	m_center_y(center_y)
{}

ApertureMacroPrimitiveCircle::~ApertureMacroPrimitiveCircle()
{}

std::ostream& ApertureMacroPrimitiveCircle::do_print(std::ostream& os)
{
	os << "Macro Primitive: Circle" << std::endl;
	os << "Exposure:" << std::endl;
	os << m_exposure;
	os << "Diamemter:" << std::endl;
	os << m_diameter;
	os << "Center (X):" << std::endl;
	os << m_center_x;
	os << "Center (Y):" << std::endl;
	os << m_center_y;
	os << "Rotation:";
	if (m_rotation) {
		os << std::endl;
		os << m_rotation;
	} else {
		os << " None" << std::endl;
	}
	return os;
}