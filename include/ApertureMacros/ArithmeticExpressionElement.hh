/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _ARITHMETIC_EXPRESSION_ELEMENT_H
#define _ARITHMETIC_EXPRESSION_ELEMENT_H

#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>

class ArithmeticExpressionElement {
public:
	ArithmeticExpressionElement();
	virtual ~ArithmeticExpressionElement();

	double eval(ApertureMacroVariableEnvironment& variable_env);

	friend std::ostream& operator<<(std::ostream& os, const ArithmeticExpressionElement& expression_element);

private:
	virtual double do_eval(ApertureMacroVariableEnvironment& variable_env) = 0;
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _ARITHMETIC_EXPRESSION_ELEMENT_H
