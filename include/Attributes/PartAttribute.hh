#ifndef _PART_ATTRIBUTE_H
#define _PART_ATTRIBUTE_H

#include "Attributes/StandardAttribute.hh"
#include "Util/ValueWithLocation.hh"

#include <string>

class PartAttribute : public StandardAttribute {
public:
	enum class Part {
		SINGLE,
		ARRAY,
		FABRIATION_PANEL,
		COUPON,
		OTHER
	};

	PartAttribute(ValueWithLocation<std::string> name, ValueWithLocation<Part> part);
	virtual ~PartAttribute();

	void set_other_field(ValueWithLocation<std::string> other_field);

private:
	ValueWithLocation<Part> m_part;
	ValueWithLocation<std::string> m_other_field;
};

#endif // _PART_ATTRIBUTE_H
