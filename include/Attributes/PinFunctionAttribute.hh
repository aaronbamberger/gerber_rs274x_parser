#ifndef _PIN_FUNCTION_ATTRIBUTE_H
#define _PIN_FUNCTION_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"

#include <string>

class PinFunctionAttribute : public StandardAttribute {
public:
	PinFunctionAttribute(std::string name, std::string function);
	virtual ~PinFunctionAttribute();

private:
	std::string m_function;
};

#endif // _PIN_FUNCTION_ATTRIBUTE_H
