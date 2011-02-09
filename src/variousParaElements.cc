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

#include <cassert>
#include "variousParaElements.h"

void
StringParaElement::emitXML(unsigned indentation,
                           bool &parentStartedElements) const
{
    if (parentStartedElements == false) {
        spaces(indentation);
        cout << "<elements>";
        parentStartedElements = true;
    }
    cout << str;
}

void
FootnoteParaElement::emitXML(unsigned indentation,
                             bool &parentStartedElements) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    bool startedElements = false;
    block->emitXML(indentation, startedElements);
}

void
ReferenceParaElement::emitXML(unsigned indentation,
                              bool &parentStartedElements) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    bool startedElements = false;
    block->emitXML(indentation, startedElements);
}

void
ModifierParaElement::emitXML(unsigned indentation,
                             bool &parentStartedElements) const
{
    switch (modifier) {
    case ParaElement::ITALICS:
        cout << "[it]";
        break;
    case ParaElement::BOLD:
        cout << "[bf]";
        break;
    case ParaElement::SMALL_CAPS:
        cout << "[sc]";
        break;
    default:
        assert(0);
    }
}

void
DotsParaElement::emitXML(unsigned indentation,
                         bool &parentStartedElements) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    spaces(indentation);
    cout << "<element type=\"dots\">...</element>" << endl;
}

void
TstarParaElement::emitXML(unsigned indentation,
                          bool &parentStartedElements) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    spaces(indentation);
    cout << "<element type=\"tstar\">***</element>" << endl;
}

void
LineBreakParaElement::emitXML(unsigned indentation,
                              bool &parentStartedElements) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    cout << "<linebreak/>" << endl;
}

void
PageBreakParaElement::emitXML(unsigned indentation,
                              bool &parentStartedElements) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    spaces(indentation);
    cout << "<pagebreak number=\"" << pageNumber << "\"/>" << endl;
}

void
NDashParaElement::emitXML(unsigned indentation,
                          bool &parentStartedElements) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    spaces(indentation);
    cout << "<element type=\"ndash\">--</element>" << endl;
};

void
MDashParaElement::emitXML(unsigned indentation,
                          bool &parentStartedElements) const
{
    if (parentStartedElements) {
        cout << "</elements>" << endl;
        parentStartedElements = false;
    }
    spaces(indentation);
    cout << "<element type=\"mdash\">---</element>" << endl;
};

void
OpeningSingleQuoteParaElement::emitXML(unsigned indentation,
                                       bool &parentStartedElements) const
{
    if (parentStartedElements == false) {
        spaces(indentation);
        cout << "<elements>";
        parentStartedElements = true;
    }
    cout << "`";
}

void
OpeningDoubleQuotesParaElement::emitXML(unsigned indentation,
                                        bool &parentStartedElements) const
{
    if (parentStartedElements == false) {
        spaces(indentation);
        cout << "<elements>";
        parentStartedElements = true;
    }
    cout << "``";
}

void
ClosingDoubleQuotesParaElement::emitXML(unsigned indentation,
                                        bool &parentStartedElements) const
{
    if (parentStartedElements == false) {
        spaces(indentation);
        cout << "<elements>";
        parentStartedElements = true;
    }
    cout << "''";
}
