/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_MACRO_VARIABLE_DEFINITION_H
#define _APERTURE_MACRO_VARIABLE_DEFINITION_H

#include "ApertureMacros/ApertureMacroContent.hh"
#include "ApertureMacros/ArithmeticExpressionElement.hh"
#include "ApertureMacros/InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"

#include <iostream>
#include <memory>

class ApertureMacroVariableDefinition : public ApertureMacroContent {
public:
	ApertureMacroVariableDefinition(int var_num, std::shared_ptr<ArithmeticExpressionElement> var_value);
	virtual ~ApertureMacroVariableDefinition();

private:
	virtual std::shared_ptr<InstantiatedApertureMacroPrimitive> do_instantiate(ApertureMacroVariableEnvironment& variable_env);
	virtual std::ostream& do_print(std::ostream& os) const;

	int m_var_num;
	std::shared_ptr<ArithmeticExpressionElement> m_var_value;
};

#endif // _APERTURE_MACRO_VARIABLE_DEFINITION_H
