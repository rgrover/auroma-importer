%parsefun-source parser.auroma.cc
%class-name auromaParser

%stype const char *

%expect 1                       /* expect one shift-reduce conflict :-) */

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
%token BOLD_ITALICS_FACE_CMD    /* Bold and italics. */
%token BOLD_FACE_CMD
%token ITALICS_FACE_CMD
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

%token N_DASH
%token M_DASH
%token OPENING_SINGLE_QUOTE
%token OPENING_DOUBLE_QUOTES
%token CLOSING_DOUBLE_QUOTES
%token PUNCTUATION_MARK

%token NEWLINE
%token BLANK_SPACE

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
    optionalBlankSpace
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
    optionalBlankSpace
    newline
|
    nonEmptyLineWithoutParCmd
;


nonEmptyLineWithoutParCmd :
    nonEmptyLineWithoutParCmdOrLineBreak
    optionalBlankSpace
    newline
;

nonEmptyLineWithoutParCmdOrLineBreak :
    paragraphElement
|
    blankSpace
    paragraphElement
|
    nonEmptyLineWithoutParCmdOrLineBreak
    optionalBlankSpace
    paragraphElement
;

block:
    optionalBlankSpace
    newline
|
    paragraphElement
|
    blankSpace
    paragraphElement
|
    block
    optionalBlankSpace
    newline
|
    block
    paragraphElement
|
    block
    blankSpace
    paragraphElement
;

paragraphElement:
    '{'
    {
        pushSubContainer();
    }
    block
    '}'
    {
        ParaElementContainer *block;

        block = currentContainer(); /* get a ref to the block's container */
        popSubContainer();          // pop the block out of the stack
        currentContainer()->append(block); // add the block as a paraElement
    }
|
    STRING
    {
        /* Pay attention to any blank space preceding the string */
        if (precedingWhiteSpace != NULL) {
            currentContainer()->append($1); /* Appended as a normal
                                             * string with space to
                                             * separate it from the
                                             * preceding element. */
        } else {
            currentContainer()->appendWithoutPrevSep($1);
        }
    }
|
    PUNCTUATION_MARK
    {
        /* Pay attention to any blank space preceding the punctuation mark */
        if (precedingWhiteSpace != NULL) {
            currentContainer()->append($1); /* Appended as a normal
                                             * string with space to
                                             * separate it from the
                                             * preceding element. */
        } else {
            currentContainer()->appendWithoutPrevSep($1);
        }
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
    blankSpace
    pageNumber
    {
        assert(currentContainerIsPara());
        currentContainer()->append(new PageBreakParaElement($3));
    }
|
    ITALICS_FACE_CMD
    {
        ModifierParaElement *mod =
            new ModifierParaElement(ParaElement::ITALICS);
        currentContainer()->append(mod);
    }
|
    BOLD_FACE_CMD
    {
        ModifierParaElement *mod =
            new ModifierParaElement(ParaElement::BOLD);
        currentContainer()->append(mod);
    }
|
    BOLD_ITALICS_FACE_CMD
    {
        ModifierParaElement *mod;

        mod = new ModifierParaElement(ParaElement::BOLD);
        currentContainer()->append(mod);

        mod = new ModifierParaElement(ParaElement::ITALICS);
        currentContainer()->append(mod);
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
    '['
    {
        currentContainer()->append("[");
    }
|
    ']'
    {
        currentContainer()->appendWithoutPrevSep("]");
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
    optionalBlankSpace
    newline
;

newline:
    NEWLINE
    {
        updatePrecedingWhiteSpace("\n");
    }
;

optionalBlankSpace :
    /* empty */
    {
        updatePrecedingWhiteSpace(NULL);
    }
|
    blankSpace
;

blankSpace:
    BLANK_SPACE
    {
        updatePrecedingWhiteSpace($1);
    }
;
