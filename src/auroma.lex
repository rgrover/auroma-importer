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

 /* Options */
%option prefix="auroma"

%option c++
%option yylineno
%option noyywrap

 /* Start condition needed to scan metadata. */
%x AT_HEAD
%x PAGE_BREAK

 /* Definitions */
EOC                  [[:blank:][:punct:]]              /* command terminator */

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
\\(?i:set)$          return auromaParserBase::SET_CMD;
\\(?i:set)/{EOC}     return auromaParserBase::SET_CMD;
\\(?i:book)$         return auromaParserBase::BOOK_CMD;
\\(?i:book)/{EOC}    return auromaParserBase::BOOK_CMD;
\\(?i:preface)$      return auromaParserBase::PREFACE_CMD;
\\(?i:preface)/{EOC} return auromaParserBase::PREFACE_CMD;
\\(?i:part)$         return auromaParserBase::PART_CMD;
\\(?i:part)/{EOC}    return auromaParserBase::PART_CMD;
\\(?i:chapter)$      return auromaParserBase::CHAPTER_CMD;
\\(?i:chapter)/{EOC} return auromaParserBase::CHAPTER_CMD;
\\(?i:section)$      return auromaParserBase::SECTION_CMD;
\\(?i:section)/{EOC} return auromaParserBase::SECTION_CMD;
\\(?i:sect1)$        return auromaParserBase::SECTION1_CMD;
\\(?i:sect1)/{EOC}   return auromaParserBase::SECTION1_CMD;
\\(?i:sect2)$        return auromaParserBase::SECTION2_CMD;
\\(?i:sect2)/{EOC}   return auromaParserBase::SECTION2_CMD;
\\(?i:sect3)$        return auromaParserBase::SECTION3_CMD;
\\(?i:sect3)/{EOC}   return auromaParserBase::SECTION3_CMD;
\\(?i:sect4)$        return auromaParserBase::SECTION4_CMD;
\\(?i:sect4)/{EOC}   return auromaParserBase::SECTION4_CMD;
\\(?i:title)$        return auromaParserBase::TITLE_CMD;
\\(?i:title)/{EOC}   return auromaParserBase::TITLE_CMD;
\\(?i:author)$       return auromaParserBase::AUTHOR_CMD;
\\(?i:author)/{EOC}  return auromaParserBase::AUTHOR_CMD;

\\(?i:par)$          return auromaParserBase::PARA_CMD;
\\(?i:par)/{EOC}     return auromaParserBase::PARA_CMD;
\\(?i:spar)$         return auromaParserBase::PARA_CMD;
\\(?i:spar)/{EOC}    return auromaParserBase::PARA_CMD;
\\(?i:sparn)$        return auromaParserBase::PARA_CMD;
\\(?i:sparn)/{EOC}   return auromaParserBase::PARA_CMD;

\\(?i:hn)$           return auromaParserBase::HEADING_NUMBER_CMD;
\\(?i:hn)/{EOC}      return auromaParserBase::HEADING_NUMBER_CMD;
\\(?i:ht)$           return auromaParserBase::HEADING_TITLE_CMD;
\\(?i:ht)/{EOC}      return auromaParserBase::HEADING_TITLE_CMD;

\\(?i:sref)$         return auromaParserBase::REFERENCE_CMD;
\\(?i:sref)/{EOC}    return auromaParserBase::REFERENCE_CMD;
\\(?i:sitem)$        return auromaParserBase::ENUMERATION_ITEM_CMD;
\\(?i:sitem)/{EOC}   return auromaParserBase::ENUMERATION_ITEM_CMD;

\\(?i:pnote)$        return auromaParserBase::FOOTNOTE_CMD;
\\(?i:pnote)/{EOC}   return auromaParserBase::FOOTNOTE_CMD;
\\(?i:note)$         return auromaParserBase::FOOTNOTE_CMD;
\\(?i:note)/{EOC}    return auromaParserBase::FOOTNOTE_CMD;
\\(?i:lnote)$        return auromaParserBase::FOOTNOTE_CMD;
\\(?i:lnote)/{EOC}   return auromaParserBase::FOOTNOTE_CMD;
\\(?i:xnote)$        return auromaParserBase::FOOTNOTE_CMD;
\\(?i:xnote)/{EOC}   return auromaParserBase::FOOTNOTE_CMD;

\\(?i:csf)$          return auromaParserBase::CHAPTER_HEAD_QUOTE_CMD;
\\(?i:csf)/{EOC}     return auromaParserBase::CHAPTER_HEAD_QUOTE_CMD;
\\(?i:sf)$           return auromaParserBase::BLOCK_QUOTE_CMD;
\\(?i:sf)/{EOC}      return auromaParserBase::BLOCK_QUOTE_CMD;
\\(?i:quote)$        return auromaParserBase::BLOCK_QUOTE_CMD;
\\(?i:quote)/{EOC}   return auromaParserBase::BLOCK_QUOTE_CMD;
\\(?i:pf)$           return auromaParserBase::NOINDENT_CMD;
\\(?i:pf)/{EOC}      return auromaParserBase::NOINDENT_CMD;
\\(?i:noindent)$     return auromaParserBase::NOINDENT_CMD;
\\(?i:noindent)/{EOC} return auromaParserBase::NOINDENT_CMD;
\\(?i:bf)$           return auromaParserBase::NOINDENT_CMD;
\\(?i:bf)/{EOC}      return auromaParserBase::NOINDENT_CMD;
\\(?i:poem)$         return auromaParserBase::POEM_CMD;
\\(?i:poem)/{EOC}    return auromaParserBase::POEM_CMD;
\\(?i:prose)$        return auromaParserBase::PROSE_CMD;
\\(?i:prose)/{EOC}   return auromaParserBase::PROSE_CMD;
\\(?i:ftext)$        return auromaParserBase::FOOTER_CENTERED_TEXT_CMD;
\\(?i:ftext)/{EOC}   return auromaParserBase::FOOTER_CENTERED_TEXT_CMD;
\\(?i:drop)$         return auromaParserBase::DROP_CMD;
\\(?i:drop)/{EOC}    return auromaParserBase::DROP_CMD;
\\(?i:nodrop)$       return auromaParserBase::NODROP_CMD;
\\(?i:nodrop)/{EOC}  return auromaParserBase::NODROP_CMD;
\\(?i:center)$       return auromaParserBase::CENTER_CMD;
\\(?i:center)/{EOC}  return auromaParserBase::CENTER_CMD;

\\(?i:s)$            return auromaParserBase::ITALICS_FACE_CMD;
\\(?i:s)/{EOC}       return auromaParserBase::ITALICS_FACE_CMD;
\\(?i:sforced)$      return auromaParserBase::ITALICS_FACE_CMD;
\\(?i:sforced)/{EOC} return auromaParserBase::ITALICS_FACE_CMD;
\\(?i:ftextbi)$      return auromaParserBase::BOLD_ITALICS_FACE_CMD;
\\(?i:ftextbi)/{EOC} return auromaParserBase::BOLD_ITALICS_FACE_CMD;
\\(?i:ftextb)$       return auromaParserBase::BOLD_FACE_CMD;
\\(?i:ftextb)/{EOC}  return auromaParserBase::BOLD_FACE_CMD;
\\(?i:it)$           return auromaParserBase::ITALICS_FACE_CMD;
\\(?i:it)/{EOC}      return auromaParserBase::ITALICS_FACE_CMD;

\\(?i:dots)$         return auromaParserBase::DOTS_CMD;
\\(?i:dots)/{EOC}    return auromaParserBase::DOTS_CMD;
\\(?i:sdots)$        return auromaParserBase::DOTS_CMD;
\\(?i:sdots)/{EOC}   return auromaParserBase::DOTS_CMD;
\\(?i:dotsns)$       return auromaParserBase::DOTS_CMD;
\\(?i:dotsns)/{EOC}  return auromaParserBase::DOTS_CMD;
\\(?i:tstar)$        return auromaParserBase::TSTAR_CMD;
\\(?i:tstar)/{EOC}   return auromaParserBase::TSTAR_CMD;

\\(?i:nl)$           return auromaParserBase::LINE_BREAK_CMD;
\\(?i:nl)/{EOC}      return auromaParserBase::LINE_BREAK_CMD;
^Page/[[:blank:]](--|[[:digit:]]+) {
    BEGIN(PAGE_BREAK);
    return auromaParserBase::PAGE_CMD;
 }
<PAGE_BREAK>\n+                              {
    BEGIN(INITIAL);
    return auromaParserBase::NEWLINE;
 }

\\(?i:BC)$                     /* ignore */
\\(?i:BC)[[:blank:]]*          /* ignore */
\\(?i:bl)$                     /* ignore */
\\(?i:bl)[[:blank:]]*          /* ignore */
\\(?i:bi)$                     /* ignore */
\\(?i:bi)[[:blank:]]*          /* ignore */
\\(?i:bigskip)$                /* ignore */
\\(?i:bigskip)/{EOC}           /* ignore */
\\(?i:dropquote)$              /* ignore */
\\(?i:dropquote)/{EOC}         /* ignore */
\\(?i:emptypage)$              /* ignore */
\\(?i:emptypage)/{EOC}         /* ignore */
\\(?i:fnquad)$                 /* ignore */
\\(?i:fnquad)[[:blank:]]*      /* ignore */
\\(?i:fsc)$                    /* ignore */
\\(?i:fsc)/{EOC}               /* ignore */
\\(?i:fsqend)$                 /* ignore */
\\(?i:fsqend)/{EOC}            /* ignore */
\\(?i:fsqstart)$               /* ignore */
\\(?i:fsqstart)/{EOC}          /* ignore */
\\(?i:hbox)$                   /* ignore */
\\(?i:hbox)[[:blank:]]*        /* ignore */
\\(?i:lnotes)$                 /* ignore */
\\(?i:lnotes)/{EOC}            /* ignore */
\\(?i:medskip)$                /* ignore */
\\(?i:medskip)/{EOC}           /* ignore */
\\(?i:nh)$                     /* ignore */
\\(?i:nh)[[:blank:]]*          /* ignore */
\\(?i:oquad)$                  /* ignore */
\\(?i:oquad)/{EOC}             /* ignore */
\\(?i:phantom)$                /* ignore */
\\(?i:phantom)/{EOC}           /* ignore */
\\(?i:pi)$                     /* ignore */
\\(?i:pi)/{EOC}                /* ignore */
\\(?i:pnotes)$                 /* ignore */
\\(?i:pnotes)/{EOC}            /* ignore */
\\(?i:qquad)$                  /* ignore */
\\(?i:qquad)/{EOC}             /* ignore */
\\(?i:quad)$                   /* ignore */
\\(?i:quad)/{EOC}              /* ignore */
\\(?i:relax)$                  /* ignore */
\\(?i:relax)/{EOC}             /* ignore */
\\(?i:rl)$                     /* ignore */
\\(?i:rl)[[:blank:]]*          /* ignore */
\\(?i:sbigcap)$                /* ignore */
\\(?i:sbigcap)[[:blank:]]*     /* ignore */
\\(?i:shortlines)$             /* ignore; but needs to be addressed */
\\(?i:shortlines)/{EOC}        /* ignore; but needs to be addressed */
\\(?i:si)$                     /* ignore */
\\(?i:si)[[:blank:]]*          /* ignore */
\\(?i:text)$                   /* ignore */
\\(?i:text)[[:blank:]]*        /* ignore */
\\(?i:thinspace)$              /* ignore */
\\(?i:thinspace)[[:blank:]]*   /* ignore */
\\[[:digit:]]$                 /* ignore; but needs to be addressed */
\\[[:digit:]]/{EOC}            /* ignore; but needs to be addressed */

    /* Punctuations marks */
\[                              return '[';
\]                              return ']';
\{                              return '{';
\}                              return '}';
<*>\-\-|\x96                    return auromaParserBase::N_DASH;
\-\-\-|\x97                     return auromaParserBase::M_DASH;
`                               return auromaParserBase::OPENING_SINGLE_QUOTE;
\x93|``                         return auromaParserBase::OPENING_DOUBLE_QUOTES;
\x94|\'\'                       return auromaParserBase::CLOSING_DOUBLE_QUOTES;
 /* The default rule for punctuation */
[[:punct:]]                     {
    d_val = YYText();
    return auromaParserBase::PUNCTUATION_MARK;
 }

\.\.\.                    {
    cerr << "\033[01;31mscanner: line " << yylineno
         << ": found occurrence of '...', "
         << "please replace with \\dots\033[00m" << endl;
 }
[[:blank:]]*\*[[:blank:]]*\*[[:blank:]]*\* {
    cerr << "\033[01;31mscanner: line " << yylineno
         << ": found occurrence of triple-star, "
         << "please replace with \\tstar\033[00m" << endl;
 }

    /* String */
<*>(?x:
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
   \\d  )\{[[:alpha:]]\}|
  (\\=  |
   \\\. |
   \\,  |
   \\\' |
   \\\" |
   \\^  |
   \\`  |
   \\~  |
   \\,  )[[:alpha:]]
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
   \\d  )\{[[:alpha:]]\}|
  (\\=  |
   \\\. |
   \\,  |
   \\\' |
   \\\" |
   \\^  |
   \\`  |
   \\~  |
   \\,  )[[:alpha:]]    |
  \'[[:alpha:]]         |
  (\- | \x96)[[:alpha:]]|       /* allow hyphens */
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


<*>[[:blank:]]+                 {
    /* ECHO;  */
    d_val = YYText();
    return auromaParserBase::BLANK_SPACE;
 }

 /*
  * Default catch-all rules; error reporting
  */

 /* The unknown command! */
\\[[:alnum:]]+                  {
    cerr << "\033[01;31mscanner: line "
         << yylineno << ": Unknown Command:\033[00m'" << YYText() << "'"
         << endl;
    return 1; /* return auromaParserBase::UNKNOWN_COMMAND; */
 }

 /* for unsupported diacritical combinations */
\\[^[:alnum:][:blank:]][[:alpha:]] {
    cerr << "\033[01;31mscanner: line " << yylineno
         << ": unknown diacritical mark: \033[00m'" << YYText() << "'" << endl;
 }

 /* For unknown byte--this is the default match. */
.                               {
    cerr << "\033[01;31mscanner: line " << yylineno
         << ": unexpected byte: \033[00m'" << YYText() << "'" << endl;
 }

%%
