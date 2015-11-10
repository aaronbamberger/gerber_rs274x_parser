#ifndef _APERTURE_MACRO_PRIMITIVE_CENTER_LINE_H
#define _APERTURE_MACRO_PRIMITIVE_CENTER_LINE_H

#include "ApertureMacroPrimitive.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

template <typename T> struct CenterLine {
    CenterLine(T exposure, T rect_width, T rect_height, T center_x, T center_y, T rotation) :
        m_exposure(exposure), m_rect_width(rect_width), m_rect_height(rect_height),
        m_center_x(center_x), m_center_y(center_y), m_rotation(rotation), m_has_rotation(true)
    {}

    CenterLine(T exposure, T rect_width, T rect_height, T center_x, T center_y) :
        m_exposure(exposure), m_rect_width(rect_width), m_rect_height(rect_height),
        m_center_x(center_x), m_center_y(center_y), m_has_rotation(false)
    {}

    ~CenterLine()
    {}

    T m_exposure;
    T m_rect_width;
    T m_rect_height;
    T m_center_x;
    T m_center_y;
    T m_rotation;
    bool m_has_rotation;
};

class InstantiatedApertureMacroPrimitiveCenterLine : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitiveCenterLine(double exposure,
        double rect_width,
        double rect_height,
        double center_x,
        double center_y,
        double rotation);

    InstantiatedApertureMacroPrimitiveCenterLine(double exposure,
        double rect_width,
        double rect_height,
        double center_x,
        double center_y);

    virtual ~InstantiatedApertureMacroPrimitiveCenterLine();

private:
    Gerber::SemanticValidity do_check_semantic_validity();

    CenterLine<double> m_center_line;
};

class ApertureMacroPrimitiveCenterLine : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> rect_width,
		std::shared_ptr<ArithmeticExpressionElement> rect_height,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> rect_width,
		std::shared_ptr<ArithmeticExpressionElement> rect_height,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y);

	virtual ~ApertureMacroPrimitiveCenterLine();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	CenterLine<std::shared_ptr<ArithmeticExpressionElement> > m_center_line;
};

#endif // _APERTURE_MACRO_PRIMITIVE_CENTER_LINE_H
