/*
 * Copyright (c) 2011, Rohit Grover
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither Rohit Grover, nor Aurokruti, nor the names of Aurokruti's
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
        {"docbook",
         0                              /* has_arg */,
         reinterpret_cast<int *>(&mode) /* flag */,
         DOCBOOK                        /* val */
        },
        {"wordpress",
         0                              /* has_arg */,
         reinterpret_cast<int *>(&mode) /* flag */,
         WORDPRESS                      /* val */
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
    outputMode_t outputMode = DOCBOOK;
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
