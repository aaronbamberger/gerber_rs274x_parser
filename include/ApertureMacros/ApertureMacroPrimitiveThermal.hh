#ifndef _APERTURE_MACRO_PRIMITIVE_THERMAL_H
#define _APERTURE_MACRO_PRIMITIVE_THERMAL_H

#include "ApertureMacros/ApertureMacroPrimitive.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>
#include <memory>

template <typename T> struct Thermal {
    Thermal(T center_x, T center_y, T outer_diameter, T inner_diameter, T gap_thickness, T rotation) :
        m_center_x(center_x), m_center_y(center_y), m_outer_diameter(outer_diameter), m_inner_diameter(inner_diameter),
        m_gap_thickness(gap_thickness), m_rotation(rotation), m_has_rotation(true)
    {}

    Thermal(T center_x, T center_y, T outer_diameter, T inner_diameter, T gap_thickness) :
        m_center_x(center_x), m_center_y(center_y), m_outer_diameter(outer_diameter), m_inner_diameter(inner_diameter),
        m_gap_thickness(gap_thickness), m_has_rotation(false)
    {}

    ~Thermal()
    {}

    T m_center_x;
    T m_center_y;
    T m_outer_diameter;
    T m_inner_diameter;
    T m_gap_thickness;
    T m_rotation;
    bool m_has_rotation;
};

class InstantiatedApertureMacroPrimitiveThermal : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitiveThermal(double center_x,
        double center_y,
        double outer_diameter,
        double inner_diameter,
        double gap_thickness,
        double rotation);

    InstantiatedApertureMacroPrimitiveThermal(double center_x,
        double center_y,
        double outer_diameter,
        double inner_diameter,
        double gap_thickness);

    virtual ~InstantiatedApertureMacroPrimitiveThermal();

private:
    Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
    std::ostream& do_print(std::ostream& os) const;

    Thermal<double> m_thermal;
};

class ApertureMacroPrimitiveThermal : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveThermal(std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
		std::shared_ptr<ArithmeticExpressionElement> inner_diameter,
		std::shared_ptr<ArithmeticExpressionElement> gap_thickness,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitiveThermal(std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> outer_diameter,
		std::shared_ptr<ArithmeticExpressionElement> inner_diameter,
		std::shared_ptr<ArithmeticExpressionElement> gap_thickness);

	virtual ~ApertureMacroPrimitiveThermal();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	Thermal<std::shared_ptr<ArithmeticExpressionElement> > m_thermal;
};

#endif // _APERTURE_MACRO_PRIMITIVE_THERMAL_H
