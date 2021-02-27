/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

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
