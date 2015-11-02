#ifndef _ARITHMETIC_EXPRESSION_ELEMENT_H
#define _ARITHMETIC_EXPRESSION_ELEMENT_H

#include "../GraphicsState.hh"

#include <iostream>

class ArithmeticExpressionElement {
public:
	ArithmeticExpressionElement();
	virtual ~ArithmeticExpressionElement();

	friend std::ostream& operator<<(std::ostream& os, const ArithmeticExpressionElement& expression_element);

private:
	virtual double eval(const GraphicsState& graphics_state) = 0;
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _ARITHMETIC_EXPRESSION_ELEMENT_H