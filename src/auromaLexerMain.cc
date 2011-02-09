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
