#include <iostream>
#include <fstream>

#include <cstdlib>

#include "auromaParser.ih"

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

    auromaFlexLexer *lexer = new auromaFlexLexer(yyin);
    auromaParser parser(lexer);

    parser.parse();

    return 0;
}
