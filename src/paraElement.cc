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
 * - Neither Rohit Grover, nor Aurokruti nor the names of Aurokruti's
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
#include "paraElement.h"

unsigned int ParaElement::footnoteNumber = 0;
string       ParaElement::footnoteHref = string("");


bool
ParaElement::separatedFromPrevBySpace(void) const
{
    return prevSep;
}

bool
ParaElement::isPhantom(void) const
{
    return false;
}


void
ParaElement::emitStartFontModifier(outputMode_t       mode,
                                   set<FontModifiers> fontModifiers)
{
    if (mode == DOCBOOK) {
        cout << "<elements font=\"";
        for (set<FontModifiers>::iterator iter = fontModifiers.begin();
             iter != fontModifiers.end();
             iter++) {
            if (iter != fontModifiers.begin()) {
                cout << ",";
            }

            switch (*iter) {
            case ITALICS:
                cout << "italics";
                break;
            case BOLD:
                cout << "bold";
                break;
            case SMALL_CAPS:
                cout << "small_caps";
                break;
            default:
                break;
            }
        }
        cout << "\">";
    } else if (mode == WORDPRESS) {
        for (set<FontModifiers>::iterator iter = fontModifiers.begin();
             iter != fontModifiers.end();
             iter++) {
            switch (*iter) {
            case ITALICS:
                cout << "<i>";
                break;
            case BOLD:
                cout << "<b>";
                break;
            case SMALL_CAPS:
            default:
                break;
            }
        }
    }
}

void
ParaElement::emitEndFontModifier(outputMode_t       mode,
                                 set<FontModifiers> fontModifiers)
{
    assert(mode == WORDPRESS);
    for (set<FontModifiers>::reverse_iterator iter = fontModifiers.rbegin();
         iter != fontModifiers.rend();
         iter++) {
        switch (*iter) {
        case ITALICS:
            cout << "</i>";
            break;
        case BOLD:
            cout << "</b>";
            break;
        case SMALL_CAPS:
        default:
            break;
        }
    }
}


unsigned int
ParaElement::getFootnoteNumber(void)
{
    if (footnoteNumber == 0) {
        srand48(time(NULL)); /* initialize the random number generator */

        footnoteNumber = 1;
        updateFootnoteHref();
    }

    return footnoteNumber;
}

void
ParaElement::incrementFootnoteNumber(void)
{
    ++footnoteNumber;
    updateFootnoteHref();
}

void
ParaElement::resetFootnoteNumber()
{
    if (footnoteNumber == 0) {
        return;                 /* don't do anything just yet; wait
                                 * for the first use of
                                 * footnoteNumber */
    }

    /* otherwise, reset the footnote number and update the href string */
    footnoteNumber = 1;
    updateFootnoteHref();
}

string
ParaElement::getFootnoteHref(void)
{
    assert(footnoteNumber != 0);
    return footnoteHref;
}

void
ParaElement::updateFootnoteHref(void)
{
    const unsigned int N = 3;
    long int num[N];
    unsigned int i;

    stringstream tmpStr;
    for (i = 0; i < N; i++) {
        if (i != 0) {
            tmpStr << "-";
        }
        tmpStr << lrand48();
    }

    footnoteHref = tmpStr.str();
}
