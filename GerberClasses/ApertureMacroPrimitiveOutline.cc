#include "ApertureMacroPrimitiveOutline.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

ApertureMacroPrimitiveOutline::ApertureMacroPrimitiveOutline(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_points,
		std::shared_ptr<std::list<std::pair<std::shared_ptr<ArithmeticExpressionElement>, std::shared_ptr<ArithmeticExpressionElement> > > > coords,
		std::shared_ptr<ArithmeticExpressionElement> rotation) : m_exposure(exposure),
																	m_num_points(num_points),
																	m_coords(coords),
																	m_rotation(rotation)
{}

ApertureMacroPrimitiveOutline::ApertureMacroPrimitiveOutline(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_points,
		std::shared_ptr<std::list<std::pair<std::shared_ptr<ArithmeticExpressionElement>, std::shared_ptr<ArithmeticExpressionElement> > > > coords) : m_exposure(exposure),
																	m_num_points(num_points),
																	m_coords(coords)
{}

ApertureMacroPrimitiveOutline::~ApertureMacroPrimitiveOutline()
{}

std::ostream& ApertureMacroPrimitiveOutline::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Outline" << std::endl;
	os << "Exposure:" << std::endl;
	os << *m_exposure;
	os << "Number of Points:" << std::endl;
	os << *m_num_points;
	
	int point_num = 0;
	for (auto coord : *m_coords) {
		os << "Point: " << point_num++ << std::endl;
		// Type of coord should be std::pair<std::shared_ptr<ArithmeticExpressionElement>, std::shared_ptr<ArithmeticExpressionElement> >
		os << "X Coordinate:" << std::endl;
		os << *(coord.first);
		os << "Y Coordinate:" << std::endl;
		os << *(coord.second);
	}

	os << "Rotation:";
	if (m_rotation) {
		os << std::endl;
		os << *m_rotation;
	} else {
		os << " None" << std::endl;
	}
	return os;
}