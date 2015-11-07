#include "ApertureMacroPrimitiveCenterLine.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

ApertureMacroPrimitiveCenterLine::ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> rect_width,
		std::shared_ptr<ArithmeticExpressionElement> rect_height,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> rotation) : m_exposure(exposure),
																	m_rect_width(rect_width),
																	m_rect_height(rect_height),
																	m_center_x(center_x),
																	m_center_y(center_y),
																	m_rotation(rotation)
{}

ApertureMacroPrimitiveCenterLine::ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> rect_width,
		std::shared_ptr<ArithmeticExpressionElement> rect_height,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y) : m_exposure(exposure),
																	m_rect_width(rect_width),
																	m_rect_height(rect_height),
																	m_center_x(center_x),
																	m_center_y(center_y)
{}

ApertureMacroPrimitiveCenterLine::~ApertureMacroPrimitiveCenterLine()
{}

std::ostream& ApertureMacroPrimitiveCenterLine::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Center Line" << std::endl;
	os << "Exposure:" << std::endl;
	os << *m_exposure;
	os << "Rectangle Width:" << std::endl;
	os << *m_rect_width;
	os << "Rectangle Height:" << std::endl;
	os << *m_rect_height;
	os << "Center (X):" << std::endl;
	os << *m_center_x;
	os << "Center (Y):" << std::endl;
	os << *m_center_y;
	os << "Rotation:";
	if (m_rotation) {
		os << std::endl;
		os << *m_rotation;
	} else {
		os << " None" << std::endl;
	}
	return os;
}