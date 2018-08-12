#ifndef _PART_ATTRIBUTE_H
#define _PART_ATTRIBUTE_H

#include "StandardAttribute.hh"

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

	PartAttribute(std::string name, Part part);
	virtual ~PartAttribute();

	void set_other_field(std::string other_field);

private:
	Part m_part;
	std::string m_other_field;
};

#endif // _PART_ATTRIBUTE_H
