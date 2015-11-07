#ifndef _APERTURE_MACRO_H
#define _APERTURE_MACRO_H

#include "Command.hh"
#include "ApertureMacroContent.hh"

#include <iostream>
#include <string>
#include <memory>
#include <list>

class ApertureMacro : public Command {
public:
	ApertureMacro(char* macro_name, std::shared_ptr<std::list<std::shared_ptr<ApertureMacroContent> > > macro_content_list);
	virtual ~ApertureMacro();

private:
	virtual bool do_check_semantic_validity(std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	std::string m_macro_name;
	std::shared_ptr<std::list<std::shared_ptr<ApertureMacroContent> > > m_macro_content_list;
};

#endif // _APERTURE_MACRO_H