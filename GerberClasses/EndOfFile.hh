#ifndef _END_OF_FILE_H
#define _END_OF_FILE_H

#include "Command.hh"
#include "GlobalDefs.hh"
#include "../GraphicsState.hh"
#include "../location.hh"

#include <iostream>
#include <string>

class EndOfFile : public Command {
public:
	EndOfFile();
	EndOfFile(yy::location location);
	~EndOfFile();

private:
	virtual Gerber::SemanticValidity do_check_semantic_validity(GraphicsState& graphics_state, std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;

	yy::location m_location;
};

#endif // _END_OF_FILE_H
