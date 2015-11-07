#ifndef _APERTURE_MACRO_PRIMITIVE_CENTER_LINE_H
#define _APERTURE_MACRO_PRIMITIVE_CENTER_LINE_H

#include "ApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

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
	std::ostream& do_print(std::ostream& os) const;

	std::shared_ptr<ArithmeticExpressionElement> m_exposure;
	std::shared_ptr<ArithmeticExpressionElement> m_rect_width;
	std::shared_ptr<ArithmeticExpressionElement> m_rect_height;
	std::shared_ptr<ArithmeticExpressionElement> m_center_x;
	std::shared_ptr<ArithmeticExpressionElement> m_center_y;
	std::shared_ptr<ArithmeticExpressionElement> m_rotation;
};

#endif // _APERTURE_MACRO_PRIMITIVE_CENTER_LINE_H