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
%token QUOTE_CMD              /* Indented quotations. */
/* %token REFERENCE_CMD          /\* References for quotations. *\/ */
/* %token FOOTNOTE_CMD */
%token POEM_CMD                /* Enter poem mode. */
%token PROSE_CMD               /* return to default (prose) mode */
/* %token ENUMERATION_ITEM_CMD */
/* %token BOLD_ITALICS_FACE_CMD    /\* Bold and italics. *\/ */
/* %token BOLD_FACE_CMD */
/* %token ITALICS_FACE_CMD */
/* %token SLANT_CMD            /\* Slanted text. *\/ */
%token NOINDENT_CMD         /* Begin paragraph without indentation. */
%token FOOTER_CENTERED_TEXT_CMD /* Centered text at the footer of a page.*/
%token DROP_CMD            /* Enlarge the first letter which follows*/
%token NODROP_CMD
%token LINE_BREAK_CMD
%token DOTS_CMD              /* ... */
%token TSTAR_CMD             /* Triple star, centered. */
%token PAGE_CMD              /* Page break */
%token STRING
/* %token UNKNOWN_COMMAND */

%token PERIOD
%token N_DASH
%token M_DASH
%token OPENING_SINGLE_QUOTE
%token OPENING_DOUBLE_QUOTES
%token CLOSING_DOUBLE_QUOTES
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
        newPara();
    }
    stuffWithinParagraph
    {
        finishPara();
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
        currentContainer()->append($1);
    }
|
    PUNCTUATION_MARK
    {
        currentContainer()->append($1);
    }
|
    NOINDENT_CMD
    {
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->unsetAttribute(Para::INDENT);
    }
|
    QUOTE_CMD
    {
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->setAttribute(Para::QUOTE);
    }
|
    POEM_CMD
    {
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->setAttribute(Para::POEM);
    }
|
    PROSE_CMD
    {
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->unsetAttribute(Para::POEM);
    }
|
    FOOTER_CENTERED_TEXT_CMD
    {
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->setAttribute(Para::FOOTER);
        para->setAttribute(Para::CENTER);
    }
|
    DROP_CMD
    {
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->setAttribute(Para::DROP);
    }
|
    NODROP_CMD
    {
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->unsetAttribute(Para::DROP);
    }
|
    DOTS_CMD
    {
        currentContainer()->append(new DotsParaElement());
    }
|
    TSTAR_CMD
    {
        currentContainer()->append(new TstarParaElement());
    }
|
    LINE_BREAK_CMD
    {
        currentContainer()->append(new LineBreakParaElement());
    }
|
    PAGE_CMD
    WHITE_SPACE
    pageNumber
    {
        assert(currentContainerIsPara());
        currentContainer()->append(new PageBreakParaElement($3));
    }
|
    N_DASH
    {
        currentContainer()->append(new NDashParaElement());
    }
|
    M_DASH
    {
        currentContainer()->append(new MDashParaElement());
    }
|
    '.'
    {
        currentContainer()->append(new PeriodParaElement);
    }
|
    '['
    {
        currentContainer()->append("[");
    }
|
    ']'
    {
        currentContainer()->append("]");
    }
|
    '\''
    {
        currentContainer()->append("'");
    }
|
    '\"'
    {
        currentContainer()->append("\"");
    }
|
    OPENING_SINGLE_QUOTE
    {
        currentContainer()->append(new OpeningSingleQuoteParaElement());
    }
|
    OPENING_DOUBLE_QUOTES
    {
        currentContainer()->append(new OpeningDoubleQuotesParaElement());
    }
|
    CLOSING_DOUBLE_QUOTES
    {
        currentContainer()->append(new ClosingDoubleQuotesParaElement());
    }
;

pageNumber:
    STRING
|
    N_DASH
    {
        $$ = "--";
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
