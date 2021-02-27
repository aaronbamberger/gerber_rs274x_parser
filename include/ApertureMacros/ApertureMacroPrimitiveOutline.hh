/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_MACRO_PRIMITIVE_OUTLINE_H
#define _APERTURE_MACRO_PRIMITIVE_OUTLINE_H

#include "ApertureMacros/ApertureMacroPrimitive.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "Point.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>
#include <memory>
#include <list>

template <typename T> struct Outline {
    Outline(T exposure, T num_points, std::shared_ptr<std::list<Point<T> > > coords, T rotation) :
        m_exposure(exposure), m_num_points(num_points), m_coords(coords), m_rotation(rotation),
        m_has_rotation(true)
    {}

    Outline(T exposure, T num_points, std::shared_ptr<std::list<Point<T> > > coords) :
        m_exposure(exposure), m_num_points(num_points), m_coords(coords), m_has_rotation(false)
    {}

    ~Outline()
    {}

    T m_exposure;
    T m_num_points;
    std::shared_ptr<std::list<Point<T> > > m_coords;
    T m_rotation;
    bool m_has_rotation;
};

class InstantiatedApertureMacroPrimitiveOutline : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitiveOutline(double exposure,
        double num_points,
        std::shared_ptr<std::list<Point<double> > > coords,
        double rotation);

    InstantiatedApertureMacroPrimitiveOutline(double exposure,
        double num_points,
        std::shared_ptr<std::list<Point<double> > > coords);

    virtual ~InstantiatedApertureMacroPrimitiveOutline();

private:
    Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
    std::ostream& do_print(std::ostream& os) const;

    Outline<double> m_outline;
};

class ApertureMacroPrimitiveOutline : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveOutline(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_points,
		std::shared_ptr<std::list<Point<std::shared_ptr<ArithmeticExpressionElement> > > > coords,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitiveOutline(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_points,
		std::shared_ptr<std::list<Point<std::shared_ptr<ArithmeticExpressionElement> > > > coords);

	virtual ~ApertureMacroPrimitiveOutline();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	Outline<std::shared_ptr<ArithmeticExpressionElement> > m_outline;
};

#endif // _APERTURE_MACRO_PRIMITIVE_OUTLINE_H
