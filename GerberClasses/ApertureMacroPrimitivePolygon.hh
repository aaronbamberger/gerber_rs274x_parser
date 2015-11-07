#ifndef _APERTURE_MACRO_PRIMITIVE_POLYGON_H
#define _APERTURE_MACRO_PRIMITIVE_POLYGON_H

#include "ApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>

class ApertureMacroPrimitivePolygon : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitivePolygon(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_vertices,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> diameter,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitivePolygon(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_vertices,
		std::shared_ptr<ArithmeticExpressionElement> center_x,
		std::shared_ptr<ArithmeticExpressionElement> center_y,
		std::shared_ptr<ArithmeticExpressionElement> diameter);

	virtual ~ApertureMacroPrimitivePolygon();

private:
	std::ostream& do_print(std::ostream& os) const;

	std::shared_ptr<ArithmeticExpressionElement> m_exposure;
	std::shared_ptr<ArithmeticExpressionElement> m_num_vertices;
	std::shared_ptr<ArithmeticExpressionElement> m_center_x;
	std::shared_ptr<ArithmeticExpressionElement> m_center_y;
	std::shared_ptr<ArithmeticExpressionElement> m_diameter;
	std::shared_ptr<ArithmeticExpressionElement> m_rotation;
};

#endif // _APERTURE_MACRO_PRIMITIVE_POLYGON_H