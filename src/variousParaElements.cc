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

#include <cassert>
#include "variousParaElements.h"

void
StringParaElement::emit(outputMode_t        mode,
                        unsigned            indentation,
                        bool               &parentStartedElements,
                        set<FontModifiers> &fontModifiers,
                        bool                firstElement
    ) const
{
    if (parentStartedElements == false) {
        spaces(indentation);
        if (fontModifiers.size()) {
            emitStartFontModifier(mode, fontModifiers);
        } else {
            if (mode == DOCBOOK) {
                cout << "<elements>";
            }
        }
        parentStartedElements = true;

        /* If we're starting out <elements>, we should also take care
         * of the space before the first element. */
        if (!firstElement && separatedFromPrevBySpace()) {
            cout << " ";
        }
    }

    cout << str;
}

void
FootnoteParaElement::emit(outputMode_t        mode,
                          unsigned            indentation,
                          bool               &parentStartedElements,
                          set<FontModifiers> &fontModifiers,
                          bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
        } else if (mode == WORDPRESS) {
            cout << endl;
        }
        parentStartedElements = false;
    }

    bool startedElements = false;
    if (mode == WORDPRESS) {
        unsigned int fn = getFootnoteNumber();

        spaces(indentation);
        cout << "<sup><a href=\"#"
             << getFootnoteHref() << "\" id=\"#"
             << getFootnoteHref() << "-fn" << fn << "\">"
             << fn << "</a></sup>"
             << endl;
    }
    block->emit(mode, indentation, startedElements, fontModifiers);

    incrementFootnoteNumber(); /* for the remaining footnotes in the
                                * current page. */
}

void
ReferenceParaElement::emit(outputMode_t        mode,
                           unsigned            indentation,
                           bool               &parentStartedElements,
                           set<FontModifiers> &fontModifiers,
                           bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
        } else if (mode == WORDPRESS) {
            cout << endl;
        }
        parentStartedElements = false;
    }
    bool startedElements = false;
    block->emit(mode, indentation, startedElements, fontModifiers);
}

void
ModifierParaElement::emit(outputMode_t        mode,
                          unsigned            indentation,
                          bool               &parentStartedElements,
                          set<FontModifiers> &fontModifiers,
                          bool                firstElement
    ) const
{
    set<FontModifiers> origFontModifiers(fontModifiers);
    pair<set<FontModifiers>::iterator, bool> ret;

    // add the modifier to the set
    switch (modifier) {
    case ParaElement::ITALICS:
        ret = fontModifiers.insert(ITALICS);
        break;
    case ParaElement::BOLD:
        ret = fontModifiers.insert(BOLD);
        break;
    case ParaElement::SMALL_CAPS:
        ret = fontModifiers.insert(SMALL_CAPS);
        break;
    default:
        assert(0);
    }

    if (ret.second == true) {
        // we have added a new element to the set of font-modifiers
        if (parentStartedElements) {
            if (mode == DOCBOOK) {
                // terminate an existing "elements"
                cout << "</elements>" << endl;

                // start a new one with updated fonts
                spaces(indentation);
                emitStartFontModifier(mode, fontModifiers);
            } else {
                /* terminate the existing font modifier blocks */
                emitEndFontModifier(mode, origFontModifiers);

                /* start html blocks for the new modifiers */
                emitStartFontModifier(mode, fontModifiers);
            }
        }
    }
}

void
DotsParaElement::emit(outputMode_t        mode,
                      unsigned            indentation,
                      bool               &parentStartedElements,
                      set<FontModifiers> &fontModifiers,
                      bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
            parentStartedElements = false;
        }
    }
    if (mode == DOCBOOK) {
        spaces(indentation);
        cout << "<element type=\"dots\">...</element>" << endl;
    } else {
        cout << "...";
    }
}

void
TstarParaElement::emit(outputMode_t        mode,
                       unsigned            indentation,
                       bool               &parentStartedElements,
                       set<FontModifiers> &fontModifiers,
                       bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
            parentStartedElements = false;
        }
    }
    if (mode == DOCBOOK) {
        spaces(indentation);
        cout << "<element type=\"tstar\">***</element>" << endl;
    } else {
        cout << "***";
    }
}

void
LineBreakParaElement::emit(outputMode_t        mode,
                           unsigned            indentation,
                           bool               &parentStartedElements,
                           set<FontModifiers> &fontModifiers,
                           bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
            parentStartedElements = false;
        }
    }
    if (mode == DOCBOOK) {
        spaces(indentation);
        cout << "<linebreak/>" << endl;
    } else {
        cout << "<br/>" << endl;
    }
}

void
PageBreakParaElement::emit(outputMode_t        mode,
                           unsigned            indentation,
                           bool               &parentStartedElements,
                           set<FontModifiers> &fontModifiers,
                           bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
            parentStartedElements = false;
        }
    }
    if (mode == DOCBOOK) {
        spaces(indentation);
        cout << "<pagebreak number=\"" << pageNumber << "\"/>" << endl;
    } else {
        cout << endl;
        spaces(indentation);
        cout << "<!--nextpage-->" << endl;
        spaces(indentation);
        resetFootnoteNumber();
    }
}

void
NDashParaElement::emit(outputMode_t        mode,
                       unsigned            indentation,
                       bool               &parentStartedElements,
                       set<FontModifiers> &fontModifiers,
                       bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
            parentStartedElements = false;
        }
    }

    if (mode == DOCBOOK) {
        spaces(indentation);
        if (fontModifiers.size()) {
            cout << "<element type=\"ndash\" font=\"";
            emitStartFontModifier(mode, fontModifiers);
            cout << "\">--</element>" << endl;
        } else {
            cout << "<element type=\"ndash\">--</element>" << endl;
        }
    } else {
        cout << "--";
    }
};

void
MDashParaElement::emit(outputMode_t        mode,
                       unsigned            indentation,
                       bool               &parentStartedElements,
                       set<FontModifiers> &fontModifiers,
                       bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
            parentStartedElements = false;
        }
    }

    if (mode == DOCBOOK) {
        spaces(indentation);
        if (fontModifiers.size()) {
            cout << "<element type=\"mdash\" font=\"";
            emitStartFontModifier(mode, fontModifiers);
            cout << "\">---</element>" << endl;
        } else {
            cout << "<element type=\"mdash\">---</element>" << endl;
        }
    } else {
        cout << "--";
    }
};

void
OpeningSingleQuoteParaElement::emit(outputMode_t        mode,
                                    unsigned            indentation,
                                    bool               &parentStartedElements,
                                    set<FontModifiers> &fontModifiers,
                                    bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
            parentStartedElements = false;
        }
    }

    if (mode == DOCBOOK) {
        spaces(indentation);
        if (fontModifiers.size()) {
            cout << "<element type=\"open_single_quote\" font=\"";
            emitStartFontModifier(mode, fontModifiers);
            cout << "\">`</element>" << endl;
        } else {
            cout << "<element type=\"open_single_quote\">`</element>" << endl;
        }
    } else {
        cout << "\'";
    }
}

void
OpeningDoubleQuotesParaElement::emit(outputMode_t        mode,
                                     unsigned            indentation,
                                     bool               &parentStartedElements,
                                     set<FontModifiers> &fontModifiers,
                                     bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
            parentStartedElements = false;
        }
    }

    if (mode == DOCBOOK) {
        spaces(indentation);
        if (fontModifiers.size()) {
            cout << "<element type=\"open_double_quotes\" font=\"";
            emitStartFontModifier(mode, fontModifiers);
            cout << "\">``</element>" << endl;
        } else {
            cout << "<element type=\"open_double_quotes\">``</element>" << endl;
        }
    } else {
        cout << "\"";
    }
}

void
ClosingDoubleQuotesParaElement::emit(outputMode_t        mode,
                                     unsigned            indentation,
                                     bool               &parentStartedElements,
                                     set<FontModifiers> &fontModifiers,
                                     bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == DOCBOOK) {
            cout << "</elements>" << endl;
            parentStartedElements = false;
        }
    }

    if (mode == DOCBOOK) {
        spaces(indentation);
        if (fontModifiers.size()) {
            cout << "<element type=\"close_double_quotes\" font=\"";
            emitStartFontModifier(mode, fontModifiers);
            cout << "\">''</element>" << endl;
        } else {
            cout << "<element type=\"close_double_quotes\">''</element>" << endl;
        }
    } else {
        cout << "\"";
    }
}
