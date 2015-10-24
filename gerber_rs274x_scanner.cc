#include "gerber_rs274x_scanner.hh"

#include <stdio.h>

GerberRS274XScanner::GerberRS274XScanner(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0) : yyFlexLexer(arg_yyin, arg_yyout)
{
	this->set_debug(1);
}

int GerberRS274XScanner::yylex(yy::GerberRS274XParser::semantic_type* yylval, yy::GerberRS274XParser::location_type* yyloc)
{
	this->yylval = yylval;
	this->yylloc = yylloc;
	return this->yylex();
}