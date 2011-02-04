 /* Options */
%option prefix="auroma"

%option c++
%option yylineno
%option noyywrap

 /* Start condition needed to scan metadata. */
%x AT_HEAD                      

 /* Definitions */
EOC                  [[:space:][:punct:]]              /* command terminator */

%{
using namespace std;
#include "auromaParserbase.h"
extern auromaParserBase::STYPE__ d_val;

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
\\(?i:tpt)/{EOC}     return 1;/* return auromaParserBase::BOOK_PART_TITLE_CMD; */
\\(?i:tpn)/{EOC}     return 1;/* return auromaParserBase::BOOK_PART_NUMBER_CMD; */
\\(?i:tc)/{EOC}      return 1;/* return auromaParserBase::CHAPTER_TITLE_CMD; */
\\(?i:tcf)/{EOC}     return 1;/* return auromaParserBase::CHAPTER_TITLE_CMD; */
\\(?i:tcfup)/{EOC}   return 1;/* return auromaParserBase::CHAPTER_GROUP_TITLE_CMD; */
\\(?i:tcsub)/{EOC}   return 1;/* return auromaParserBase::CHAPTER_GROUP_SUBTITLE_CMD; */
\\(?i:tcn)/{EOC}     return 1;/* return auromaParserBase::CHAPTER_NUMBER_CMD; */
\\(?i:tscc)/{EOC}    return 1;/* return auromaParserBase::CHAPTER_TERMINATOR_CENTERED_CMD; */
\\(?i:par)/{EOC}     return auromaParserBase::PARA_CMD;
\\(?i:pf)/{EOC}      return 1;/* return auromaParserBase::NOINDENT_CMD; */
\\(?i:noindent)/{EOC} return 1;/* return auromaParserBase::NOINDENT_CMD; */
\\(?i:bf)/{EOC}      return 1;/* return auromaParserBase::NOINDENT_CMD;/\* not sure about this *\/ */
\\(?i:csf)/{EOC}     return 1;/* return auromaParserBase::CHAPTER_HEAD_QUOTE_CMD; */
\\(?i:sf)/{EOC}      return 1;/* return auromaParserBase::CHAPTER_HEAD_QUOTE_CMD; */
\\(?i:quote)/{EOC}   return 1;/* return auromaParserBase::QUOTE_CMD; */
\\(?i:sref)/{EOC}    return 1;/* return auromaParserBase::REFERENCE_CMD; */
\\(?i:pnote)/{EOC}   return 1;/* return auromaParserBase::FOOTNOTE_CMD; */
\\(?i:note)/{EOC}    return 1;/* return auromaParserBase::FOOTNOTE_CMD; */
\\(?i:lnote)/{EOC}   return 1;/* return auromaParserBase::FOOTNOTE_CMD; */
\\(?i:poem)/{EOC}    return 1;/* return auromaParserBase::POEM_CMD; */
\\(?i:prose)/{EOC}   return 1;/* return auromaParserBase::PROSE_CMD; */
\\(?i:sitem)/{EOC}   return 1;/* return auromaParserBase::ENUMERATION_ITEM_CMD; */
\\(?i:fnquad)/{EOC}  return 1;/* return auromaParserBase::FOOTNOTE_QUADSPACE_CMD; */
\\(?i:s)/{EOC}       return 1;/* return auromaParserBase::SLANT_CMD; */
\\(?i:sforced)/{EOC} return 1;/* return auromaParserBase::SLANT_CMD; */
\\(?i:ftext)/{EOC}   return 1;/* return auromaParserBase::FOOTER_CENTERED_TEXT_CMD; */
\\(?i:drop)/{EOC}    return 1;/* return auromaParserBase::DROP_CMD; */
\\(?i:nodrop)/{EOC}  return 1;/* return auromaParserBase::NODROP_CMD; */
\\(?i:ftextbi)/{EOC} return 1;/* return auromaParserBase::BOLD_ITALICS_FACE_CMD; */
\\(?i:ftextb)/{EOC}  return 1;/* return auromaParserBase::BOLD_FACE_CMD; */
\\(?i:it)/{EOC}      return 1;/* return auromaParserBase::ITALICS_FACE_CMD; */
\\(?i:nl)/{EOC}      return 1;/* return auromaParserBase::LINE_BREAK_CMD; */
\\(?i:dots)/{EOC}    return 1;/* return auromaParserBase::DOTS_CMD; */
\\(?i:sdots)/{EOC}   return 1;/* return auromaParserBase::DOTS_CMD; */
\\(?i:dotsns)/{EOC}  return 1;/* return auromaParserBase::DOTSNS_CMD; */
\\(?i:tstar)/{EOC}   return 1;/* return auromaParserBase::TSTAR_CMD; */
^Page/[[:blank:]](--|[[:digit:]]+) return 1;/* return auromaParserBase::PAGE_CMD; */

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
\{                                 return 1;/* return auromaParserBase::BEGIN_BLOCK; */
\}                                 return 1;/* return auromaParserBase::END_BLOCK; */

    /* Punctuations marks */
\-\-                            return 1;/* return auromaParserBase::N_DASH; */
\-\-\-|\x97                     return 1;/* return auromaParserBase::M_DASH; */
`                               return 1;/* return auromaParserBase::OPENING_SINGLE_QUOTE; */
\x93|``                         return 1;/* return auromaParserBase::OPENING_DOUBLE_QUOTES; */
\x94|''                         return 1;/* return auromaParserBase::CLOSING_DOUBLE_QUOTES; */
\'                              return 1;/* return auromaParserBase::SINGLE_QUOTE; */
\"                              return 1;/* return auromaParserBase::DOUBLE_QUOTES; */
\[                              return 1;/* return auromaParserBase::OPENING_SQUARE_BRACKET; */
\]                              return 1;/* return auromaParserBase::CLOSING_SQUARE_BRACKET; */
 /* The default rule for punctuation */
[[:punct:]]                     {
    d_val = YYText();
    return auromaParserBase::PUNCTUATION_MARK;
 }


    /* String */
(?x:
 /* The pattern for the first character of a string */
 ([[:alnum:]]           |
  \\[uU][[:xdigit:]]{4} |        /* allow for UTF-16 */
  /* Handle Diacritical marks */
  (\\=  |
   \\\. |
   \\\' |
   \\\" |
   \\^  |
   \\`  |
   \\~  |
   \\c  |
   \\,  |
   \\d  )[[:alpha:]]
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
   \\c  |
   \\,  |
   \\d  )[[:alpha:]]    |
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
    d_val = YYText();
    return auromaParserBase::STRING;
 }


    /* Line terminators */
\r                              /* ignore  */
\n                              {
    return auromaParserBase::NEWLINE;
 }


[[:blank:]]+                    /* ECHO;  */return auromaParserBase::WHITE_SPACE;

 /*
  * Default catch-all rules; error reporting
  */

 /* The unknown command! */
\\[[:alnum:]]+                  {
    cerr << "\033[01;31mline:"
         << yylineno << " Unknown Command:\033[00m'" << YYText() << "'"
         << endl;
    return 1; /* return auromaParserBase::UNKNOWN_COMMAND; */
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
