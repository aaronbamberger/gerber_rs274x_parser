#include "ApertureMacroPrimitiveThermal.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

InstantiatedApertureMacroPrimitiveThermal::InstantiatedApertureMacroPrimitiveThermal(double center_x,
    double center_y,
    double outer_diameter,
    double inner_diameter,
    double gap_thickness,
    double rotation) :
        m_thermal(center_x, center_y, outer_diameter, inner_diameter, gap_thickness, rotation)
{}

InstantiatedApertureMacroPrimitiveThermal::InstantiatedApertureMacroPrimitiveThermal(double center_x,
    double center_y,
    double outer_diameter,
    double inner_diameter,
    double gap_thickness) :
        m_thermal(center_x, center_y, outer_diameter, inner_diameter, gap_thickness)
{}

InstantiatedApertureMacroPrimitiveThermal::~InstantiatedApertureMacroPrimitiveThermal()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitiveThermal::do_check_semantic_validity(SemanticIssueList& issue_list)
{
    // TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& InstantiatedApertureMacroPrimitiveThermal::do_print(std::ostream& os) const
{
    os << "Instantiated Macro Primitive: Thermal" << std::endl;
    os << "Center (X):" << std::endl;
    os << m_thermal.m_center_x;
    os << "Center (Y):" << std::endl;
    os << m_thermal.m_center_y;
    os << "Outer Diameter:" << std::endl;
    os << m_thermal.m_outer_diameter;
    os << "Inner Diameter:" << std::endl;
    os << m_thermal.m_inner_diameter;
    os << "Gap Thickness:" << std::endl;
    os << m_thermal.m_gap_thickness;
    os << "Rotation:";
    if (m_thermal.m_has_rotation) {
        os << std::endl;
        os << m_thermal.m_rotation;
    } else {
        os << " None" << std::endl;
    }
    return os;
}

ApertureMacroPrimitiveThermal::ApertureMacroPrimitiveThermal(std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
    std::shared_ptr<ArithmeticExpressionElement> inner_diameter,
    std::shared_ptr<ArithmeticExpressionElement> gap_thickness,
    std::shared_ptr<ArithmeticExpressionElement> rotation) :
        m_thermal(center_x, center_y, outer_diameter, inner_diameter, gap_thickness, rotation)
{}

ApertureMacroPrimitiveThermal::ApertureMacroPrimitiveThermal(std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
    std::shared_ptr<ArithmeticExpressionElement> inner_diameter,
    std::shared_ptr<ArithmeticExpressionElement> gap_thickness) :
        m_thermal(center_x, center_y, outer_diameter, inner_diameter, gap_thickness)
{}

ApertureMacroPrimitiveThermal::~ApertureMacroPrimitiveThermal()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroPrimitiveThermal::do_instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    double center_x = m_thermal.m_center_x->eval(variable_env);
    double center_y = m_thermal.m_center_y->eval(variable_env);
    double outer_diameter = m_thermal.m_outer_diameter->eval(variable_env);
    double inner_diameter = m_thermal.m_inner_diameter->eval(variable_env);
    double gap_thickness = m_thermal.m_gap_thickness->eval(variable_env);
    if (m_thermal.m_has_rotation) {
        double rotation = m_thermal.m_rotation->eval(variable_env);
        return std::make_shared<InstantiatedApertureMacroPrimitiveThermal>(center_x, center_y, outer_diameter, inner_diameter, gap_thickness, rotation);
    } else {
        return std::make_shared<InstantiatedApertureMacroPrimitiveThermal>(center_x, center_y, outer_diameter, inner_diameter, gap_thickness);
    }
}

std::ostream& ApertureMacroPrimitiveThermal::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Thermal" << std::endl;
	os << "Center (X):" << std::endl;
	os << *(m_thermal.m_center_x);
	os << "Center (Y):" << std::endl;
	os << *(m_thermal.m_center_y);
	os << "Outer Diameter:" << std::endl;
	os << *(m_thermal.m_outer_diameter);
	os << "Inner Diameter:" << std::endl;
	os << *(m_thermal.m_inner_diameter);
	os << "Gap Thickness:" << std::endl;
	os << *(m_thermal.m_gap_thickness);
	os << "Rotation:";
	if (m_thermal.m_has_rotation) {
		os << std::endl;
		os << *(m_thermal.m_rotation);
	} else {
		os << " None" << std::endl;
	}
	return os;
}
