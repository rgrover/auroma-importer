#include <iostream>
#include <fstream>
#include <getopt.h>

#include <cstdlib>

#include "auromaParser.ih"

/* definitions of some globals */
auromaParserBase::STYPE__ d_val;
Para *currentPara = NULL;

auromaFlexLexer *lexer;

void
parseOptions(int   argc,
             char *argv[],
             outputMode_t &mode)
{
    int c;
    int digit_optind = 0;

    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"xml", 
         0                              /* has_arg */,
         reinterpret_cast<int *>(&mode) /* flag */,
         XML                            /* val */
        },
        {"html",
         0                              /* has_arg */,
         reinterpret_cast<int *>(&mode) /* flag */,
         HTML                           /* val */
        },
        {0, 0, 0, 0}
    };

    while ((c = getopt_long_only(argc, argv, "",
                                 long_options, &option_index)) != -1)
        ;
}

int
main(int argc, char *argv[])
{
    if (argc == 1) {
        cerr << "Usage: " << argv[0] << " filename" << endl;
        exit(-1);
    }

    /* parse the command line options */
    outputMode_t outputMode = XML;
    parseOptions(argc, argv, outputMode);
    if (optind != (argc -1)) {
        cerr << "Too many ARGV-elements: ";
        while (optind < argc)
            cerr << argv[optind++] << " ";
        cerr << endl;
        return (-1);
    }
    /* cout << "outputMode: " << outputMode << endl; */

    const char *fileName = argv[optind];
    ifstream *yyin = new ifstream(fileName , ifstream::in);
    if (yyin->fail()) {
        cerr << "failed to open file '" << fileName << "'" << endl;
        exit(-1);
    }

    lexer = new auromaFlexLexer(yyin);
    auromaParser parser(lexer);

    parser.parse();

    parser.emit(outputMode);

    return (0);
}
