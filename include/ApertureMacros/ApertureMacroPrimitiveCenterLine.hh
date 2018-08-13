#ifndef _APERTURE_MACRO_PRIMITIVE_CENTER_LINE_H
#define _APERTURE_MACRO_PRIMITIVE_CENTER_LINE_H

#include "ApertureMacros/ApertureMacroPrimitive.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssueList.hh"
#include "location.hh"

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

    CenterLine(T exposure, T rect_width, T rect_height, T center_x, T center_y, T rotation,
        yy::location exposure_location, yy::location rect_width_location, yy::location rect_height_location,
        yy::location center_x_location, yy::location center_y_location, yy::location rotation_location,
        yy::location location) :
            m_exposure(exposure), m_rect_width(rect_width), m_rect_height(rect_height),
            m_center_x(center_x), m_center_y(center_y), m_rotation(rotation), m_has_rotation(true),
            m_exposure_location(exposure_location), m_rect_width_location(rect_width_location),
            m_rect_height_location(rect_height_location), m_center_x_location(center_x_location),
            m_center_y_location(center_y_location), m_rotation_location(rotation_location),
            m_location(location)
    {}

    CenterLine(T exposure, T rect_width, T rect_height, T center_x, T center_y,
        yy::location exposure_location, yy::location rect_width_location, yy::location rect_height_location,
        yy::location center_x_location, yy::location center_y_location, yy::location location) :
            m_exposure(exposure), m_rect_width(rect_width), m_rect_height(rect_height),
            m_center_x(center_x), m_center_y(center_y), m_has_rotation(false),
            m_exposure_location(exposure_location), m_rect_width_location(rect_width_location),
            m_rect_height_location(rect_height_location), m_center_x_location(center_x_location),
            m_center_y_location(center_y_location), m_location(location)
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
    yy::location m_exposure_location;
    yy::location m_rect_width_location;
    yy::location m_rect_height_location;
    yy::location m_center_x_location;
    yy::location m_center_y_location;
    yy::location m_rotation_location;
    yy::location m_location;
};

class InstantiatedApertureMacroPrimitiveCenterLine : public InstantiatedApertureMacroPrimitive {
public:
    InstantiatedApertureMacroPrimitiveCenterLine(double exposure, double rect_width, double rect_height,
        double center_x, double center_y, double rotation);

    InstantiatedApertureMacroPrimitiveCenterLine(double exposure, double rect_width, double rect_height,
        double center_x, double center_y);

    InstantiatedApertureMacroPrimitiveCenterLine(double exposure, double rect_width, double rect_height,
        double center_x, double center_y, double rotation, yy::location exposure_location,
        yy::location rect_width_location, yy::location rect_height_location,
        yy::location center_x_location, yy::location center_y_location,
        yy::location rotation_location, yy::location location);

    InstantiatedApertureMacroPrimitiveCenterLine(double exposure, double rect_width, double rect_height,
        double center_x, double center_y, yy::location exposure_location, yy::location rect_width_location, yy::location rect_height_location,
        yy::location center_x_location, yy::location center_y_location, yy::location location);

    virtual ~InstantiatedApertureMacroPrimitiveCenterLine();

private:
    Gerber::SemanticValidity do_check_semantic_validity(SemanticIssueList& issue_list);
    std::ostream& do_print(std::ostream& os) const;

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

	ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> rect_width,
		std::shared_ptr<ArithmeticExpressionElement> rect_height,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> rotation,
		yy::location exposure_location, yy::location rect_width_location,
		yy::location rect_height_location, yy::location center_x_location,
		yy::location center_y_location, yy::location rotation_location,
		yy::location location);

	ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> rect_width,
		std::shared_ptr<ArithmeticExpressionElement> rect_height,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		yy::location exposure_location, yy::location rect_width_location,
        yy::location rect_height_location, yy::location center_x_location,
        yy::location center_y_location, yy::location location);

	virtual ~ApertureMacroPrimitiveCenterLine();

private:
	std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::ostream& do_print(std::ostream& os) const;

	CenterLine<std::shared_ptr<ArithmeticExpressionElement> > m_center_line;
};

#endif // _APERTURE_MACRO_PRIMITIVE_CENTER_LINE_H
