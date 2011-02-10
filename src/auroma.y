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

%stype const char *

%expect 2                 /*
                           * Expect two shift-reduce conflicts:
                           *   - one for white spaces within paragraphs.
                           *   - another for commands which take
                           *     optinal blocks, e.g. \sitem
                           */

%token HEADING_NUMBER_CMD       /* e.g. Chapter IX */
%token HEADING_TITLE_CMD        /* e.g. Chapter Headings. */
%token PARA_CMD
%token CHAPTER_HEAD_QUOTE_CMD   /* Quotations following a chapter heading. */
%token QUOTE_CMD                /* Indented quotations. */
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
    possiblyEmptyParaLine
|
    stuffWithinParagraph
    nonEmptyLineWithoutParCmd
;

possiblyEmptyParaLine :
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
    {
        updatePrecedingWhiteSpace(NULL); // reset blank-space for the
                                         // following paraElement.
    }
|
    nonEmptyLineWithoutParCmdOrLineBreak
    optionalBlankSpace
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
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->setAttribute(Para::HEADING_NUMBER);
    }
|
    HEADING_TITLE_CMD
    {
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->setAttribute(Para::HEADING_TITLE);
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
    enumeration
|
    CHAPTER_HEAD_QUOTE_CMD
    {
        assert(currentContainerIsPara());

        Para *para = reinterpret_cast<Para *>(currentContainer());
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
        Para *para = reinterpret_cast<Para *>(currentContainer());
        para->setAttribute(Para::ENUMERATION);
    }
|
    '{'
    {
        pushSubContainer("enumeration");
    }
    block
    '}'
    {
        ParaElementContainer *block;
        block = currentContainer(); /* get a ref to the block's container */
        popSubContainer();          // pop the block out of the stack

        Para *para = reinterpret_cast<Para *>(currentContainer());
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
    FOOTNOTE_CMD
    optionalBlankSpace
    '{'
    {
        pushSubContainer("footnote");
    }
    block
    '}'
    {
        ParaElementContainer *block;
        block = currentContainer(); /* get a ref to the block's container */
        popSubContainer();          // pop the block out of the stack

        FootnoteParaElement *fn;
        fn = new FootnoteParaElement(block);
        currentContainer()->append(fn); // add the footnote as a paraElement
    }
|
    REFERENCE_CMD
    optionalBlankSpace
    '{'
    {
        pushSubContainer("reference");
    }
    block
    '}'
    {
        ParaElementContainer *block;
        block = currentContainer(); /* get a ref to the block's container */
        popSubContainer();          // pop the block out of the stack

        ReferenceParaElement *ref;
        ref = new ReferenceParaElement(block);
        currentContainer()->append(ref); // add the reference as a paraElement
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
        OpeningSingleQuoteParaElement *quote;
        quote = new OpeningSingleQuoteParaElement();
        if (!precedingWhiteSpace) {
            quote->unsetPrevSep();
        }
        currentContainer()->append(quote);
    }
|
    OPENING_DOUBLE_QUOTES
    {
        OpeningDoubleQuotesParaElement *quotes;
        quotes = new OpeningDoubleQuotesParaElement();
        if (!precedingWhiteSpace) {
            quotes->unsetPrevSep();
        }

        currentContainer()->append(quotes);
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
