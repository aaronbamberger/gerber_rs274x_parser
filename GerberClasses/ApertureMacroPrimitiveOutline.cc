#include "ApertureMacroPrimitiveOutline.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"
#include "Point.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

InstantiatedApertureMacroPrimitiveOutline::InstantiatedApertureMacroPrimitiveOutline(double exposure,
    double num_points,
    std::shared_ptr<std::list<Point<double> > > coords,
    double rotation) :
        m_outline(exposure, num_points, coords, rotation)
{}

InstantiatedApertureMacroPrimitiveOutline::InstantiatedApertureMacroPrimitiveOutline(double exposure,
    double num_points,
    std::shared_ptr<std::list<Point<double> > > coords) :
        m_outline(exposure, num_points, coords)
{}

InstantiatedApertureMacroPrimitiveOutline::~InstantiatedApertureMacroPrimitiveOutline()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitiveOutline::do_check_semantic_validity()
{
    // TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& InstantiatedApertureMacroPrimitiveOutline::do_print(std::ostream& os) const
{
    os << "Instantiated Macro Primitive: Outline" << std::endl;
    os << "Exposure:" << std::endl;
    os << m_outline.m_exposure;
    os << "Number of Points:" << std::endl;
    os << m_outline.m_num_points;

    int point_num = 0;
    for (auto coord : *(m_outline.m_coords)) {
        os << "Point: " << point_num++ << std::endl;
        // Type of coord should be Point<std::shared_ptr<ArithmeticExpressionElement> >
        os << "X Coordinate:" << std::endl;
        os << coord.x;
        os << "Y Coordinate:" << std::endl;
        os << coord.y;
    }

    os << "Rotation:";
    if (m_outline.m_has_rotation) {
        os << std::endl;
        os << m_outline.m_rotation;
    } else {
        os << " None" << std::endl;
    }
    return os;
}

ApertureMacroPrimitiveOutline::ApertureMacroPrimitiveOutline(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> num_points,
    std::shared_ptr<std::list<Point<std::shared_ptr<ArithmeticExpressionElement> > > > coords,
    std::shared_ptr<ArithmeticExpressionElement> rotation) :
        m_outline(exposure, num_points, coords, rotation)
{}

ApertureMacroPrimitiveOutline::ApertureMacroPrimitiveOutline(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> num_points,
    std::shared_ptr<std::list<Point<std::shared_ptr<ArithmeticExpressionElement> > > > coords) :
        m_outline(exposure, num_points, coords)
{}

ApertureMacroPrimitiveOutline::~ApertureMacroPrimitiveOutline()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroPrimitiveOutline::do_instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    double exposure = m_outline.m_exposure->eval(variable_env);
    double num_points = m_outline.m_num_points->eval(variable_env);
    auto coords = std::make_shared<std::list<Point<double> > >();
    for (auto coord : *(m_outline.m_coords)) {
        coords->push_back(Point<double>(coord.x->eval(variable_env), coord.y->eval(variable_env)));
    }
    if (m_outline.m_has_rotation) {
        double rotation = m_outline.m_rotation->eval(variable_env);
        return std::make_shared<InstantiatedApertureMacroPrimitiveOutline>(exposure, num_points, coords, rotation);
    } else {
        return std::make_shared<InstantiatedApertureMacroPrimitiveOutline>(exposure, num_points, coords);
    }
}

std::ostream& ApertureMacroPrimitiveOutline::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Outline" << std::endl;
	os << "Exposure:" << std::endl;
	os << *(m_outline.m_exposure);
	os << "Number of Points:" << std::endl;
	os << *(m_outline.m_num_points);
	
	int point_num = 0;
	for (auto coord : *(m_outline.m_coords)) {
		os << "Point: " << point_num++ << std::endl;
		// Type of coord should be Point<std::shared_ptr<ArithmeticExpressionElement> >
		os << "X Coordinate:" << std::endl;
		os << *(coord.x);
		os << "Y Coordinate:" << std::endl;
		os << *(coord.y);
	}

	os << "Rotation:";
	if (m_outline.m_has_rotation) {
		os << std::endl;
		os << *(m_outline.m_rotation);
	} else {
		os << " None" << std::endl;
	}
	return os;
}
