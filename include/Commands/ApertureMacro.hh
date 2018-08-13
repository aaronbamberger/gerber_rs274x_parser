#ifndef _APERTURE_MACRO_H
#define _APERTURE_MACRO_H

#include "Commands/Command.hh"
#include "ApertureMacros/ApertureMacroContent.hh"
#include "Apertures/InstantiatedApertureMacro.hh"
#include "ApertureMacros/ApertureMacroVariableEnvironment.hh"
#include "SemanticIssueList.hh"
#include "GraphicsState.hh"
#include "location.hh"
#include "GlobalDefs.hh"

#include <iostream>
#include <string>
#include <memory>
#include <list>

class ApertureMacro : public Command {
public:
	ApertureMacro(std::string macro_name,
        std::shared_ptr<std::list<std::shared_ptr<ApertureMacroContent> > > macro_content);
	ApertureMacro(std::string macro_name,
	        std::shared_ptr<std::list<std::shared_ptr<ApertureMacroContent> > > macro_content,
	        yy::location location);
	virtual ~ApertureMacro();

	std::shared_ptr<InstantiatedApertureMacro> instantiate(ApertureMacroVariableEnvironment& variable_env);

	std::string& macro_name();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, SemanticIssueList& issue_list);
	virtual std::ostream& do_print(std::ostream& os) const;

	std::string m_macro_name;
	std::shared_ptr<std::list<std::shared_ptr<ApertureMacroContent> > > m_macro_content;
	yy::location m_location;
};

#endif // _APERTURE_MACRO_H
