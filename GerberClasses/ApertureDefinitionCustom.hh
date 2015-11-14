#ifndef _APERTURE_DEFINITION_CUSTOM_H
#define _APERTURE_DEFINITION_CUSTOM_H

#include "ApertureDefinition.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"

#include <iostream>
#include <memory>
#include <list>
#include <string>

class ApertureDefinitionCustom : public ApertureDefinition {
public:
	ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name, std::shared_ptr<std::list<double> > modifier_list);
	ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name);
	virtual ~ApertureDefinitionCustom();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	std::string m_custom_aperture_name;
	std::shared_ptr<std::list<double> > m_modifier_list;
};

#endif // _APERTURE_DEFINITION_CUSTOM_H
