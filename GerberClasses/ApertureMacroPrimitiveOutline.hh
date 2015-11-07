#ifndef _APERTURE_MACRO_PRIMITIVE_OUTLINE_H
#define _APERTURE_MACRO_PRIMITIVE_OUTLINE_H

#include "ApertureMacroPrimitive.hh"
#include "ArithmeticExpressionElement.hh"

#include <iostream>
#include <memory>
#include <utility>
#include <list>

class ApertureMacroPrimitiveOutline : public ApertureMacroPrimitive {
public:
	ApertureMacroPrimitiveOutline(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_points,
		std::shared_ptr<std::list<std::pair<std::shared_ptr<ArithmeticExpressionElement>, std::shared_ptr<ArithmeticExpressionElement> > > > coords,
		std::shared_ptr<ArithmeticExpressionElement> rotation);

	ApertureMacroPrimitiveOutline(std::shared_ptr<ArithmeticExpressionElement> exposure,
		std::shared_ptr<ArithmeticExpressionElement> num_points,
		std::shared_ptr<std::list<std::pair<std::shared_ptr<ArithmeticExpressionElement>, std::shared_ptr<ArithmeticExpressionElement> > > > coords);

	virtual ~ApertureMacroPrimitiveOutline();

private:
	std::ostream& do_print(std::ostream& os) const;

	std::shared_ptr<ArithmeticExpressionElement> m_exposure;
	std::shared_ptr<ArithmeticExpressionElement> m_num_points;
	std::shared_ptr<ArithmeticExpressionElement> m_rotation;
	std::shared_ptr<std::list<std::pair<std::shared_ptr<ArithmeticExpressionElement>, std::shared_ptr<ArithmeticExpressionElement> > > > m_coords;
};

#endif // _APERTURE_MACRO_PRIMITIVE_OUTLINE_H