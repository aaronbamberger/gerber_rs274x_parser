#include "ArithmeticExpressionElement.hh"
#include "ApertureMacroVariableEnvironment.hh"

#include <iostream>

ArithmeticExpressionElement::ArithmeticExpressionElement()
{}

ArithmeticExpressionElement::~ArithmeticExpressionElement()
{}

double ArithmeticExpressionElement::eval(ApertureMacroVariableEnvironment& variable_env)
{
	return do_eval(variable_env);
}

std::ostream& operator<<(std::ostream& os, const ArithmeticExpressionElement& expression_element)
{
	return expression_element.do_print(os);
}
