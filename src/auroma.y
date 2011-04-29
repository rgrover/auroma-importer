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
 * - Neither Aurokruti nor the names of its contributors may be used
 *   to endorse or promote products derived from this software without
 *   specific prior written permission.
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

%parsefun-source parser.auroma.cc
%class-name auromaParser

%stype string

%expect 3                 /*
                           * Expect two shift-reduce conflicts:
                           *   - one for white spaces within paragraphs.
                           *   - another for commands which take
                           *     optinal blocks, e.g. \sitem
                           *   - another for \it (or \s) which can take
                           *     an optional block
                           */

%token SET_CMD
%token PREFACE_CMD
%token BOOK_CMD
%token PART_CMD
%token CHAPTER_CMD
%token SECTION_CMD
%token SECTION1_CMD
%token SECTION2_CMD
%token SECTION3_CMD
%token TITLE_CMD
%token AUTHOR_CMD

%token PARA_CMD
%token HEADING_NUMBER_CMD       /* e.g. Chapter IX */
%token HEADING_TITLE_CMD        /* e.g. Chapter Headings. */
%token CHAPTER_HEAD_QUOTE_CMD   /* Quotations following a chapter heading. */
%token BLOCK_QUOTE_CMD          /* Indented quotations. */
%token REFERENCE_CMD            /* References for quotations. */
%token FOOTNOTE_CMD
%token POEM_CMD                 /* Enter poem mode. */
%token PROSE_CMD                /* return to default (prose) mode */
%token ENUMERATION_ITEM_CMD
%token BOLD_ITALICS_FACE_CMD    /* Bold and italics. */
%token BOLD_FACE_CMD
%token ITALICS_FACE_CMD
%token NOINDENT_CMD             /* Begin paragraph without indentation. */
%token FOOTER_CENTERED_TEXT_CMD /* Centered text at the footer of a page.*/
%token DROP_CMD                 /* Enlarge the first letter which follows*/
%token NODROP_CMD
%token CENTER_CMD
%token LINE_BREAK_CMD
%token DOTS_CMD                 /* ... */
%token TSTAR_CMD                /* Triple star, centered. */
%token PAGE_CMD                 /* Page break */
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
|
    input
    paragraphContainerDirective
;

paragraph :
    optionalBlankSpaces
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
    possiblyEmptyParaLine
|
    stuffWithinParagraph
    nonEmptyLineWithoutParCmd
;

possiblyEmptyParaLine :
    optionalBlankSpaces
    newline
|
    nonEmptyLineWithoutParCmd
;


nonEmptyLineWithoutParCmd :
    nonEmptyLineWithoutParCmdOrLineBreak
    optionalBlankSpaces
    newline
;

nonEmptyLineWithoutParCmdOrLineBreak :
    paragraphElement
|
    blankSpaces
    paragraphElement
    {
        updatePrecedingWhiteSpace(NULL); // reset blank-space for the
                                         // following paraElement.
    }
|
    nonEmptyLineWithoutParCmdOrLineBreak
    optionalBlankSpaces
    paragraphElement
    {
        updatePrecedingWhiteSpace(NULL); // reset blank-space for the
                                         // following paraElement.
    }
;

block:
    /* empty */
|
    block
    newline
|
    block
    blankSpace
|
    block
    blockElement
    {
        updatePrecedingWhiteSpace(NULL); // reset blank-space for the
                                         // following blockElement.
    }
;

paragraphElement :
    blockElement
|
    paraAttributeCommand
;

paraAttributeCommand :
    HEADING_NUMBER_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->setAttribute(Para::HEADING_NUMBER);
    }
|
    HEADING_TITLE_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->setAttribute(Para::HEADING_TITLE);
    }
|
    NOINDENT_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->unsetAttribute(Para::INDENT);
    }
|
    BLOCK_QUOTE_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->setAttribute(Para::BLOCK_QUOTE);
    }
|
    POEM_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->setAttribute(Para::POEM);
    }
|
    PROSE_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->unsetAttribute(Para::POEM);
    }
|
    FOOTER_CENTERED_TEXT_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->setAttribute(Para::FOOTER);
        para->setAttribute(Para::CENTER);
    }
|
    DROP_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->setAttribute(Para::DROP);
    }
|
    NODROP_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->unsetAttribute(Para::DROP);
    }
|
    CENTER_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->setAttribute(Para::CENTER);
    }
|
    enumeration
|
    CHAPTER_HEAD_QUOTE_CMD
    {
        assert(currentElementContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->setAttribute(Para::HEAD_QUOTE);
    }
;

enumeration:
    ENUMERATION_ITEM_CMD
    optionalEnumerationBlock
;

optionalEnumerationBlock:
/* empty */
    {
        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        para->setAttribute(Para::ENUMERATION);
    }
|
    '{'
    {
        pushElementSubContainer("enumeration");
    }
    block
    '}'
    {
        ParaElementContainer *block;
        block = currentElementContainer(); /* get a ref to the block's container */
        popElementSubContainer();          // pop the block out of the stack

        Para *para = reinterpret_cast<Para *>(currentElementContainer());
        if (!para->setEnumerationBlock(block)) {
            std::cerr << "\033[01;31mpaser: line "
                      << lexer->lineno() << ":\033[00m "
                      << "attempting to define multiple enumerations "
                      << "for the same paragraph"<< endl;
        }
    }
;

blockElement:
    '{'
    {
        pushElementSubContainer();
    }
    block
    '}'
    {
        ParaElementContainer *block;

        block = currentElementContainer(); /* get a ref to the block's container */
        popElementSubContainer();          // pop the block out of the stack
        currentElementContainer()->append(block); // add the block as a paraElement
    }
|
    STRING
    {
        /* Pay attention to any blank space preceding the string */
        if (precedingWhiteSpace != NULL) {
            currentElementContainer()->append($1); /* Appended as a normal
                                             * string with space to
                                             * separate it from the
                                             * preceding element. */
        } else {
            currentElementContainer()->appendWithoutPrevSep($1);
        }
    }
|
    FOOTNOTE_CMD
    optionalBlankSpaces
    '{'
    {
        pushElementSubContainer("footnote");
    }
    block
    '}'
    {
        ParaElementContainer *block;
        block = currentElementContainer(); /* get a ref to the block's container */
        popElementSubContainer();          // pop the block out of the stack

        FootnoteParaElement *fn;
        fn = new FootnoteParaElement(block);
        currentElementContainer()->append(fn); // add the footnote as a paraElement
    }
|
    REFERENCE_CMD
    optionalBlankSpaces
    '{'
    {
        pushElementSubContainer("reference");
    }
    block
    '}'
    {
        ParaElementContainer *block;
        block = currentElementContainer(); /* get a ref to the block's container */
        popElementSubContainer();          // pop the block out of the stack

        ReferenceParaElement *ref;
        ref = new ReferenceParaElement(block);
        currentElementContainer()->append(ref); // add the reference as a paraElement
    }
|
    PUNCTUATION_MARK
    {
        /* Pay attention to any blank space preceding the punctuation mark */
        if (precedingWhiteSpace != NULL) {
            currentElementContainer()->append($1); /* Appended as a normal
                                             * string with space to
                                             * separate it from the
                                             * preceding element. */
        } else {
            currentElementContainer()->appendWithoutPrevSep($1);
        }
    }

|
    DOTS_CMD
    {
        currentElementContainer()->append(new DotsParaElement());
    }
|
    TSTAR_CMD
    {
        currentElementContainer()->append(new TstarParaElement());
    }
|
    LINE_BREAK_CMD
    {
        currentElementContainer()->append(new LineBreakParaElement());
    }
|
    PAGE_CMD
    blankSpace
    pageNumber
    {
        assert(currentElementContainerIsPara());
        currentElementContainer()->append(new PageBreakParaElement($3));
    }
|
    ITALICS_FACE_CMD
    {
        ModifierParaElement *mod =
            new ModifierParaElement(ParaElement::ITALICS);
        currentElementContainer()->append(mod);
    }
|
    ITALICS_FACE_CMD
    '{'
    {
        pushElementSubContainer();
        ModifierParaElement *mod =
            new ModifierParaElement(ParaElement::ITALICS);
        currentElementContainer()->append(mod);
    }
    block
    '}'
    {
        ParaElementContainer *block;
        block = currentElementContainer(); /* get a ref to the block's container */
        popElementSubContainer();          // pop the block out of the stack

        currentElementContainer()->append(block); // add the block as a paraElement
    }
|
    BOLD_FACE_CMD
    {
        ModifierParaElement *mod =
            new ModifierParaElement(ParaElement::BOLD);
        currentElementContainer()->append(mod);
    }
|
    BOLD_ITALICS_FACE_CMD
    {
        ModifierParaElement *mod;

        mod = new ModifierParaElement(ParaElement::BOLD);
        currentElementContainer()->append(mod);

        mod = new ModifierParaElement(ParaElement::ITALICS);
        currentElementContainer()->append(mod);
    }
|
    N_DASH
    {
        currentElementContainer()->append(new NDashParaElement());
    }
|
    M_DASH
    {
        currentElementContainer()->append(new MDashParaElement());
    }
|
    '['
    {
        currentElementContainer()->append("[");
    }
|
    ']'
    {
        currentElementContainer()->appendWithoutPrevSep("]");
    }
|
    OPENING_SINGLE_QUOTE
    {
        OpeningSingleQuoteParaElement *quote;
        quote = new OpeningSingleQuoteParaElement();
        if (!precedingWhiteSpace) {
            quote->unsetPrevSep();
        }
        currentElementContainer()->append(quote);
    }
|
    OPENING_DOUBLE_QUOTES
    {
        OpeningDoubleQuotesParaElement *quotes;
        quotes = new OpeningDoubleQuotesParaElement();
        if (!precedingWhiteSpace) {
            quotes->unsetPrevSep();
        }

        currentElementContainer()->append(quotes);
    }
|
    CLOSING_DOUBLE_QUOTES
    {
        currentElementContainer()->append(new ClosingDoubleQuotesParaElement());
    }
;

strings:
    STRING
    {
        $$ = $1;
    }
|
    strings
    optionalBlankSpaces
    STRING
    {
        $$ = $$ + " " + $3;
    }
;

/* pushContainerLevel : */
/*     optionalBlankSpaces */
/*     PUSH_CMD */
/*     optionalBlankSpaces */
/*     newline */
/*     { */
/*         Para::pushContainerLevel(); */
/*     } */
/* ; */

/* popContainerLevel : */
/*     optionalBlankSpaces */
/*     POP_CMD */
/*     optionalBlankSpaces */
/*     newline */
/*     { */
/*         Para::popContainerLevel(); */
/*     } */
/* ; */

paragraphContainerDirective:
    optionalBlankSpaces
    SET_CMD
    optionalBlankSpaces
    newline
    {
        ContainerDirective *set = new Set();
        newDirective(set);
    }
|
    optionalBlankSpaces
    BOOK_CMD
    optionalBlankSpaces
    newline
    {
        ContainerDirective *book = new Book();
        newDirective(book);
    }
|
    optionalBlankSpaces
    PART_CMD
    optionalBlankSpaces
    newline
    {
        ContainerDirective *part = new Part();
        newDirective(part);
    }
|
    optionalBlankSpaces
    PREFACE_CMD
    optionalBlankSpaces
    newline
    {
        ContainerDirective *preface = new Preface();
        newDirective(preface);
    }
|
    optionalBlankSpaces
    CHAPTER_CMD
    optionalBlankSpaces
    newline
    {
        ContainerDirective *chapter = new Chapter();
        newDirective(chapter);
    }
|
    optionalBlankSpaces
    SECTION_CMD
    optionalBlankSpaces
    newline
    {
        ContainerDirective *section = new Section();
        newDirective(section);
    }
|
    optionalBlankSpaces
    SECTION1_CMD
    optionalBlankSpaces
    newline
    {
        ContainerDirective *section1 = new Section1();
        newDirective(section1);
    }
|
    optionalBlankSpaces
    SECTION2_CMD
    optionalBlankSpaces
    newline
    {
        ContainerDirective *section2 = new Section2();
        newDirective(section2);
    }
|
    optionalBlankSpaces
    SECTION3_CMD
    optionalBlankSpaces
    newline
    {
        ContainerDirective *section3 = new Section3();
        newDirective(section3);
    }
|
    optionalBlankSpaces
    AUTHOR_CMD
    optionalBlankSpaces
    strings
    optionalBlankSpaces
    newline
    {
        assert(pods.back()->isDirective());

        ContainerDirective *directive =
            reinterpret_cast<ContainerDirective *>(pods.back());
        directive->setAuthor($4);
    }
|
    optionalBlankSpaces
    TITLE_CMD
    optionalBlankSpaces
    strings
    optionalBlankSpaces
    newline
    {
        assert(pods.back()->isDirective());

        ContainerDirective *directive =
            reinterpret_cast<ContainerDirective *>(pods.back());
        directive->setTitle($4);
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
    optionalBlankSpaces
    newline
;

newline:
    NEWLINE
    {
        updatePrecedingWhiteSpace("\n");
    }
;

optionalBlankSpaces :
    /* empty */
    {
        updatePrecedingWhiteSpace(NULL);
    }
|
    blankSpaces
;

blankSpaces:
    BLANK_SPACE
    {
        updatePrecedingWhiteSpace($1.c_str());
    }
|
    blankSpaces
    BLANK_SPACE
    {
        updatePrecedingWhiteSpace($2.c_str());
    }
;

blankSpace:
    BLANK_SPACE
    {
        updatePrecedingWhiteSpace($1.c_str());
    }
;
