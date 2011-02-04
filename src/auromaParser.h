// Generated by Bisonc++ V2.7.0 on Wed, 02 Feb 2011 18:33:03 +0530

#ifndef auromaParser_h_included
#define auromaParser_h_included

#include <stack>
#include <cassert>

using namespace std;

// $insert baseclass
#include "auromaParserbase.h"

#undef yyFlexLexer
#define yyFlexLexer auromaFlexLexer
#include <FlexLexer.h>

extern auromaParserBase::STYPE__ d_val;

#include "para.h"
#include "paraElementContainer.h"

#undef auromaParser
class auromaParser: public auromaParserBase
{
  public:
    ~auromaParser();

public:
    auromaParser(yyFlexLexer *lexerIn) :
        lexer(lexerIn)
        {
            /* empty */
        }

    int parse();

    void newPara(void);
    void finishPara(void);
    void pushSubContainer(void);
    void popSubContainer(void);

    ParaElementContainer *currentContainer(void);
    bool                  currentContainerIsPara(void);

    void display();

private:
    yyFlexLexer *lexer;

    vector<Para *>                paragraphs;
    stack<ParaElementContainer *> containerStack;

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
    assert(containerStack.empty());

    // free up all the paragraphs
    vector<Para *>::iterator iter;
    for (iter = paragraphs.begin(); iter != paragraphs.end(); iter++) {
        delete (*iter);
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
    /* default: */
    /*     cout << lexer->lineno() << " token: " << token << endl; */
    /* } */

    return (token);
}

inline ParaElementContainer *
auromaParser::currentContainer(void)
{
    return containerStack.top();
}

inline bool
auromaParser::currentContainerIsPara(void)
{
    return (containerStack.size() == 1);
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
