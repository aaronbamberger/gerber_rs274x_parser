#ifndef _APERTURE_DEFINITION_CUSTOM_H
#define _APERTURE_DEFINITION_CUSTOM_H

#include "ApertureDefinition.hh"
#include "GlobalDefs.hh"
#include "ApertureDefinitionModifier.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>
#include <memory>
#include <list>
#include <string>

class ApertureDefinitionCustom : public ApertureDefinition {
public:
	ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name, std::shared_ptr<std::list<ApertureDefinitionModifier> > modifier_list);
	ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name);
	ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name, std::shared_ptr<std::list<ApertureDefinitionModifier> > modifier_list,
        yy::location aperture_number_location, yy::location aperture_name_location, yy::location modifier_list_location, yy::location location);
    ApertureDefinitionCustom(int aperture_number, std::string custom_aperture_name,
        yy::location aperture_number_location, yy::location aperture_name_location, yy::location location);
	virtual ~ApertureDefinitionCustom();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	std::string m_custom_aperture_name;
	std::shared_ptr<std::list<ApertureDefinitionModifier> > m_modifier_list;
	yy::location m_aperture_name_location;
	yy::location m_modifier_list_location;
};

#endif // _APERTURE_DEFINITION_CUSTOM_H
