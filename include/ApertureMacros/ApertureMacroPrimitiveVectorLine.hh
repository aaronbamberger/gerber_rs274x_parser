/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_MACRO_PRIMITIVE_VECTOR_LINE_H
#define _APERTURE_MACRO_PRIMITIVE_VECTOR_LINE_H

#include "ApertureMacros/ApertureMacroPrimitive.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>
#include <memory>

template <typename T> struct VectorLine {
    VectorLine(T exposure, T line_width, T start_x, T start_y, T end_x, T end_y, T rotation) :
        m_exposure(exposure), m_line_width(line_width), m_start_x(start_x), m_start_y(start_y),
        m_end_x(end_x), m_end_y(end_y), m_rotation(rotation), m_has_rotation(true)
    {}

    VectorLine(T exposure, T line_width, T start_x, T start_y, T end_x, T end_y) :
        m_exposure(exposure), m_line_width(line_width), m_start_x(start_x), m_start_y(start_y),
        m_end_x(end_x), m_end_y(end_y), m_has_rotation(false)
    {}

    ~VectorLine()
    {}

    T m_exposure;
    T m_line_width;
    T m_start_x;
    T m_start_y;
    T m_end_x;
    T m_end_y;
    T m_rotation;
    bool m_has_rotation;
};

class InstantiatedApertureMacroPrimitiveVectorLine : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitiveVectorLine(double exposure,
        double line_width,
        double start_x,
        double start_y,
        double end_x,
        double end_y,
        double rotation);

    InstantiatedApertureMacroPrimitiveVectorLine(double exposure,
        double line_width,
        double start_x,
        double start_y,
        double end_x,
        double end_y);

    virtual ~InstantiatedApertureMacroPrimitiveVectorLine();

private:
    Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
    std::ostream& do_print(std::ostream& os) const;

    VectorLine<double> m_vector_line;
};

class ApertureMacroPrimitiveVectorLine : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveVectorLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> line_width,
		std::shared_ptr<ArithmeticExpressionElement> start_x,
		std::shared_ptr<ArithmeticExpressionElement> start_y,
		std::shared_ptr<ArithmeticExpressionElement> end_x,
		std::shared_ptr<ArithmeticExpressionElement> end_y,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitiveVectorLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> line_width,
		std::shared_ptr<ArithmeticExpressionElement> start_x,
		std::shared_ptr<ArithmeticExpressionElement> start_y,
		std::shared_ptr<ArithmeticExpressionElement> end_x,
		std::shared_ptr<ArithmeticExpressionElement> end_y);

	virtual ~ApertureMacroPrimitiveVectorLine();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	VectorLine<std::shared_ptr<ArithmeticExpressionElement> > m_vector_line;
};

#endif // _APERTURE_MACRO_PRIMITIVE_VECTOR_LINE_H
