#include "ApertureMacroPrimitiveVectorLine.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

ApertureMacroPrimitiveVectorLine::ApertureMacroPrimitiveVectorLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> line_width,
		std::shared_ptr<ArithmeticExpressionElement> start_x,
		std::shared_ptr<ArithmeticExpressionElement> start_y,
		std::shared_ptr<ArithmeticExpressionElement> end_x,
		std::shared_ptr<ArithmeticExpressionElement> end_y,
		std::shared_ptr<ArithmeticExpressionElement> rotation) : m_exposure(exposure),
																	m_line_width(line_width),
																	m_start_x(start_x),
																	m_start_y(start_y),
																	m_end_x(end_x),
																	m_end_y(end_y),
																	m_rotation(rotation)
{}

ApertureMacroPrimitiveVectorLine::ApertureMacroPrimitiveVectorLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> line_width,
		std::shared_ptr<ArithmeticExpressionElement> start_x,
		std::shared_ptr<ArithmeticExpressionElement> start_y,
		std::shared_ptr<ArithmeticExpressionElement> end_x,
		std::shared_ptr<ArithmeticExpressionElement> end_y) : m_exposure(exposure),
																	m_line_width(line_width),
																	m_start_x(start_x),
																	m_start_y(start_y),
																	m_end_x(end_x),
																	m_end_y(end_y)
{}

ApertureMacroPrimitiveVectorLine::~ApertureMacroPrimitiveVectorLine()
{}

std::ostream& ApertureMacroPrimitiveVectorLine::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Vector Line" << std::endl;
	os << "Exposure:" << std::endl;
	os << *m_exposure;
	os << "Line Width:" << std::endl;
	os << *m_line_width;
	os << "Start (X):" << std::endl;
	os << *m_start_x;
	os << "Start (Y):" << std::endl;
	os << *m_start_y;
	os << "End (X):" << std::endl;
	os << *m_end_x;
	os << "End (Y):" << std::endl;
	os << *m_end_y;
	os << "Rotation:";
	if (m_rotation) {
		os << std::endl;
		os << *m_rotation;
	} else {
		os << " None" << std::endl;
	}
	return os;
}