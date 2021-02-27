/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _BINARY_OPERATION_ARITHMETIC_EXPRESSION_ELEMENT_H
#define _BINARY_OPERATION_ARITHMETIC_EXPRESSION_ELEMENT_H

#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>
#include <memory>

class BinaryOperationArithmeticExpressionElement : public ArithmeticExpressionElement {
public:
	enum class BinaryOperationType {
		BINARY_OPERATION_TYPE_ADD,
		BINARY_OPERATION_TYPE_SUB,
		BINARY_OPERATION_TYPE_MULT,
		BINARY_OPERATION_TYPE_DIV
	};

	BinaryOperationArithmeticExpressionElement(BinaryOperationType op_type, std::shared_ptr<ArithmeticExpressionElement> left_arg, std::shared_ptr<ArithmeticExpressionElement> right_arg);
	virtual ~BinaryOperationArithmeticExpressionElement();

private:
	virtual double do_eval(ApertureMacroVariableEnvironment& variable_env);
	virtual std::ostream& do_print(std::ostream& os) const;

	BinaryOperationType m_op_type;
	std::shared_ptr<ArithmeticExpressionElement> m_left_arg;
	std::shared_ptr<ArithmeticExpressionElement> m_right_arg;
};

#endif // _BINARY_OPERATION_ARITHMETIC_EXPRESSION_ELEMENT_H
