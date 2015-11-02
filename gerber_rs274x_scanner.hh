#ifndef GERBER_RS274X_PARSER_DRIVER_H
#define GERBER_RS274X_PARSER_DRIVER_H

#include "gerber_parser.yy.hh"

// Because of some janky stuff that flex does to allow multiple c++ scanners in the same
// executable, we need to provide our own include guard for FlexLexer.h that depends on
// an internal #define set in FlexLexer.h.  This will probably break when flex is updated.
// This file also must be included in the flex generated implementation file after the flex
// generate implementation file itself includes FlexLexer.h, to prevent multiple definitions
// of yyFlexLexer.  This is accomplished in the flex file by being careful where the include
// for this file appears, see the flex file for more information
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <iostream>

class GerberRS274XScanner : public yyFlexLexer {
public:
	GerberRS274XScanner(std::istream *arg_yyin = 0, std::ostream *arg_yyout = 0);

	// This is the overloaded scanning function that bison will call
	int yylex(yy::GerberRS274XParser::semantic_type* yylval_in, yy::GerberRS274XParser::location_type* yylloc_in);

private:
	// This is the scanning function created by flex.  We make this private and define our
	// own yylex that delegates to this function so that we can accept the extra arguments
	// that bison passes
	virtual int yylex();

	// Pointer to semantic value passed by bison
	// that we can use in the flex actions
	yy::GerberRS274XParser::semantic_type* yylval;

	// Pointer to location value passed by bison
	// that we can use in the flex actions
	yy::GerberRS274XParser::location_type* yylloc;
};

#endif // GERBER_RS274X_PARSER_DRIVER_H