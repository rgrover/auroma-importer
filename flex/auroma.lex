 /* Options */
%option prefix="auroma"

%option c++
%option yylineno
%option noyywrap

 /* Start condition needed to scan metadata. */
%x AT_HEAD                      

 /* Definitions */
commandTerminator [[:space:]\\{]
%{
     #include <iostream>
     using namespace std;

     enum tokens {
         BOOK_TITLE_CMD = 1,    /* For book titles. */
         CHAPTER_NUMBER_CMD,    /* Chapter IX */
         CHAPTER_TITLE_CMD,     /* Chapter Headings. */
         QUOTE_CMD,             /* Indented quotations */
         REFERENCE_CMD,         /* References for quotations */
         FOOTNOTE_CMD,
         NOTE_CMD,
         PARA_CMD,
         FOOTER_TEXT_CMD,
         DROP_CMD,
         NODROP_CMD,
         ITALICS_CMD,
         LINE_BREAK_CMD,
         DOTS_CMD,
         DOTSNS_CMD,         /* dots without a space following them */
         BEGIN_BLOCK,
         END_BLOCK,
         STRING,
         COMMA,
         PERIOD,
         OPENING_DOUBLE_QUOTES,
         CLOSING_DOUBLE_QUOTES,
         SEMICOLON,
         M_DASH,
         NEWLINE,
         UNKNOWN_COMMAND,
     };
%}

%%
     /*
      * We expect there to be special metadata at the head of text
      * files. We begin with the start condition AT_HEAD in order to
      * deal with this information.
      */
     BEGIN(AT_HEAD);

    /*
     * Handle the special sequences which may be found at the head of the
     * Auroma text.
     */
<AT_HEAD>^Session\ on:.*\n      /* Ignore the "Session on:" header. */
<AT_HEAD>^Volume:.*\n           /* Ignore the "Volume:" header. */
<AT_HEAD>^[[:space:]]*\n        /* Ignore blank lines in the header */
<AT_HEAD>.                      {
    /*
     * Switch back to the normal 'INITIAL' start-condition upon
     * discovering any character other than the special sequences
     * permitted in the metadata section.
     */
    BEGIN(INITIAL);
    unput(yytext[0]);
 }

    /*
     * Handle commands.
     */
\\(?i:tpt)/{commandTerminator}     return BOOK_TITLE_CMD;
\\(?i:tc)/{commandTerminator}      return CHAPTER_TITLE_CMD;
\\(?i:tcf)/{commandTerminator}     return CHAPTER_TITLE_CMD;
\\(?i:tcn)/{commandTerminator}     return CHAPTER_NUMBER_CMD;
\\(?i:par)/{commandTerminator}     return PARA_CMD;
\\(?i:csf)/{commandTerminator}     return QUOTE_CMD;
\\(?i:sf)/{commandTerminator}      return QUOTE_CMD;
\\(?i:sref)/{commandTerminator}    return REFERENCE_CMD;
\\(?i:pnote)/{commandTerminator}   return FOOTNOTE_CMD;
\\(?i:note)/{commandTerminator}    return NOTE_CMD;
\\(?i:ftext)/{commandTerminator}   return FOOTER_TEXT_CMD;
\\(?i:drop)/{commandTerminator}    return DROP_CMD;
\\(?i:nodrop)/{commandTerminator}  return NODROP_CMD;
\\(?i:it)/{commandTerminator}      return ITALICS_CMD;
\\(?i:nl)/{commandTerminator}      return LINE_BREAK_CMD;
\\(?i:dots)/{commandTerminator}    return DOTS_CMD;
\\(?i:dotsns)/{commandTerminator}  return DOTSNS_CMD;
\.\.\.                          /* ignore dots; handled by \dots */
\{                                 return BEGIN_BLOCK;
\}                                 return END_BLOCK;
    /* The unknown command! */
\\[[:alpha:]]+                  {
    cout << endl << "\033[01;31mline:" << yylineno << " UC:\033[00m'" << YYText() << "'" << endl;
    return UNKNOWN_COMMAND;
 }

    /* Handle Diacritical marks */

    /* String */
(?xi:
 ([[:alnum:]])+(\'s)?
)                               {
    cout << "'" << YYText() << "'";
    return STRING;
 }

    /* Punctuations marks */
\x97                            cout << "--"; return M_DASH;
\x93|``                         cout << "``"; return OPENING_DOUBLE_QUOTES;
\x94|''                         cout << "''"; return CLOSING_DOUBLE_QUOTES;
,                               cout << ","; return COMMA;
;                               cout << ";"; return SEMICOLON;
\.                              return PERIOD;
\r                              /* ignore */
\n                              cout << endl; return NEWLINE;


%%

int
main()
{
    yyFlexLexer* lexer = new yyFlexLexer;
    while(lexer->yylex() != 0)
        ;
    return 0;
}
