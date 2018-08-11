#ifndef _APERTURE_MACRO_PRIMITIVE_CIRCLE_H
#define _APERTURE_MACRO_PRIMITIVE_CIRCLE_H

#include "ApertureMacroPrimitive.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"

#include <iostream>
#include <memory>

template <typename T> struct Circle {
    Circle(T exposure, T diameter, T center_x, T center_y, T rotation) :
        m_exposure(exposure), m_diameter(diameter), m_center_x(center_x),
        m_center_y(center_y), m_rotation(rotation), m_has_rotation(true)
    {}

    Circle(T exposure, T diameter, T center_x, T center_y) :
        m_exposure(exposure), m_diameter(diameter), m_center_x(center_x),
        m_center_y(center_y), m_has_rotation(false)
    {}

    ~Circle()
    {}

    T m_exposure;
    T m_diameter;
    T m_center_x;
    T m_center_y;
    T m_rotation;
    bool m_has_rotation;
};

class InstantiatedApertureMacroPrimitiveCircle : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitiveCircle(double exposure,
        double diameter,
        double center_x,
        double center_y,
        double rotation);

    InstantiatedApertureMacroPrimitiveCircle(double exposure,
        double diameter,
        double center_x,
        double center_y);

    virtual ~InstantiatedApertureMacroPrimitiveCircle();

private:
    Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
    std::ostream& do_print(std::ostream& os) const;

    Circle<double> m_circle;
};

class ApertureMacroPrimitiveCircle : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveCircle(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> diameter,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitiveCircle(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> diameter,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y);

	virtual ~ApertureMacroPrimitiveCircle();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	Circle<std::shared_ptr<ArithmeticExpressionElement> > m_circle;
};

#endif // _APERTURE_MACRO_PRIMITIVE_CIRCLE_H
