#ifndef _VARIABLE_REFERENCE_ARITHMETIC_EXPRESSION_H
#define _VARIABLE_REFERENCE_ARITHMETIC_EXPRESSION_H

#include "ArithmeticExpressionElement.hh"

#include <iostream>

class VariableReferenceArithmeticExpressionElement : public ArithmeticExpressionElement {
public:
	VariableReferenceArithmeticExpressionElement(int variable_number);
	virtual ~VariableReferenceArithmeticExpressionElement();

private:
	virtual double do_eval();
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_variable_number;
};

#endif // _VARIABLE_REFERENCE_ARITHMETIC_EXPRESSION_H