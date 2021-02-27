/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "ApertureMacros/BinaryOperationArithmeticExpressionElement.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>
#include <memory>

BinaryOperationArithmeticExpressionElement::BinaryOperationArithmeticExpressionElement(BinaryOperationType op_type, std::shared_ptr<ArithmeticExpressionElement> left_arg, std::shared_ptr<ArithmeticExpressionElement> right_arg) :
	m_op_type(op_type),
	m_left_arg(left_arg),
	m_right_arg(right_arg)
{}

BinaryOperationArithmeticExpressionElement::~BinaryOperationArithmeticExpressionElement()
{}

double BinaryOperationArithmeticExpressionElement::do_eval(ApertureMacroVariableEnvironment& variable_env)
{
	double result = 0.0;
	switch (m_op_type) {
    case BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_ADD:
        result = m_left_arg->eval(variable_env) + m_right_arg->eval(variable_env);
        break;

    case BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_SUB:
        result = m_left_arg->eval(variable_env) - m_right_arg->eval(variable_env);
        break;

    case BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_MULT:
        result = m_left_arg->eval(variable_env) * m_right_arg->eval(variable_env);
        break;

    case BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_DIV:
        result = m_left_arg->eval(variable_env) / m_right_arg->eval(variable_env);
        break;
	}
	return result;
}

std::ostream& BinaryOperationArithmeticExpressionElement::do_print(std::ostream& os) const
{
	os << "Binary Operation: ";
	switch (m_op_type) {
		case BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_ADD:
			os << "Add" << std::endl;
			break;

		case BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_SUB:
			os << "Subtract" << std::endl;
			break;

		case BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_MULT:
			os << "Multiply" << std::endl;
			break;

		case BinaryOperationArithmeticExpressionElement::BinaryOperationType::BINARY_OPERATION_TYPE_DIV:
			os << "Divide" << std::endl;
			break;
	}

	os << "Left Argument:" << std::endl;
	os << *m_left_arg;
	os << "Right Argument:" << std::endl;
	os << *m_right_arg;
	return os;
}
