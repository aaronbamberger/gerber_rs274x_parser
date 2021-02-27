/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "ApertureMacros/ApertureMacroPrimitiveVectorLine.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>
#include <memory>

InstantiatedApertureMacroPrimitiveVectorLine::InstantiatedApertureMacroPrimitiveVectorLine(double exposure,
    double line_width,
    double start_x,
    double start_y,
    double end_x,
    double end_y,
    double rotation) :
        m_vector_line(exposure, line_width, start_x, start_y, end_x, end_y, rotation)
{}

InstantiatedApertureMacroPrimitiveVectorLine::InstantiatedApertureMacroPrimitiveVectorLine(double exposure,
    double line_width,
    double start_x,
    double start_y,
    double end_x,
    double end_y) :
        m_vector_line(exposure, line_width, start_x, start_y, end_x, end_y)
{}

InstantiatedApertureMacroPrimitiveVectorLine::~InstantiatedApertureMacroPrimitiveVectorLine()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitiveVectorLine::do_check_semantic_validity(SemanticIssueList& issue_list)
{
    // TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& InstantiatedApertureMacroPrimitiveVectorLine::do_print(std::ostream& os) const
{
    os << "Instantiated Macro Primitive: Vector Line" << std::endl;
    os << "Exposure: " << m_vector_line.m_exposure << std::endl;
    os << "Line Width: " << m_vector_line.m_line_width << std::endl;
    os << "Start (X): " << m_vector_line.m_start_x << std::endl;
    os << "Start (Y): " << m_vector_line.m_start_y << std::endl;
    os << "End (X): " << m_vector_line.m_end_x << std::endl;
    os << "End (Y): " << m_vector_line.m_end_y << std::endl;
    os << "Rotation: ";
    if (m_vector_line.m_has_rotation) {
        os << m_vector_line.m_rotation << std::endl;
    } else {
        os << "None" << std::endl;
    }
    return os;
}

ApertureMacroPrimitiveVectorLine::ApertureMacroPrimitiveVectorLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> line_width,
    std::shared_ptr<ArithmeticExpressionElement> start_x,
    std::shared_ptr<ArithmeticExpressionElement> start_y,
    std::shared_ptr<ArithmeticExpressionElement> end_x,
    std::shared_ptr<ArithmeticExpressionElement> end_y,
    std::shared_ptr<ArithmeticExpressionElement> rotation) :
        m_vector_line(exposure, line_width, start_x, start_y, end_x, end_y, rotation)
{}

ApertureMacroPrimitiveVectorLine::ApertureMacroPrimitiveVectorLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> line_width,
    std::shared_ptr<ArithmeticExpressionElement> start_x,
    std::shared_ptr<ArithmeticExpressionElement> start_y,
    std::shared_ptr<ArithmeticExpressionElement> end_x,
    std::shared_ptr<ArithmeticExpressionElement> end_y) :
        m_vector_line(exposure, line_width, start_x, start_y, end_x, end_y)
{}

ApertureMacroPrimitiveVectorLine::~ApertureMacroPrimitiveVectorLine()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroPrimitiveVectorLine::do_instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    double exposure = m_vector_line.m_exposure->eval(variable_env);
    double line_width = m_vector_line.m_line_width->eval(variable_env);
    double start_x = m_vector_line.m_start_x->eval(variable_env);
    double start_y = m_vector_line.m_start_y->eval(variable_env);
    double end_x = m_vector_line.m_end_x->eval(variable_env);
    double end_y = m_vector_line.m_end_y->eval(variable_env);
    if (m_vector_line.m_has_rotation) {
        double rotation = m_vector_line.m_rotation->eval(variable_env);
        return std::make_shared<InstantiatedApertureMacroPrimitiveVectorLine>(exposure, line_width, start_x, start_y, end_x, end_y, rotation);
    } else {
        return std::make_shared<InstantiatedApertureMacroPrimitiveVectorLine>(exposure, line_width, start_x, start_y, end_x, end_y);
    }
}

std::ostream& ApertureMacroPrimitiveVectorLine::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Vector Line" << std::endl;
	os << "Exposure:" << std::endl;
	os << *(m_vector_line.m_exposure);
	os << "Line Width:" << std::endl;
	os << *(m_vector_line.m_line_width);
	os << "Start (X):" << std::endl;
	os << *(m_vector_line.m_start_x);
	os << "Start (Y):" << std::endl;
	os << *(m_vector_line.m_start_y);
	os << "End (X):" << std::endl;
	os << *(m_vector_line.m_end_x);
	os << "End (Y):" << std::endl;
	os << *(m_vector_line.m_end_y);
	os << "Rotation:";
	if (m_vector_line.m_has_rotation) {
		os << std::endl;
		os << *(m_vector_line.m_rotation);
	} else {
		os << " None" << std::endl;
	}
	return os;
}
