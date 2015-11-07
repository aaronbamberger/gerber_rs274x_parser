#ifndef _APERTURE_MACRO_PRIMITIVE_MOIRE_H
#define _APERTURE_MACRO_PRIMITIVE_MOIRE_H

#include "ApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

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
	std::ostream& do_print(std::ostream& os) const;

	std::shared_ptr<ArithmeticExpressionElement> m_center_x;
	std::shared_ptr<ArithmeticExpressionElement> m_center_y;
	std::shared_ptr<ArithmeticExpressionElement> m_outer_diameter;
	std::shared_ptr<ArithmeticExpressionElement> m_ring_thickness;
	std::shared_ptr<ArithmeticExpressionElement> m_ring_gap;
	std::shared_ptr<ArithmeticExpressionElement> m_max_rings;
	std::shared_ptr<ArithmeticExpressionElement> m_crosshair_thickness;
	std::shared_ptr<ArithmeticExpressionElement> m_crosshair_length;
	std::shared_ptr<ArithmeticExpressionElement> m_rotation;
};

#endif // _APERTURE_MACRO_PRIMITIVE_MOIRE_H