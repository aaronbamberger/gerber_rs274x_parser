#ifndef _UNIT_SPECIFIER_H
#define _UNIT_SPECIFIER_H

#include "Command.hh"

#include <iostream>
#include <string>

class UnitSpecifier : public Command {
public:
	enum class UnitType {
		UNIT_TYPE_IN,
		UNIT_TYPE_MM
	};

	UnitSpecifier(UnitType unit_type);
	virtual ~UnitSpecifier();

private:
	virtual bool do_check_semantic_validity(std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	UnitType m_unit_type;
};

#endif // _UNIT_SPECIFIER_H