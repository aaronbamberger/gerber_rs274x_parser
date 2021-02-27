/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _VARIABLE_REFERENCE_ARITHMETIC_EXPRESSION_H
#define _VARIABLE_REFERENCE_ARITHMETIC_EXPRESSION_H

#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>

class VariableReferenceArithmeticExpressionElement : public ArithmeticExpressionElement {
public:
	VariableReferenceArithmeticExpressionElement(int variable_number);
	virtual ~VariableReferenceArithmeticExpressionElement();

private:
	virtual double do_eval(ApertureMacroVariableEnvironment& variable_env);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_variable_number;
};

#endif // _VARIABLE_REFERENCE_ARITHMETIC_EXPRESSION_H
