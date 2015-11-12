#ifndef _APERTURE_MACRO_VARIABLE_DEFINITION_H
#define _APERTURE_MACRO_VARIABLE_DEFINITION_H

#include "ApertureMacroContent.hh"
#include "ArithmeticExpressionElement.hh"
#include "InstantiatedApertureMacroPrimitive.hh"
#include "ApertureMacroVariableEnvironment.hh"

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
