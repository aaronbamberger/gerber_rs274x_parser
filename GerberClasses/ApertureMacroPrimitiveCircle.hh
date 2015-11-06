#ifndef _APERTURE_MACRO_PRIMITIVE_CIRCLE_H
#define _APERTURE_MACRO_PRIMITIVE_CIRCLE_H

#include "ApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

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
	std::ostream& do_print(std::ostream& os);

	std::shared_ptr<ArithmeticExpressionElement> m_exposure;
	std::shared_ptr<ArithmeticExpressionElement> m_diameter;
	std::shared_ptr<ArithmeticExpressionElement> m_center_x;
	std::shared_ptr<ArithmeticExpressionElement> m_center_y;
	std::shared_ptr<ArithmeticExpressionElement> m_rotation;
};

#endif // _APERTURE_MACRO_PRIMITIVE_CIRCLE_H