#include "ApertureMacros/ApertureMacroPrimitiveCenterLine.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"
#include "SemanticIssue.hh"

#include <iostream>
#include <memory>

InstantiatedApertureMacroPrimitiveCenterLine::InstantiatedApertureMacroPrimitiveCenterLine(double exposure,
    double rect_width, double rect_height, double center_x, double center_y, double rotation) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y, rotation)
{}

InstantiatedApertureMacroPrimitiveCenterLine::InstantiatedApertureMacroPrimitiveCenterLine(double exposure,
    double rect_width, double rect_height, double center_x, double center_y) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y)
{}

InstantiatedApertureMacroPrimitiveCenterLine::InstantiatedApertureMacroPrimitiveCenterLine(double exposure,
    double rect_width, double rect_height, double center_x, double center_y, double rotation,
    yy::location exposure_location, yy::location rect_width_location, yy::location rect_height_location,
    yy::location center_x_location, yy::location center_y_location, yy::location rotation_location,
    yy::location location) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y, rotation,
        exposure_location, rect_width_location, rect_height_location, center_x_location,
        center_y_location, rotation_location, location)
{}

InstantiatedApertureMacroPrimitiveCenterLine::InstantiatedApertureMacroPrimitiveCenterLine(double exposure,
    double rect_width, double rect_height, double center_x, double center_y,
    yy::location exposure_location, yy::location rect_width_location, yy::location rect_height_location,
    yy::location center_x_location, yy::location center_y_location, yy::location location) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y,
        exposure_location, rect_width_location, rect_height_location, center_x_location,
        center_y_location, location)
{}

InstantiatedApertureMacroPrimitiveCenterLine::~InstantiatedApertureMacroPrimitiveCenterLine()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitiveCenterLine::do_check_semantic_validity(SemanticIssueList& issue_list)
{
    // TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
}

std::ostream& InstantiatedApertureMacroPrimitiveCenterLine::do_print(std::ostream& os) const
{
    os << "Instantiated Macro Primitive: Center Line (@" << m_center_line.m_location << ")\n";
    os << "Exposure: " << m_center_line.m_exposure << " (@" << m_center_line.m_exposure_location << ")\n";
    os << "Rectangle Width: " << m_center_line.m_rect_width << " (@" << m_center_line.m_rect_width_location << ")\n";
    os << "Rectangle Height: " << m_center_line.m_rect_height << " (@" << m_center_line.m_rect_height_location << ")\n";
    os << "Center (X): " << m_center_line.m_center_x << " (@" << m_center_line.m_center_x_location << ")\n";
    os << "Center (Y): " << m_center_line.m_center_y << " (@" << m_center_line.m_center_y_location << ")\n";
    os << "Rotation: ";
    if (m_center_line.m_has_rotation) {
        os << m_center_line.m_rotation << " (@" << m_center_line.m_rotation_location << ")" << std::endl;
    } else {
        os << "None" << std::endl;
    }
    return os;
}

ApertureMacroPrimitiveCenterLine::ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> rect_width,
    std::shared_ptr<ArithmeticExpressionElement> rect_height,
    std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    std::shared_ptr<ArithmeticExpressionElement> rotation) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y, rotation)
{}

ApertureMacroPrimitiveCenterLine::ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> rect_width,
    std::shared_ptr<ArithmeticExpressionElement> rect_height,
    std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y)
{}

ApertureMacroPrimitiveCenterLine::ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> rect_width,
    std::shared_ptr<ArithmeticExpressionElement> rect_height,
    std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    std::shared_ptr<ArithmeticExpressionElement> rotation,
    yy::location exposure_location, yy::location rect_width_location,
    yy::location rect_height_location, yy::location center_x_location,
    yy::location center_y_location, yy::location rotation_location,
    yy::location location) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y, rotation,
        exposure_location, rect_width_location, rect_height_location, center_x_location,
        center_y_location, rotation_location, location)
{}

ApertureMacroPrimitiveCenterLine::ApertureMacroPrimitiveCenterLine(std::shared_ptr<ArithmeticExpressionElement> exposure,
    std::shared_ptr<ArithmeticExpressionElement> rect_width,
    std::shared_ptr<ArithmeticExpressionElement> rect_height,
    std::shared_ptr<ArithmeticExpressionElement> center_x,
    std::shared_ptr<ArithmeticExpressionElement> center_y,
    yy::location exposure_location, yy::location rect_width_location,
    yy::location rect_height_location, yy::location center_x_location,
    yy::location center_y_location, yy::location location) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y,
        exposure_location, rect_width_location, rect_height_location, center_x_location,
        center_y_location, location)
{}

ApertureMacroPrimitiveCenterLine::~ApertureMacroPrimitiveCenterLine()
{}

std::shared_ptr<InstantiatedApertureMacroPrimitive> ApertureMacroPrimitiveCenterLine::do_instantiate(ApertureMacroVariableEnvironment& variable_env)
{
    double exposure = m_center_line.m_exposure->eval(variable_env);
    double rect_width = m_center_line.m_rect_width->eval(variable_env);
    double rect_height = m_center_line.m_rect_height->eval(variable_env);
    double center_x = m_center_line.m_center_x->eval(variable_env);
    double center_y = m_center_line.m_center_y->eval(variable_env);
    if (m_center_line.m_has_rotation) {
        double rotation = m_center_line.m_rotation->eval(variable_env);
        return std::make_shared<InstantiatedApertureMacroPrimitiveCenterLine>(exposure, rect_width, rect_height, center_x, center_y, rotation,
            m_center_line.m_exposure_location, m_center_line.m_rect_width_location, m_center_line.m_rect_height_location,
            m_center_line.m_center_x_location, m_center_line.m_center_y_location, m_center_line.m_rotation_location,
            m_center_line.m_location);
    } else {
        return std::make_shared<InstantiatedApertureMacroPrimitiveCenterLine>(exposure, rect_width, rect_height, center_x, center_y,
            m_center_line.m_exposure_location, m_center_line.m_rect_width_location, m_center_line.m_rect_height_location,
            m_center_line.m_center_x_location, m_center_line.m_center_y_location, m_center_line.m_location);
    }
}

std::ostream& ApertureMacroPrimitiveCenterLine::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Center Line (@" << m_center_line.m_location << ")\n";
	os << "Exposure: (@" << m_center_line.m_exposure_location << ")\n";
	os << *(m_center_line.m_exposure);
	os << "Rectangle Width: (@" << m_center_line.m_rect_width_location << ")\n";
	os << *(m_center_line.m_rect_width);
	os << "Rectangle Height: (@" << m_center_line.m_rect_height_location << ")\n";
	os << *(m_center_line.m_rect_height);
	os << "Center (X):  (@" << m_center_line.m_center_x_location << ")\n";
	os << *(m_center_line.m_center_x);
	os << "Center (Y):  (@" << m_center_line.m_center_y_location << ")\n";
	os << *(m_center_line.m_center_y);
	os << "Rotation:";
	if (m_center_line.m_has_rotation) {
		os << " (@" << m_center_line.m_rotation_location << ")" << std::endl;
		os << *(m_center_line.m_rotation);
	} else {
		os << " None" << std::endl;
	}
	return os;
}
