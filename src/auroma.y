%parsefun-source parser.auroma.cc
%class-name auromaParser

%stype const char *

%expect 1

/* %token BOOK_PART_TITLE_CMD      /\* For part titles. *\/ */
/* %token BOOK_PART_NUMBER_CMD     /\* For part numbers. *\/ */
/* %token CHAPTER_NUMBER_CMD       /\* e.g. Chapter IX *\/ */
/* %token CHAPTER_TITLE_CMD        /\* Chapter Headings. *\/ */
/* %token CHAPTER_GROUP_TITLE_CMD  /\* Title for a group of chapters. *\/ */
/* %token CHAPTER_GROUP_SUBTITLE_CMD /\* Title for chapter within a chap-group.*\/ */
/* %token CHAPTER_TERMINATOR_CENTERED_CMD /\* Centered text to end a chapter. *\/ */
%token PARA_CMD
/* %token CHAPTER_HEAD_QUOTE_CMD /\* Quotations following a chapter heading. *\/ */
/* %token QUOTE_CMD              /\* Indented quotations. *\/ */
/* %token REFERENCE_CMD          /\* References for quotations. *\/ */
/* %token FOOTNOTE_CMD */
/* %token FOOTNOTE_QUADSPACE_CMD  /\* 12pt. space in a footnote context *\/ */
/* %token POEM_CMD                /\* Enter poem mode. *\/ */
/* %token PROSE_CMD               /\* return to default (prose) mode *\/ */
/* %token ENUMERATION_ITEM_CMD */
/* %token BOLD_ITALICS_FACE_CMD    /\* Bold and italics. *\/ */
/* %token BOLD_FACE_CMD */
/* %token ITALICS_FACE_CMD */
/* %token SLANT_CMD            /\* Slanted text. *\/ */
/* %token NOINDENT_CMD         /\* Begin paragraph without indentation. *\/ */
/* %token FOOTER_CENTERED_TEXT_CMD /\* Centered text at the footer of a page.*\/ */
/* %token DROP_CMD            /\* Enlarge the first letter which follows*\/ */
/* %token NODROP_CMD */
/* %token LINE_BREAK_CMD */
/* %token DOTS_CMD              /\* ... *\/ */
/* %token DOTSNS_CMD            /\* Dots without a space following them *\/ */
/* %token TSTAR_CMD             /\* Triple star, centered. *\/ */
/* %token PAGE_CMD              /\* Page break *\/ */
/* %token UNKNOWN_COMMAND */
/* %token BEGIN_BLOCK */
/* %token END_BLOCK */
%token STRING

/* %token N_DASH */
/* %token M_DASH */
/* %token SINGLE_QUOTE */
/* %token DOUBLE_QUOTES */
/* %token OPENING_SINGLE_QUOTE */
/* %token OPENING_DOUBLE_QUOTES */
/* %token CLOSING_DOUBLE_QUOTES */
/* %token OPENING_SQUARE_BRACKET */
/* %token CLOSING_SQUARE_BRACKET */
%token PUNCTUATION_MARK

%token NEWLINE
%token WHITE_SPACE

%%

input :
    /* empty */
|
    input
    paragraph
|
    input
    emptyLine
;

paragraph :
    optionalWhiteSpace
    PARA_CMD
    {
        currentPara = new Para();
    }
    stuffWithinParagraph
    {
        currentPara->display();
    }
;

stuffWithinParagraph :
    firstLineOfAParagraph
|
    stuffWithinParagraph
    nonEmptyLineWithoutParCmd
;

firstLineOfAParagraph :
    optionalWhiteSpace
    NEWLINE
|
    nonEmptyLineWithoutParCmd
;


nonEmptyLineWithoutParCmd :
    nonEmptyLineWithoutParCmdOrLineBreak
    optionalWhiteSpace
    NEWLINE
;

nonEmptyLineWithoutParCmdOrLineBreak :
    optionalWhiteSpace
    paragraphElement
|
    nonEmptyLineWithoutParCmdOrLineBreak
    optionalWhiteSpace
    paragraphElement
;

paragraphElement:
    STRING
    {
        currentPara->append($1);
    }
|
    PUNCTUATION_MARK
    {
        currentPara->append($1);
    }
;

emptyLine :
    optionalWhiteSpace
    NEWLINE
;

optionalWhiteSpace :
    /* empty */
|
    WHITE_SPACE
;
