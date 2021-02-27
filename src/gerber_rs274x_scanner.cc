/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#include "gerber_rs274x_scanner.hh"

#include <stdio.h>

GerberRS274XScanner::GerberRS274XScanner(std::istream* arg_yyin, std::ostream* arg_yyout) : yyFlexLexer(arg_yyin, arg_yyout)
{
	this->set_debug(0);
}

int GerberRS274XScanner::yylex(yy::GerberRS274XParser::semantic_type* yylval_in, yy::location* yylloc_in)
{
	this->yylval = yylval_in;
	this->yylloc = yylloc_in;
	return this->yylex();
}
