#include "ApertureMacros/ApertureMacroPrimitivePolygon.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

InstantiatedApertureMacroPrimitivePolygon::InstantiatedApertureMacroPrimitivePolygon(double exposure,
    double num_vertices,
    double center_x,
    double center_y,
    double diameter,
    double rotation) :
        m_polygon(exposure, num_vertices, center_x, center_y, diameter, rotation)
{}

InstantiatedApertureMacroPrimitivePolygon::InstantiatedApertureMacroPrimitivePolygon(double exposure,
    double num_vertices,
    double center_x,
    double center_y,
    double diameter) :
        m_polygon(exposure, num_vertices, center_x, center_y, diameter)
{}

InstantiatedApertureMacroPrimitivePolygon::~InstantiatedApertureMacroPrimitivePolygon()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitivePolygon::do_check_semantic_validity(SemanticIssueList& issue_list)
{
    //TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& InstantiatedApertureMacroPrimitivePolygon::do_print(std::ostream& os) const
{
    os << "Instantiated Macro Primitive: Polygon" << std::endl;
    os << "Exposure:" << std::endl;
    os << m_polygon.m_exposure;
    os << "Number of Vertices:" << std::endl;
    os << m_polygon.m_num_vertices;
    os << "Center (X):" << std::endl;
    os << m_polygon.m_center_x;
    os << "Center (Y):" << std::endl;
    os << m_polygon.m_center_y;
    os << "Diameter:" << std::endl;
    os << m_polygon.m_diameter;
    os << "Rotation:";
    if (m_polygon.m_has_rotation) {
        os << std::endl;
        os << m_polygon.m_rotation;
    } else {
        os << " None" << std::endl;
    }
    return os;
}

ApertureMacroPrimitivePolygon::ApertureMacroPrimitivePolygon(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> num_vertices,
    std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    std::shared_ptr<ArithmeticExpressionElement> diameter,
    std::shared_ptr<ArithmeticExpressionElement> rotation) :
        m_polygon(exposure, num_vertices, center_x, center_y, diameter, rotation)
{}

ApertureMacroPrimitivePolygon::ApertureMacroPrimitivePolygon(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> num_vertices,
    std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    std::shared_ptr<ArithmeticExpressionElement> diameter) :
        m_polygon(exposure, num_vertices, center_x, center_y, diameter)
{}

ApertureMacroPrimitivePolygon::~ApertureMacroPrimitivePolygon()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroPrimitivePolygon::do_instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    double exposure = m_polygon.m_exposure->eval(variable_env);
    double num_vertices = m_polygon.m_num_vertices->eval(variable_env);
    double center_x = m_polygon.m_center_x->eval(variable_env);
    double center_y = m_polygon.m_center_y->eval(variable_env);
    double diameter = m_polygon.m_diameter->eval(variable_env);
    if (m_polygon.m_has_rotation) {
        double rotation = m_polygon.m_rotation->eval(variable_env);
        return std::make_shared<InstantiatedApertureMacroPrimitivePolygon>(exposure, num_vertices, center_x, center_y, diameter, rotation);
    } else {
        return std::make_shared<InstantiatedApertureMacroPrimitivePolygon>(exposure, num_vertices, center_x, center_y, diameter);
    }
}

std::ostream& ApertureMacroPrimitivePolygon::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Polygon" << std::endl;
	os << "Exposure:" << std::endl;
	os << *(m_polygon.m_exposure);
	os << "Number of Vertices:" << std::endl;
	os << *(m_polygon.m_num_vertices);
	os << "Center (X):" << std::endl;
	os << *(m_polygon.m_center_x);
	os << "Center (Y):" << std::endl;
	os << *(m_polygon.m_center_y);
	os << "Diameter:" << std::endl;
	os << *(m_polygon.m_diameter);
	os << "Rotation:";
	if (m_polygon.m_has_rotation) {
		os << std::endl;
		os << *(m_polygon.m_rotation);
	} else {
		os << " None" << std::endl;
	}
	return os;
}
