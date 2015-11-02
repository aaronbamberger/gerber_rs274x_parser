#include "gerber_rs274x_scanner.hh"

#include <stdio.h>

GerberRS274XScanner::GerberRS274XScanner(std::istream* arg_yyin, std::ostream* arg_yyout) : yyFlexLexer(arg_yyin, arg_yyout)
{
	this->set_debug(1);
}

int GerberRS274XScanner::yylex(yy::GerberRS274XParser::semantic_type* yylval_in, yy::GerberRS274XParser::location_type* yylloc_in)
{
	this->yylval = yylval_in;
	this->yylloc = yylloc_in;
	return this->yylex();
}