#ifndef _GERBER_AST_H
#define _GERBER_AST_H

#include "CommandList.hh"

#include <unordered_map>

class GerberAST {
public:
	GerberAST();
	~GerberAST();

private:
	CommandList m_command_list;
	

}

#endif // _GERBER_AST_H
