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
StringParaElement::emitXML(unsigned            indentation,
                           bool               &parentStartedElements,
                           set<FontModifiers> &fontModifiers,
                           bool                firstElement
    ) const
{
    if (parentStartedElements == false) {
        spaces(indentation);
        if (fontModifiers.size()) {
            cout << "<elements font=\"";
            emitFontModifierString(fontModifiers);
            cout << "\">";
        } else {
            cout << "<elements>";
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
FootnoteParaElement::emitXML(unsigned            indentation,
                             bool               &parentStartedElements,
                             set<FontModifiers> &fontModifiers,
                             bool                firstElement
    ) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    bool startedElements = false;
    block->emitXML(indentation, startedElements, fontModifiers);
}

void
ReferenceParaElement::emitXML(unsigned            indentation,
                              bool               &parentStartedElements,
                              set<FontModifiers> &fontModifiers,
                              bool                firstElement
    ) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    bool startedElements = false;
    block->emitXML(indentation, startedElements, fontModifiers);
}

void
ModifierParaElement::emitXML(unsigned            indentation,
                             bool               &parentStartedElements,
                             set<FontModifiers> &fontModifiers,
                             bool                firstElement
    ) const
{
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
            // terminate an existing "elements"
            cout << "</elements>" << endl;

            // start a new one with updated fonts
            spaces(indentation);
            cout << "<elements font=\"";
            emitFontModifierString(fontModifiers);
            cout << "\">";
        }
    }
}

void
DotsParaElement::emitXML(unsigned            indentation,
                         bool               &parentStartedElements,
                         set<FontModifiers> &fontModifiers,
                         bool                firstElement
    ) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    spaces(indentation);
    cout << "<element type=\"dots\">...</element>" << endl;
}

void
TstarParaElement::emitXML(unsigned            indentation,
                          bool               &parentStartedElements,
                          set<FontModifiers> &fontModifiers,
                          bool                firstElement
    ) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    spaces(indentation);
    cout << "<element type=\"tstar\">***</element>" << endl;
}

void
LineBreakParaElement::emitXML(unsigned            indentation,
                              bool               &parentStartedElements,
                              set<FontModifiers> &fontModifiers,
                              bool                firstElement
    ) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    spaces(indentation);
    cout << "<linebreak/>" << endl;
}

void
PageBreakParaElement::emitXML(unsigned            indentation,
                              bool               &parentStartedElements,
                              set<FontModifiers> &fontModifiers,
                              bool                firstElement
    ) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    spaces(indentation);
    cout << "<pagebreak number=\"" << pageNumber << "\"/>" << endl;
}

void
NDashParaElement::emitXML(unsigned            indentation,
                          bool               &parentStartedElements,
                          set<FontModifiers> &fontModifiers,
                          bool                firstElement
    ) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }

    spaces(indentation);
    if (fontModifiers.size()) {
        cout << "<element type=\"ndash\" font=\"";
        emitFontModifierString(fontModifiers);
        cout << "\">--</element>" << endl;
    } else {
        cout << "<element type=\"ndash\">--</element>" << endl;
    }

};

void
MDashParaElement::emitXML(unsigned            indentation,
                          bool               &parentStartedElements,
                          set<FontModifiers> &fontModifiers,
                          bool                firstElement
    ) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }

    spaces(indentation);
    if (fontModifiers.size()) {
        cout << "<element type=\"mdash\" font=\"";
        emitFontModifierString(fontModifiers);
        cout << "\">---</element>" << endl;
    } else {
        cout << "<element type=\"mdash\">---</element>" << endl;
    }
};

void
OpeningSingleQuoteParaElement::emitXML(unsigned            indentation,
                                       bool               &parentStartedElements,
                                       set<FontModifiers> &fontModifiers,
                                       bool                firstElement
    ) const
{
    if (parentStartedElements == false) {
        spaces(indentation);
        if (fontModifiers.size()) {
            cout << "<elements font=\"";
            emitFontModifierString(fontModifiers);
            cout << "\">";
        } else {
            cout << "<elements>";
        }
        parentStartedElements = true;

        /* If we're starting out <elements>, we should also take care
         * of the space before the first element. */
        if (!firstElement && separatedFromPrevBySpace()) {
            cout << " ";
        }
    }
    cout << "`";
}

void
OpeningDoubleQuotesParaElement::emitXML(unsigned            indentation,
                                        bool               &parentStartedElements,
                                        set<FontModifiers> &fontModifiers,
                                        bool                firstElement
    ) const
{
    if (parentStartedElements == false) {
        spaces(indentation);
        if (fontModifiers.size()) {
            cout << "<elements font=\"";
            emitFontModifierString(fontModifiers);
            cout << "\">";
        } else {
            cout << "<elements>";
        }
        parentStartedElements = true;

        /* If we're starting out <elements>, we should also take care
         * of the space before the first element. */
        if (!firstElement && separatedFromPrevBySpace()) {
            cout << " ";
        }
    }
    cout << "``";
}

void
ClosingDoubleQuotesParaElement::emitXML(unsigned            indentation,
                                        bool               &parentStartedElements,
                                        set<FontModifiers> &fontModifiers,
                                        bool                firstElement
    ) const
{
    if (parentStartedElements == false) {
        spaces(indentation);
        if (fontModifiers.size()) {
            cout << "<elements font=\"";
            emitFontModifierString(fontModifiers);
            cout << "\">";
        } else {
            cout << "<elements>";
        }
        parentStartedElements = true;

        /* If we're starting out <elements>, we should also take care
         * of the space before the first element. */
        if (!firstElement && separatedFromPrevBySpace()) {
            cout << " ";
        }
    }
    cout << "''";
}
