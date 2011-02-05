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


#ifndef PARA_H
#define PARA_H

#include <vector>
#include "paraElementContainer.h"
#include "variousParaElements.h"

class Para : public ParaElementContainer
{
public:
    Para(void) :
        attributes(NUM_PARA_ATTRIBUTES),
        enumBlock(NULL)
        {
            // cout << "creating a new paragraph" << endl;
            attributes[INDENT]      = true; // indent is turned on by default
            attributes[CENTER]      = false;
            attributes[FLUSH_LEFT]  = true;
            attributes[DROP]        = false;
            attributes[QUOTE]       = false;
            attributes[POEM]        = false;
            attributes[FOOTER]      = false;
            attributes[ENUMERATION] = false;
        }

    ~Para(void)
        {
        }

    // The attributes applicable to a paragraph.
    enum ParaAttributes {
        INDENT = 0,
        CENTER,
        FLUSH_LEFT,
        DROP,
        QUOTE,
        POEM,
        FOOTER,
        ENUMERATION,
        NUM_PARA_ATTRIBUTES     // This should be the last in the enum.
    };

    void setAttribute(ParaAttributes attr);
    void unsetAttribute(ParaAttributes attr);

    bool setEnumerationBlock(ParaElementContainer *block);

    void append(const char *str);

    void display(void) const;

private:
    vector<bool> attributes;
    ParaElementContainer *enumBlock;
};

#endif
