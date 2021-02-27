/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "ApertureMacros/ApertureMacroPrimitiveCircle.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

InstantiatedApertureMacroPrimitiveCircle::InstantiatedApertureMacroPrimitiveCircle(double exposure,
    double diameter,
    double center_x,
    double center_y,
    double rotation) :
        m_circle(exposure, diameter, center_x, center_y, rotation)
{}

InstantiatedApertureMacroPrimitiveCircle::InstantiatedApertureMacroPrimitiveCircle(double exposure,
    double diameter,
    double center_x,
    double center_y) :
        m_circle(exposure, diameter, center_x, center_y)
{}

InstantiatedApertureMacroPrimitiveCircle::~InstantiatedApertureMacroPrimitiveCircle()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitiveCircle::do_check_semantic_validity(SemanticIssueList& issue_list)
{
    // TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& InstantiatedApertureMacroPrimitiveCircle::do_print(std::ostream& os) const
{
    os << "Instantiated Macro Primitive: Circle" << std::endl;
    os << "Exposure: " << m_circle.m_exposure << std::endl;
    os << "Diameter: " << m_circle.m_diameter << std::endl;
    os << "Center (X): " << m_circle.m_center_x << std::endl;
    os << "Center (Y): " << m_circle.m_center_y << std::endl;
    os << "Rotation: ";
    if (m_circle.m_has_rotation) {
        os << m_circle.m_rotation << std::endl;
    } else {
        os << "None" << std::endl;
    }
    return os;
}

ApertureMacroPrimitiveCircle::ApertureMacroPrimitiveCircle(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> diameter,
    std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    std::shared_ptr<ArithmeticExpressionElement> rotation) :
        m_circle(exposure, diameter, center_x, center_y, rotation)
{}

ApertureMacroPrimitiveCircle::ApertureMacroPrimitiveCircle(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> diameter,
    std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y) :
        m_circle(exposure, diameter, center_x, center_y)
{}

ApertureMacroPrimitiveCircle::~ApertureMacroPrimitiveCircle()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroPrimitiveCircle::do_instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    double exposure = m_circle.m_exposure->eval(variable_env);
    double diameter = m_circle.m_diameter->eval(variable_env);
    double center_x = m_circle.m_center_x->eval(variable_env);
    double center_y = m_circle.m_center_y->eval(variable_env);
    if (m_circle.m_has_rotation) {
        double rotation = m_circle.m_rotation->eval(variable_env);
        return std::make_shared<InstantiatedApertureMacroPrimitiveCircle>(exposure, diameter, center_x, center_y, rotation);
    } else {
        return std::make_shared<InstantiatedApertureMacroPrimitiveCircle>(exposure, diameter, center_x, center_y);
    }
}

std::ostream& ApertureMacroPrimitiveCircle::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Circle" << std::endl;
	os << "Exposure:" << std::endl;
	os << *(m_circle.m_exposure);
	os << "Diameter:" << std::endl;
	os << *(m_circle.m_diameter);
	os << "Center (X):" << std::endl;
	os << *(m_circle.m_center_x);
	os << "Center (Y):" << std::endl;
	os << *(m_circle.m_center_y);
	os << "Rotation:";
	if (m_circle.m_has_rotation) {
		os << std::endl;
		os << *(m_circle.m_rotation);
	} else {
		os << " None" << std::endl;
	}
	return os;
}
