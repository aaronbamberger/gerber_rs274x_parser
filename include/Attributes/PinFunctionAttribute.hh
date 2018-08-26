#ifndef _PIN_FUNCTION_ATTRIBUTE_H
#define _PIN_FUNCTION_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"

#include <string>

class PinFunctionAttribute : public StandardAttribute {
public:
	PinFunctionAttribute(ValueWithLocation<std::string> name, ValueWithLocation<std::string> function);
	virtual ~PinFunctionAttribute();

private:
	ValueWithLocation<std::string> m_function;
};

#endif // _PIN_FUNCTION_ATTRIBUTE_H
