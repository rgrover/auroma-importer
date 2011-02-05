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
#include "para.h"

void
Para::setAttribute(ParaAttributes attr)
{
    // cout << "seting PARA attribute: " << attr << endl;
    switch (attr) {
    case FLUSH_LEFT:
        attributes[FLUSH_LEFT] = true;
        attributes[CENTER]     = false;
        break;
    default:
        attributes[attr]       = true;
        break;
    }
}

void
Para::unsetAttribute(ParaAttributes attr)
{
    // cout << "unseting PARA attribute: " << attr << endl;
    attributes[attr] = false;
}

void
Para::display(void) const
{
    for (unsigned i = 0; i < attributes.size(); ++i) {
        switch (i) {
        case INDENT:
            if (attributes[i] == false) {
                cout << "<noindent>";
            }
            break;
        case CENTER:
            if (attributes[i]) {
                cout << "<center>";
            }
            break;
        case FLUSH_LEFT:
            if (attributes[i] == false) {
                cout << "<flushright>";
            }
            break;
        case DROP:
            if (attributes[i]) {
                cout << "<drop>";
            }
            break;
        case QUOTE:
            if (attributes[i]) {
                cout << "<quote>";
            }
            break;
        case POEM:
            if (attributes[i]) {
                cout << "<poem>";
            }
            break;
        case FOOTER:
            if (attributes[i]) {
                cout << "<footer>";
            }
            break;
        default:
            assert(0);
        }
    }

    ParaElementContainer::display();
    cout << endl;
}
