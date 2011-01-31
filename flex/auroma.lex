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
         BOOK_TITLE_CMD = 1,         /* For book titles. */
         CHAPTER_NUMBER_CMD,         /* e.g. Chapter IX */
         CHAPTER_TITLE_CMD,          /* Chapter Headings. */
         CHAPTER_GROUP_TITLE_CMD,    /* Title for a group of chapters. */
         CHAPTER_GROUP_SUBTITLE_CMD, /* Title for chapter within a chap-group.*/
         CHAPTER_TERMINATOR_CENTERED_CMD, /* Centered text to end a chapter. */
         PARA_CMD,
         CHAPTER_HEAD_QUOTE_CMD, /* Quotations following a chapter heading. */
         QUOTE_CMD,                  /* Indented quotations. */
         REFERENCE_CMD,              /* References for quotations. */
         FOOTNOTE_CMD,
         FOOTNOTE_QUADSPACE_CMD,     /* 12pt. space in a footnote context */
         POEM_CMD,                   /* Enter poem mode. */
         PROSE_CMD,                  /* return to default (prose) mode */
         BOLD_ITALICS_FACE_CMD,      /* Bold and italics. */
         BOLD_FACE_CMD,
         ITALICS_FACE_CMD,
         SLANT_CMD,                  /* slanted text */
         NOINDENT_CMD,               /* Begin paragraph without indentation. */
         FOOTER_CENTERED_TEXT_CMD,  /* Centered text at the footer of a page. */
         DROP_CMD,
         NODROP_CMD,
         LINE_BREAK_CMD,
         DOTS_CMD,                   /* ... */
         DOTSNS_CMD,                 /* dots without a space following them */
         TSTAR_CMD,                  /* triple star, centered. */
         UNKNOWN_COMMAND,
         BEGIN_BLOCK,
         END_BLOCK,
         STRING,

         LONG_DASH,
         SINGLE_QUOTE,
         DOUBLE_QUOTES,
         OPENING_SINGLE_QUOTE,
         OPENING_DOUBLE_QUOTES,
         CLOSING_DOUBLE_QUOTES,
         OPENING_PAREN,
         CLOSING_PAREN,
         OPENING_SQUARE_BRACKET,
         CLOSING_SQUARE_BRACKET,
         PUNCTUATION_MARK,
         NEWLINE,
         WHITE_SPACE,
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
\\(?i:tcfup)/{commandTerminator}   return CHAPTER_GROUP_TITLE_CMD;
\\(?i:tcsub)/{commandTerminator}   return CHAPTER_GROUP_SUBTITLE_CMD;
\\(?i:tcn)/{commandTerminator}     return CHAPTER_NUMBER_CMD;
\\(?i:tscc)/{commandTerminator}    return CHAPTER_TERMINATOR_CENTERED_CMD;
\\(?i:par)/{commandTerminator}     return PARA_CMD;
\\(?i:pf)/{commandTerminator}      return NOINDENT_CMD;
\\(?i:noindent)/{commandTerminator} return NOINDENT_CMD;
\\(?i:bf)/{commandTerminator}      return NOINDENT_CMD;/* not sure about this */
\\(?i:csf)/{commandTerminator}     return CHAPTER_HEAD_QUOTE_CMD;
\\(?i:sf)/{commandTerminator}      return CHAPTER_HEAD_QUOTE_CMD;
\\(?i:quote)/{commandTerminator}   return QUOTE_CMD;
\\(?i:sref)/{commandTerminator}    return REFERENCE_CMD;
\\(?i:pnote)/{commandTerminator}   return FOOTNOTE_CMD;
\\(?i:note)/{commandTerminator}    return FOOTNOTE_CMD;
\\(?i:lnote)/{commandTerminator}   return FOOTNOTE_CMD;
\\(?i:poem)/{commandTerminator}    return POEM_CMD;
\\(?i:prose)/{commandTerminator}   return PROSE_CMD;
\\(?i:fnquad)/{commandTerminator}  return FOOTNOTE_QUADSPACE_CMD;
\\(?i:s)/{commandTerminator}       return SLANT_CMD;
\\(?i:sforced)/{commandTerminator} return SLANT_CMD;
\\(?i:ftext)/{commandTerminator}   return FOOTER_CENTERED_TEXT_CMD;
\\(?i:drop)/{commandTerminator}    return DROP_CMD;
\\(?i:nodrop)/{commandTerminator}  return NODROP_CMD;
\\(?i:ftextbi)/{commandTerminator} return BOLD_ITALICS_FACE_CMD;
\\(?i:ftextb)/{commandTerminator}  return BOLD_FACE_CMD;
\\(?i:it)/{commandTerminator}      return ITALICS_FACE_CMD;
\\(?i:nl)/{commandTerminator}      return LINE_BREAK_CMD;
\\(?i:dots)/{commandTerminator}    return DOTS_CMD;
\\(?i:sdots)/{commandTerminator}   return DOTS_CMD;
\\(?i:dotsns)/{commandTerminator}  return DOTSNS_CMD;
\\(?i:tstar)/{commandTerminator}   return TSTAR_CMD;
\\(?i:text)/{commandTerminator} /* ignore */
\\(?i:BC)/{commandTerminator}   /* ignore */
\\(?i:hbox)/{commandTerminator} /* ignore */
\\(?i:nh)/{commandTerminator}   /* ignore */
\\(?i:si)/{commandTerminator}   /* ignore */
\\(?i:rl)/{commandTerminator}   /* ignore */
\\(?i:pi)/{commandTerminator}   /* ignore */
\\(?i:quad)/{commandTerminator} /* ignore */
\\(?i:pnotes)/{commandTerminator}  /* ignore */
\\(?i:lnotes)/{commandTerminator}  /* ignore */
\\(?i:oquad)/{commandTerminator}   /* ignore */
\\(?i:qquad)/{commandTerminator}   /* ignore */
\\(?i:medskip)/{commandTerminator} /* ignore */
\\(?i:bigskip)/{commandTerminator} /* ignore */
\\(?i:relax)/{commandTerminator}   /* ignore */
\\(?i:phantom)/{commandTerminator} /* ignore */
\\(?i:fsqstart)/{commandTerminator} /* ignore */
\\(?i:fsqend)/{commandTerminator}   /* ignore */
\\(?i:dropquote)/{commandTerminator}  /* ignore */
\\(?i:shortlines)/{commandTerminator} /* ignore; but needs to be addressed */
\\[[:digit:]]/{commandTerminator}     /* ignore; but needs to be addressed */

\.\.\.                          /* ignore dots; handled by \dots */
[[:space:]]*\*[[:space:]]*\*[[:space:]]*\* /* ignore tstar */
\{                                 return BEGIN_BLOCK;
\}                                 return END_BLOCK;
    /* The unknown command! */
\\[[:alnum:]]+                  {
    cout << "\033[01;31mline:"
         << yylineno << " Unknown Command:\033[00m'" << YYText() << "'"
         << endl;
    return UNKNOWN_COMMAND;
 }


    /* String */
(?xi:
 ([[:alnum:]] |
  \-          |
  \xF1        |                 /* \~n */
  \xEA        |                 /* \^e */
  \xE9        |                 /* \'e */
  \x96        |                 /* long dash */
  \xE7        |                 /* \c{c} */
  \xFC        |                 /* \"u */
  /* Handle Diacritical marks */
  (\\=  |
   \\\. |
   \\,  |
   \\\' |
   \\\" |
   \\^  |
   \\`  |
   \\~  |
   \\c  )[[:alpha:]])+
 /* Handle the apostrophe s */
 (\'s)?
)                               {
    /* cout << "'" << YYText() << "'"; */
    return STRING;
 }

    /* Punctuations marks */
\x97                            return LONG_DASH;
`                               return OPENING_SINGLE_QUOTE;
\x93|``                         return OPENING_DOUBLE_QUOTES;
\x94|''                         return CLOSING_DOUBLE_QUOTES;
\'                              return SINGLE_QUOTE;
\"                              return DOUBLE_QUOTES;
[-,:;\.\?!/&]                   return PUNCTUATION_MARK;
\(                              return OPENING_PAREN;
\)                              return CLOSING_PAREN;
\[                              return OPENING_SQUARE_BRACKET;
\]                              return CLOSING_SQUARE_BRACKET;
\r                              /* ignore */
\n                              return NEWLINE;


[[:space:]]+                    return WHITE_SPACE;

 /* Default catch-all rules; error reporting */
\\[^[:alnum:][:blank:]][[:alpha:]] {
    cout << "\033[01;31mline:" << yylineno
         << ": unknown diacritical mark: \033[00m'" << YYText() << "'" << endl;
 }
.                               {
    cout << "\033[01;31mline:" << yylineno
         << ": unexpected byte: \033[00m'" << YYText() << "'" << endl;
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
