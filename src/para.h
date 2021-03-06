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
 * - Neither Rohit Grover, Aurokruti, nor the names of Aurokruti's
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


#ifndef PARA_H
#define PARA_H

#include <vector>
#include "paraOrDirective.h"
#include "containerDirective.h"
#include "variousParaElements.h"

class Para : public ParaElementContainer, public ParaOrDirective
{
public:
    // The attributes applicable to a paragraph.
    enum ParaAttributes {
        HEADING_NUMBER,
        HEADING_TITLE,
        INDENT,
        CENTER,
        FLUSH_LEFT,
        DROP,
        BLOCK_QUOTE,
        POEM,
        FOOTER,
        ENUMERATION,
        HEAD_QUOTE,
        NUM_PARA_ATTRIBUTES     // This should be the last in the enum.
    };

    Para(void) :
        attributes(NUM_PARA_ATTRIBUTES),
        enumBlock(NULL)
        {
            // cout << "creating a new paragraph" << endl;
            attributes[HEADING_NUMBER] = false;
            attributes[HEADING_TITLE]  = false;
            attributes[CENTER]         = false;
            attributes[INDENT]         = true; // indent is turned on by default
            attributes[CENTER]         = false;
            attributes[FLUSH_LEFT]     = true;
            attributes[DROP]           = false;
            attributes[BLOCK_QUOTE]    = false;
            attributes[POEM]           = false;
            attributes[FOOTER]         = false;
            attributes[ENUMERATION]    = false;
            attributes[HEAD_QUOTE]     = false;

            level = currentLevel;
        }

    ~Para(void)
        {
        }

    static void pushContainerLevel(void);
    static void popContainerLevel(void);

    void setAttribute(ParaAttributes attr);
    void unsetAttribute(ParaAttributes attr);

    bool setEnumerationBlock(ParaElementContainer *block);

    void append(const char *str);

    bool hasTitle(void) const;

    bool isDirective(void) const
        {
            return false;
        }

    void emit(outputMode_t mode, unsigned int &indentation);

    void emitContainedElements(outputMode_t mode,
                               unsigned     indentation);
private:
    vector<bool> attributes;
    ParaElementContainer *enumBlock;
    unsigned        level;        /* paragraph level */

    void emitDocbook(unsigned indentation) const;
    void emitWordpress(unsigned indentation) const;

    static unsigned currentLevel; /* current container level */
};

#endif
