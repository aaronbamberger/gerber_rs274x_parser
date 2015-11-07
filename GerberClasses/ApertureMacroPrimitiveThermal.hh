#ifndef _APERTURE_MACRO_PRIMITIVE_THERMAL_H
#define _APERTURE_MACRO_PRIMITIVE_THERMAL_H

#include "ApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

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
	std::ostream& do_print(std::ostream& os) const;

	std::shared_ptr<ArithmeticExpressionElement> m_center_x;
	std::shared_ptr<ArithmeticExpressionElement> m_center_y;
	std::shared_ptr<ArithmeticExpressionElement> m_outer_diameter;
	std::shared_ptr<ArithmeticExpressionElement> m_inner_diameter;
	std::shared_ptr<ArithmeticExpressionElement> m_gap_thickness;
	std::shared_ptr<ArithmeticExpressionElement> m_rotation;
};

#endif // _APERTURE_MACRO_PRIMITIVE_THERMAL_H