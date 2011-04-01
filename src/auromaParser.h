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

// Generated by Bisonc++ V2.7.0 on Wed, 02 Feb 2011 18:33:03 +0530

#ifndef auromaParser_h_included
#define auromaParser_h_included

#include <cstring>
#include <stack>
#include <cassert>

using namespace std;

// $insert baseclass
#include "auromaParserbase.h"

#undef yyFlexLexer
#define yyFlexLexer auromaFlexLexer
#include <FlexLexer.h>

extern auromaParserBase::STYPE__ d_val;

#include "outputMode.h"
#include "para.h"
#include "containerDirective.h"
#include "paraElementContainer.h"
#include "variousContainerDirectives.h"

#undef auromaParser
class auromaParser: public auromaParserBase
{
  public:
    ~auromaParser();

public:
    auromaParser(yyFlexLexer *lexerIn) :
        lexer(lexerIn), precedingWhiteSpace(NULL)
        {
            /* empty */
        }

    // The main parser function
    int parse();

    // support for the stack of elementContainers
    void newPara(void);
    void newDirective(ContainerDirective *directive);
    void finishPara(void);
    void pushSubContainer(void);
    void pushSubContainer(const char *containerType);
    void popSubContainer(void);
    ParaElementContainer *currentContainer(void);
    bool                  currentContainerIsPara(void);

    void updatePrecedingWhiteSpace(const char *precedingWhiteSpace);

    void emit(outputMode_t outputMode);

private:
    yyFlexLexer *lexer;

    vector<ParaOrDirective *>     pods;
    stack<ParaElementContainer *> elementContainerStack;

    // a temporary location to hold blank spaces as they are encountered
    const char *precedingWhiteSpace;

    void error(char const *msg);    // called on (syntax) errors
    int lex();                      // returns the next token from the
    // lexical scanner.

    void print();                   // use, e.g., d_token, d_loc

    void setDval(STYPE__ val) {
        d_val__ = val;
    }

    // support functions for parse():
    void executeAction(int ruleNr);
    void errorRecovery();
    int lookup(bool recovery);
    void nextToken();
};

inline
auromaParser::~auromaParser()
{
    assert(elementContainerStack.empty());

    // free up all the paragraphs
    vector<ParaOrDirective *>::iterator iter;
    for (iter = pods.begin(); iter != pods.end(); iter++) {
        delete(*iter);
    }
}


/* 
 * This is where we connect the parser with the lexical analyser.
 */
inline int
auromaParser::lex()
{
    int token;

    token = lexer->yylex();     // Get a token.
    setDval(d_val);             // Assign the semantic value in the
                                // global 'd_val' into the parser's
                                // private d_val__

    /* switch (token) { */
    /* case auromaParserBase::STRING: */
    /*     cout << lexer->lineno() << " token: " << token << " dval: '" << d_val << "'" << endl; */
    /*     break; */
    /* case auromaParserBase::PAGE_CMD: */
    /*     cout << lexer->lineno() << " token: PAGE_CMD" << endl; */
    /*     break; */
    /* case auromaParserBase::NEWLINE: */
    /*     cout << lexer->lineno() << " token: NEWLINE" << endl; */
    /*     break; */
    /* case auromaParserBase::BLANK_SPACE: */
    /*     cout << lexer->lineno() << " token: BLANK" << endl; */
    /*     break; */
    /* default: */
    /*     cout << lexer->lineno() << " token: " << token << endl; */
    /*     break; */
    /* } */

    return (token);
}

inline ParaElementContainer *
auromaParser::currentContainer(void)
{
    /* cout << "top: " << containerStack.top() << endl; */
    return elementContainerStack.top();
}

inline bool
auromaParser::currentContainerIsPara(void)
{
    return (elementContainerStack.size() == 1);
}

inline void
auromaParser::error(char const *msg)
{
    std::cerr << "\033[01;31mpaser: line "
              << lexer->lineno() << ":\033[00m "
              << msg << '\n';
}


// $insert print
inline void
auromaParser::print()
{

}

#endif
