/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "ApertureMacros/ConstantArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>

ConstantArithmeticExpressionElement::ConstantArithmeticExpressionElement(double constant) : m_constant(constant)
{}

ConstantArithmeticExpressionElement::~ConstantArithmeticExpressionElement()
{}

double ConstantArithmeticExpressionElement::do_eval(ApertureMacroVariableEnvironment& variable_env)
{
	return m_constant;
}

std::ostream& ConstantArithmeticExpressionElement::do_print(std::ostream& os) const
{
	os << "Constant: " << m_constant << std::endl;
	return os;
}
