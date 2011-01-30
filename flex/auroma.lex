%option prefix="auroma"

%option c++
%option yylineno
%option noyywrap
%x AT_HEAD

%%
     BEGIN(AT_HEAD);

    /* Handle the special sequences which may be found at the head of the
     * Auroma text. */
<AT_HEAD>^Session\ on:.*\n      /* Ignore the "Session on:" header. */
<AT_HEAD>^Volume:.*\n           /* Ignore the "Volume:" header. */
<AT_HEAD>.                      {
    /* We should switch back to the normal 'INITIAL' start-condition
     * upon discovering any character other than the special sequences
     * permitted in the Auroma texts. */
    BEGIN(INITIAL);
    unput(yytext[0]);
 }


%%

int
main()
{
    yyFlexLexer* lexer = new yyFlexLexer;
    while(lexer->yylex() != 0)
        ;
    return 0;
}
