#include <iostream>
#include <fstream>

#include <cstdlib>

using namespace std;

#undef yyFlexLexer
#define yyFlexLexer auromaFlexLexer
#include <FlexLexer.h>


/*
 * We need to declare a global variable to hold the semantic value of
 * tokens; this isn't required for the lexer, but is necessary for the
 * parser.
 */
#include "auromaParserbase.h"
auromaParserBase::STYPE__ d_val;


int
main(int argc, const char *argv[])
{
    if (argc == 1) {
        cerr << "Usage: " << argv[0] << " filename" << endl;
        exit(-1);
    }

    ifstream *yyin = new ifstream(argv[1] , ifstream::in);
    if (yyin->fail()) {
        cerr << "failed to open file '" << argv[1] << "'" << endl;
        exit(-1);
    }

    yyFlexLexer *lexer = new yyFlexLexer(yyin);

    /* /\* int ret; *\/ */
    while((/* ret =  */lexer->yylex()) != 0) {
        /* cout << "r" << ret << " " */;
    }

    return 0;
}
