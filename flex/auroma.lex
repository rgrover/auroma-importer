 /* Options */
%option prefix="auroma"

%option c++
%option yylineno
%option noyywrap

 /* Start condition needed to scan metadata. */
%x AT_HEAD                      

 /* Definitions */
EOC                  [[:space:]\\{]              /* command terminator */

%{
     #include <iostream>
     using namespace std;

     enum tokens {
         BOOK_PART_TITLE_CMD = 1,    /* For part titles. */
         BOOK_PART_NUMBER_CMD,       /* For part numbers. */
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
         ENUMERATION_ITEM_CMD,
         BOLD_ITALICS_FACE_CMD,      /* Bold and italics. */
         BOLD_FACE_CMD,
         ITALICS_FACE_CMD,
         SLANT_CMD,                  /* Slanted text. */
         NOINDENT_CMD,               /* Begin paragraph without indentation. */
         FOOTER_CENTERED_TEXT_CMD,   /* Centered text at the footer of a page.*/
         DROP_CMD,                   /* Enlarge the first letter which follows*/
         NODROP_CMD,
         LINE_BREAK_CMD,
         DOTS_CMD,                   /* ... */
         DOTSNS_CMD,                 /* Dots without a space following them */
         TSTAR_CMD,                  /* Triple star, centered. */
         PAGE_CMD,                   /* Page break */
         UNKNOWN_COMMAND,
         BEGIN_BLOCK,
         END_BLOCK,
         STRING,

         N_DASH,
         M_DASH,
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

    /*
     * We expect there to be special metadata at the head of text
     * files. We begin with the start condition AT_HEAD in order to
     * deal with this information.
     */
     #define YY_USER_INIT BEGIN(AT_HEAD);
%}

%%
    /*
     * Handle the special sequences which may be found at the head of the
     * Auroma text.
     */
<AT_HEAD>^Session\ on:.*\n      /* Ignore the "Session on:" header. */
<AT_HEAD>^Volume:.*\n           /* Ignore the "Volume:" header. */
<AT_HEAD>^[[:blank:]]*\n        /* Ignore blank lines in the header */
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
\\(?i:tpt)/{EOC}     return BOOK_PART_TITLE_CMD;
\\(?i:tpn)/{EOC}     return BOOK_PART_NUMBER_CMD;
\\(?i:tc)/{EOC}      return CHAPTER_TITLE_CMD;
\\(?i:tcf)/{EOC}     return CHAPTER_TITLE_CMD;
\\(?i:tcfup)/{EOC}   return CHAPTER_GROUP_TITLE_CMD;
\\(?i:tcsub)/{EOC}   return CHAPTER_GROUP_SUBTITLE_CMD;
\\(?i:tcn)/{EOC}     return CHAPTER_NUMBER_CMD;
\\(?i:tscc)/{EOC}    return CHAPTER_TERMINATOR_CENTERED_CMD;
\\(?i:par)/{EOC}     return PARA_CMD;
\\(?i:pf)/{EOC}      return NOINDENT_CMD;
\\(?i:noindent)/{EOC} return NOINDENT_CMD;
\\(?i:bf)/{EOC}      return NOINDENT_CMD;/* not sure about this */
\\(?i:csf)/{EOC}     return CHAPTER_HEAD_QUOTE_CMD;
\\(?i:sf)/{EOC}      return CHAPTER_HEAD_QUOTE_CMD;
\\(?i:quote)/{EOC}   return QUOTE_CMD;
\\(?i:sref)/{EOC}    return REFERENCE_CMD;
\\(?i:pnote)/{EOC}   return FOOTNOTE_CMD;
\\(?i:note)/{EOC}    return FOOTNOTE_CMD;
\\(?i:lnote)/{EOC}   return FOOTNOTE_CMD;
\\(?i:poem)/{EOC}    return POEM_CMD;
\\(?i:prose)/{EOC}   return PROSE_CMD;
\\(?i:sitem)/{EOC}   return ENUMERATION_ITEM_CMD;
\\(?i:fnquad)/{EOC}  return FOOTNOTE_QUADSPACE_CMD;
\\(?i:s)/{EOC}       return SLANT_CMD;
\\(?i:sforced)/{EOC} return SLANT_CMD;
\\(?i:ftext)/{EOC}   return FOOTER_CENTERED_TEXT_CMD;
\\(?i:drop)/{EOC}    return DROP_CMD;
\\(?i:nodrop)/{EOC}  return NODROP_CMD;
\\(?i:ftextbi)/{EOC} return BOLD_ITALICS_FACE_CMD;
\\(?i:ftextb)/{EOC}  return BOLD_FACE_CMD;
\\(?i:it)/{EOC}      return ITALICS_FACE_CMD;
\\(?i:nl)/{EOC}      return LINE_BREAK_CMD;
\\(?i:dots)/{EOC}    return DOTS_CMD;
\\(?i:sdots)/{EOC}   return DOTS_CMD;
\\(?i:dotsns)/{EOC}  return DOTSNS_CMD;
\\(?i:tstar)/{EOC}   return TSTAR_CMD;
^Page/[[:blank:]](--|[[:digit:]]+) return PAGE_CMD;

\\(?i:text)/{EOC} /* ignore */
\\(?i:BC)/{EOC}   /* ignore */
\\(?i:hbox)/{EOC} /* ignore */
\\(?i:nh)/{EOC}   /* ignore */
\\(?i:si)/{EOC}   /* ignore */
\\(?i:rl)/{EOC}   /* ignore */
\\(?i:pi)/{EOC}   /* ignore */
\\(?i:quad)/{EOC} /* ignore */
\\(?i:pnotes)/{EOC}  /* ignore */
\\(?i:lnotes)/{EOC}  /* ignore */
\\(?i:oquad)/{EOC}   /* ignore */
\\(?i:qquad)/{EOC}   /* ignore */
\\(?i:medskip)/{EOC} /* ignore */
\\(?i:bigskip)/{EOC} /* ignore */
\\(?i:relax)/{EOC}   /* ignore */
\\(?i:phantom)/{EOC} /* ignore */
\\(?i:fsqstart)/{EOC} /* ignore */
\\(?i:fsqend)/{EOC}   /* ignore */
\\(?i:dropquote)/{EOC}  /* ignore */
\\(?i:emptypage)/{EOC}  /* ignore */
\\(?i:shortlines)/{EOC} /* ignore; but needs to be addressed */
\\[[:digit:]]/{EOC}     /* ignore; but needs to be addressed */

\.\.\.                          /* ignore dots; handled by \dots */
[[:blank:]]*\*[[:blank:]]*\*[[:blank:]]*\* /* ignore tstar */
\{                                 return BEGIN_BLOCK;
\}                                 return END_BLOCK;

    /* Punctuations marks */
\-\-                            return N_DASH;
\-\-\-|\x97                     return M_DASH;
`                               return OPENING_SINGLE_QUOTE;
\x93|``                         return OPENING_DOUBLE_QUOTES;
\x94|''                         return CLOSING_DOUBLE_QUOTES;
\'                              return SINGLE_QUOTE;
\"                              return DOUBLE_QUOTES;
\(                              return OPENING_PAREN;
\)                              return CLOSING_PAREN;
\[                              return OPENING_SQUARE_BRACKET;
\]                              return CLOSING_SQUARE_BRACKET;
 /* The default rule for punctuation */
[[:punct:]]                     return PUNCTUATION_MARK;


    /* String */
(?x:
 /* The pattern for the first character of a string */
 ([[:alnum:]]           |
  \\[uU][[:xdigit:]]{4} |        /* allow for UTF-16 */
  /* Handle Diacritical marks */
  (\\=  |
   \\\. |
   \\,  |
   \\\' |
   \\\" |
   \\^  |
   \\`  |
   \\~  |
   \\c  )[[:alpha:]]
  )
 /* followed by other characters, which may even contain some punctuations */
 ([[:alnum:]]           |
  \\[uU][[:xdigit:]]{4} |        /* allow for UTF-16 */
  /* Handle Diacritical marks */
  (\\=  |
   \\\. |
   \\,  |
   \\\' |
   \\\" |
   \\^  |
   \\`  |
   \\~  |
   \\c  )[[:alpha:]]    |
  \'                    |
  \- | \x96             |       /* allow hyphens or n-dashes */
  \\[ ]               /* allow escaped spaces to be part of strings */
  )*
 /* Handle the apostrophe followed by s */
 (\'s)?
)                                      |
(?xi:                           /* common abbreviations */
   "e.g."                 |
   "B.C."                 |
   "B. C."                |
   "A.D."                 |
   "A. D."                |
   "Ave."                 |
   "ed."                  |
   "Gov."                 |
   "i.e."                 |
   "inc."                 |
   "Mr."                  |
   "Mrs."                 |
   "pub."                 |
   "rev."                 |
   "U.S."                 |
   "vs."
)                               {
    /* cout << "s:" << yylineno << "'" << YYText() << "'"; */
    return STRING;
 }


    /* Line terminators */
\r                              /* ignore  */
\n                              return NEWLINE;


[[:blank:]]+                    /* ECHO;  */return WHITE_SPACE;

 /*
  * Default catch-all rules; error reporting
  */

 /* The unknown command! */
\\[[:alnum:]]+                  {
    cerr << "\033[01;31mline:"
         << yylineno << " Unknown Command:\033[00m'" << YYText() << "'"
         << endl;
    return UNKNOWN_COMMAND;
 }

 /* for unsupported diacritical combinations */
\\[^[:alnum:][:blank:]][[:alpha:]] {
    cerr << "\033[01;31mline:" << yylineno
         << ": unknown diacritical mark: \033[00m'" << YYText() << "'" << endl;
 }

 /* For unknown byte--this is the default match. */
.                               {
    cerr << "\033[01;31mline:" << yylineno
         << ": unexpected byte: \033[00m'" << YYText() << "'" << endl;
 }

%%

int
main()
{
    yyFlexLexer* lexer = new yyFlexLexer;
    /* int ret; */

    while((/* ret =  */lexer->yylex()) != 0) {
        /* cout << "r" << ret << " " */;
    }

    return 0;
}
