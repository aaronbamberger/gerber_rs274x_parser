#ifndef GERBER_RS274X_PARSER_DRIVER_H
#define GERBER_RS274X_PARSER_DRIVER_H

// Need to do this to prevent redefinition error from yyFlexLexer
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <iostream>

class GerberRS274XScanner : public yyFlexLexer {
public:
	GerberRS274XScanner(std::istream *arg_yyin, std::ostream *arg_yyout);

	// This is the overloaded scanning function that bison will call
	int yylex(YYSTYPE* semantic_value, YYLTYPE* location);

private:
	// This is the scanning function created by flex.  We make this private and define our
	// own yylex that delegates to this function so that we can accept the extra arguments
	// that bison passes
	virtual int yylex();

	// Pointer to semantic value passed by bison
	// that we can use in the flex actions
	YYSTYPE* yylval;

	// Pointer to location value passed by bison
	// that we can use in the flex actions
	YYLTYPE* yyloc;
};

#endif // GERBER_RS274X_PARSER_DRIVER_H