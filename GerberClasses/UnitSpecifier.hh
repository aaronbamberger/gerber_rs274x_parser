#ifndef _UNIT_SPECIFIER_H
#define _UNIT_SPECIFIER_H

#include "Command.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <string>

class UnitSpecifier : public Command {
public:
	UnitSpecifier(Gerber::UnitType unit_type);
	virtual ~UnitSpecifier();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	Gerber::UnitType m_unit_type;
};

#endif // _UNIT_SPECIFIER_H
