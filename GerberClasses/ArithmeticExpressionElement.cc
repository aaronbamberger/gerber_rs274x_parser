#include "ArithmeticExpressionElement.hh"

#include <iostream>

ArithmeticExpressionElement::ArithmeticExpressionElement()
{}

ArithmeticExpressionElement::~ArithmeticExpressionElement()
{}

std::ostream& operator<<(std::ostream& os, const ArithmeticExpressionElement& expression_element)
{
	return expression_element.do_print(os);
}