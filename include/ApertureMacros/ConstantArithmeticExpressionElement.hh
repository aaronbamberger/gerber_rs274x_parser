/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _CONSTANT_ARITHMETIC_EXPRESSION_ELEMENT_H
#define _CONSTANT_ARITHMETIC_EXPRESSION_ELEMENT_H

#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>

class ConstantArithmeticExpressionElement : public ArithmeticExpressionElement {
public:
	ConstantArithmeticExpressionElement(double constant);
	virtual ~ConstantArithmeticExpressionElement();

private:
	virtual double do_eval(ApertureMacroVariableEnvironment& variable_env);
	virtual std::ostream& do_print(std::ostream& os) const;

	double m_constant;
};

#endif // _CONSTANT_ARITHMETIC_EXPRESSION_ELEMENT_H
