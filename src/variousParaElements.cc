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
StringParaElement::display(void) const
{
    cout << str;
}

void
FootnoteParaElement::display(void) const
{
    cout << "[fn]{";
    block->display();
    cout << "}";
}

void
ReferenceParaElement::display(void) const
{
    cout << "[ref]{";
    block->display();
    cout << "}";
}

void
ModifierParaElement::display(void) const
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
DotsParaElement::display(void) const
{
    cout << "...";
}

void
TstarParaElement::display(void) const
{
    cout << "***";
}

void
LineBreakParaElement::display(void) const
{
    cout << endl;
}

void
PageBreakParaElement::display(void) const
{
    cout << endl << "PAGE[" << pageNumber << "] " << endl;
}

void NDashParaElement::display(void) const
{
    cout << "--";
};

void MDashParaElement::display(void) const
{
    cout << "---";
};

void OpeningSingleQuoteParaElement::display(void) const
{
    cout << "`";
}

void OpeningDoubleQuotesParaElement::display(void) const
{
    cout << "``";
}

void ClosingDoubleQuotesParaElement::display(void) const
{
    cout << "''";
}
