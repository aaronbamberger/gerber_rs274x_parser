/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

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
