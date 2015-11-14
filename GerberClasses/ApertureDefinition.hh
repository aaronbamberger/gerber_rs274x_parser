#ifndef _APERTURE_DEFINITION_H
#define _APERTURE_DEFINITION_H

#include "Command.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>
#include <string>

class ApertureDefinition : public Command {
public:
	ApertureDefinition(int aperture_number);
	ApertureDefinition(int aperture_number, yy::location aperture_number_location, yy::location location);
	virtual ~ApertureDefinition();

protected:
	int m_aperture_number;
	yy::location m_aperture_number_location;
	yy::location m_location;

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg) = 0;
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

#endif // _APERTURE_DEFINITION_H
