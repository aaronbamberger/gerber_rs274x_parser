#include "ApertureMacroPrimitiveCenterLine.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"
#include "ApertureMacroVariableEnvironment.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <memory>

InstantiatedApertureMacroPrimitiveCenterLine::InstantiatedApertureMacroPrimitiveCenterLine(double exposure,
    double rect_width,
    double rect_height,
    double center_x,
    double center_y,
    double rotation) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y, rotation)
{}

InstantiatedApertureMacroPrimitiveCenterLine::InstantiatedApertureMacroPrimitiveCenterLine(double exposure,
    double rect_width,
    double rect_height,
    double center_x,
    double center_y) :
        m_center_line(exposure, rect_width, rect_height, center_x, center_y)
{}

InstantiatedApertureMacroPrimitiveCenterLine::~InstantiatedApertureMacroPrimitiveCenterLine()
{}

Gerber::SemanticValidity InstantiatedApertureMacroPrimitiveCenterLine::do_check_semantic_validity()
{
    // TODO: Implement
    return Gerber::SemanticValidity::SEMANTIC_VALIDITY_OK;
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
        return std::make_shared<InstantiatedApertureMacroPrimitiveCenterLine>(exposure, rect_width, rect_height, center_x, center_y, rotation);
    } else {
        return std::make_shared<InstantiatedApertureMacroPrimitiveCenterLine>(exposure, rect_width, rect_height, center_x, center_y);
    }
}

std::ostream& ApertureMacroPrimitiveCenterLine::do_print(std::ostream& os) const
{
	os << "Macro Primitive: Center Line" << std::endl;
	os << "Exposure:" << std::endl;
	os << *(m_center_line.m_exposure);
	os << "Rectangle Width:" << std::endl;
	os << *(m_center_line.m_rect_width);
	os << "Rectangle Height:" << std::endl;
	os << *(m_center_line.m_rect_height);
	os << "Center (X):" << std::endl;
	os << *(m_center_line.m_center_x);
	os << "Center (Y):" << std::endl;
	os << *(m_center_line.m_center_y);
	os << "Rotation:";
	if (m_center_line.m_has_rotation) {
		os << std::endl;
		os << *(m_center_line.m_rotation);
	} else {
		os << " None" << std::endl;
	}
	return os;
}
