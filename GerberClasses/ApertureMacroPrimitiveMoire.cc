#include "ApertureMacroPrimitiveMoire.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

InstantiatedApertureMacroPrimitiveMoire::InstantiatedApertureMacroPrimitiveMoire(double center_x,
    double center_y,
    double outer_diameter,
    double ring_thickness,
    double ring_gap,
    double max_rings,
    double crosshair_thickness,
    double crosshair_length,
    double rotation) :
        m_moire(center_x, center_y, outer_diameter, ring_thickness, ring_gap, max_rings, crosshair_thickness, crosshair_length, rotation)
{}

InstantiatedApertureMacroPrimitiveMoire::InstantiatedApertureMacroPrimitiveMoire(double center_x,
    double center_y,
    double outer_diameter,
    double ring_thickness,
    double ring_gap,
    double max_rings,
    double crosshair_thickness,
    double crosshair_length) :
        m_moire(center_x, center_y, outer_diameter, ring_thickness, ring_gap, max_rings, crosshair_thickness, crosshair_length)
{}

InstantiatedApertureMacroPrimitiveMoire::~InstantiatedApertureMacroPrimitiveMoire()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitiveMoire::do_check_semantic_validity(SemanticIssueList& issue_list)
{
    // TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& InstantiatedApertureMacroPrimitiveMoire::do_print(std::ostream& os) const
{
    os << "Instantiated Macro Primitive: Moire" << std::endl;
    os << "Center (X):" << std::endl;
    os << m_moire.m_center_x;
    os << "Center (Y):" << std::endl;
    os << m_moire.m_center_y;
    os << "Outer Diameter:" << std::endl;
    os << m_moire.m_outer_diameter;
    os << "Ring Thickness:" << std::endl;
    os << m_moire.m_ring_thickness;
    os << "Ring Gap:" << std::endl;
    os << m_moire.m_ring_gap;
    os << "Max Rings:" << std::endl;
    os << m_moire.m_max_rings;
    os << "Crosshair Thickness:" << std::endl;
    os << m_moire.m_crosshair_thickness;
    os << "Crosshair Length:" << std::endl;
    os << m_moire.m_crosshair_length;
    os << "Rotation:";
    if (m_moire.m_has_rotation) {
        os << std::endl;
        os << m_moire.m_rotation;
    } else {
        os << " None" << std::endl;
    }
    return os;
}

ApertureMacroPrimitiveMoire::ApertureMacroPrimitiveMoire(std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
    std::shared_ptr<ArithmeticExpressionElement> ring_thickness,
    std::shared_ptr<ArithmeticExpressionElement> ring_gap,
    std::shared_ptr<ArithmeticExpressionElement> max_rings,
    std::shared_ptr<ArithmeticExpressionElement> crosshair_thickness,
    std::shared_ptr<ArithmeticExpressionElement> crosshair_length,
    std::shared_ptr<ArithmeticExpressionElement> rotation) :
        m_moire(center_x, center_y, outer_diameter, ring_thickness, ring_gap, max_rings, crosshair_thickness, crosshair_length, rotation)
{}

ApertureMacroPrimitiveMoire::ApertureMacroPrimitiveMoire(std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
    std::shared_ptr<ArithmeticExpressionElement> ring_thickness,
    std::shared_ptr<ArithmeticExpressionElement> ring_gap,
    std::shared_ptr<ArithmeticExpressionElement> max_rings,
    std::shared_ptr<ArithmeticExpressionElement> crosshair_thickness,
    std::shared_ptr<ArithmeticExpressionElement> crosshair_length) :
        m_moire(center_x, center_y, outer_diameter, ring_thickness, ring_gap, max_rings, crosshair_thickness, crosshair_length)
{}

ApertureMacroPrimitiveMoire::~ApertureMacroPrimitiveMoire()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroPrimitiveMoire::do_instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    double center_x = m_moire.m_center_x->eval(variable_env);
    double center_y = m_moire.m_center_y->eval(variable_env);
    double outer_diameter = m_moire.m_outer_diameter->eval(variable_env);
    double ring_thickness = m_moire.m_ring_thickness->eval(variable_env);
    double ring_gap = m_moire.m_ring_gap->eval(variable_env);
    double max_rings = m_moire.m_max_rings->eval(variable_env);
    double crosshair_thickness = m_moire.m_crosshair_thickness->eval(variable_env);
    double crosshair_length = m_moire.m_crosshair_length->eval(variable_env);
    if (m_moire.m_has_rotation) {
        double rotation = m_moire.m_rotation->eval(variable_env);
        return std::make_shared<InstantiatedApertureMacroPrimitiveMoire>(center_x, center_y, outer_diameter, ring_thickness, ring_gap, max_rings, crosshair_thickness, crosshair_length, rotation);
    } else {
        return std::make_shared<InstantiatedApertureMacroPrimitiveMoire>(center_x, center_y, outer_diameter, ring_thickness, ring_gap, max_rings, crosshair_thickness, crosshair_length);
    }
}

std::ostream& ApertureMacroPrimitiveMoire::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Moire" << std::endl;
	os << "Center (X):" << std::endl;
	os << *(m_moire.m_center_x);
	os << "Center (Y):" << std::endl;
	os << *(m_moire.m_center_y);
	os << "Outer Diameter:" << std::endl;
	os << *(m_moire.m_outer_diameter);
	os << "Ring Thickness:" << std::endl;
	os << *(m_moire.m_ring_thickness);
	os << "Ring Gap:" << std::endl;
	os << *(m_moire.m_ring_gap);
	os << "Max Rings:" << std::endl;
	os << *(m_moire.m_max_rings);
	os << "Crosshair Thickness:" << std::endl;
	os << *(m_moire.m_crosshair_thickness);
	os << "Crosshair Length:" << std::endl;
	os << *(m_moire.m_crosshair_length);
	os << "Rotation:";
	if (m_moire.m_has_rotation) {
		os << std::endl;
		os << *(m_moire.m_rotation);
	} else {
		os << " None" << std::endl;
	}
	return os;
}
