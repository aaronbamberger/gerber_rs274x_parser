#include "gerber_rs274x_scanner.hh"

GerberRS274XScanner::GerberRS274XScanner(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0)
{
	yyFlexLexer(arg_yyin, arg_yyout);
}

int GerberRS274XScanner::yylex(YYSTYPE* semantic_value, YYLTYPE* location)
{
	this->yylval = semantic_value;
	this->yyloc = location;
	return this->yylex();
}