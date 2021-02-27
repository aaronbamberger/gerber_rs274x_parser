/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_MACRO_PRIMITIVE_MOIRE_H
#define _APERTURE_MACRO_PRIMITIVE_MOIRE_H

#include "ApertureMacros/ApertureMacroPrimitive.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>
#include <memory>

template <typename T> struct Moire {
    Moire(T center_x, T center_y, T outer_diameter, T ring_thickness, T ring_gap, T max_rings, T crosshair_thickness, T crosshair_length, T rotation) :
        m_center_x(center_x), m_center_y(center_y), m_outer_diameter(outer_diameter), m_ring_thickness(ring_thickness), m_ring_gap(ring_gap),
        m_max_rings(max_rings), m_crosshair_thickness(crosshair_thickness), m_crosshair_length(crosshair_length), m_rotation(rotation), m_has_rotation(true)
    {}

    Moire(T center_x, T center_y, T outer_diameter, T ring_thickness, T ring_gap, T max_rings, T crosshair_thickness, T crosshair_length) :
        m_center_x(center_x), m_center_y(center_y), m_outer_diameter(outer_diameter), m_ring_thickness(ring_thickness), m_ring_gap(ring_gap),
        m_max_rings(max_rings), m_crosshair_thickness(crosshair_thickness), m_crosshair_length(crosshair_length), m_has_rotation(false)
    {}

    ~Moire()
    {}

    T m_center_x;
    T m_center_y;
    T m_outer_diameter;
    T m_ring_thickness;
    T m_ring_gap;
    T m_max_rings;
    T m_crosshair_thickness;
    T m_crosshair_length;
    T m_rotation;
    bool m_has_rotation;
};

class InstantiatedApertureMacroPrimitiveMoire : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitiveMoire(double center_x,
        double center_y,
        double outer_diameter,
        double ring_thickness,
        double ring_gap,
        double max_rings,
        double crosshair_thickness,
        double crosshair_length,
        double rotation);

    InstantiatedApertureMacroPrimitiveMoire(double center_x,
        double center_y,
        double outer_diameter,
        double ring_thickness,
        double ring_gap,
        double max_rings,
        double crosshair_thickness,
        double crosshair_length);

    virtual ~InstantiatedApertureMacroPrimitiveMoire();

private:
    Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
    std::ostream& do_print(std::ostream& os) const;

    Moire<double> m_moire;
};

class ApertureMacroPrimitiveMoire : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveMoire(std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
		std::shared_ptr<ArithmeticExpressionElement> ring_thickness,
		std::shared_ptr<ArithmeticExpressionElement> ring_gap,
		std::shared_ptr<ArithmeticExpressionElement> max_rings,
		std::shared_ptr<ArithmeticExpressionElement> crosshair_thickness,
		std::shared_ptr<ArithmeticExpressionElement> crosshair_length,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitiveMoire(std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
		std::shared_ptr<ArithmeticExpressionElement> ring_thickness,
		std::shared_ptr<ArithmeticExpressionElement> ring_gap,
		std::shared_ptr<ArithmeticExpressionElement> max_rings,
		std::shared_ptr<ArithmeticExpressionElement> crosshair_thickness,
		std::shared_ptr<ArithmeticExpressionElement> crosshair_length);

	virtual ~ApertureMacroPrimitiveMoire();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	Moire<std::shared_ptr<ArithmeticExpressionElement> > m_moire;
};

#endif // _APERTURE_MACRO_PRIMITIVE_MOIRE_H
