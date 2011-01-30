%option prefix="auroma"

%option c++
%option yylineno
%option noyywrap


%x AT_HEAD


%{
     #include <iostream>
     using namespace std;

     enum tokens {
         CHAPTER_TITLE = 1,
         STRING,
         LINE_BREAK,
         COMMA,
         PERIOD,
         M_DASH,
         UNKNOWN_COMMAND,
     };
%}

%%
     BEGIN(AT_HEAD);

    /*
     * Handle the special sequences which may be found at the head of the
     * Auroma text.
     */
<AT_HEAD>^Session\ on:.*\n      /* Ignore the "Session on:" header. */
<AT_HEAD>^Volume:.*\n           /* Ignore the "Volume:" header. */
<AT_HEAD>^[[:space:]]*\n        /* Ignore blank lines in the header */
<AT_HEAD>.                      {
    /* We should switch back to the normal 'INITIAL' start-condition
     * upon discovering any character other than the special sequences
     * permitted in the Auroma texts. */
    BEGIN(INITIAL);
    unput(yytext[0]);
 }

    /*
     * Handle commands.
     */
\\(?i:TC)/[[:space:]]           return CHAPTER_TITLE;
\\(?i:nl)                       return LINE_BREAK;
    /* The unknown command! */
\\[[:alpha:]]+                  {
    cout << "UC:'" << YYText() << "'";
    return UNKNOWN_COMMAND;
 }

    /* Handle Diacritical marks */

    /* String */
(?xi:
 ([[:alnum:]])+(\'s)? |
 "B.C."       |
 "(c)"        
)                               {
    cout << "'" << YYText() << "'";
    return STRING;
 }

\x97                            cout << "--"; return M_DASH;
,                               cout << ","; return COMMA;
\.                              return PERIOD;


%%

int
main()
{
    yyFlexLexer* lexer = new yyFlexLexer;
    while(lexer->yylex() != 0)
        ;
    return 0;
}
