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

#ifndef PARA_ELEMENT_H
#define PARA_ELEMENT_H

#include <set>
#include <iostream>
using namespace std;

class ParaElement {
public:
   /* font modifiers */
    enum FontModifiers {
        ITALICS,
        BOLD,
        SMALL_CAPS,
    };

    ParaElement(void)
        : prevSep(true)
        {
        }
    virtual ~ParaElement()
        {
        }

    void unsetPrevSep(void) {
        prevSep = false;
    }

    /*
     * Should this element be separated from its preceding element
     * with a space?
     */
    virtual bool separatedFromPrevBySpace(void);

    virtual void emitXML(unsigned            indentation,
                         bool               &startedElements,
                         set<FontModifiers> &fontModifiers) const = 0;


    const static unsigned INDENT_STEP = 4;

protected:
    bool   prevSep;             /* Is this element separated from its
                                 * previous element by a white
                                 * space? */

    static void emitFontModifierString(set<FontModifiers> fontModifiers);

    void spaces(unsigned int indentation) const
    {
        for (unsigned i = 0; i < indentation; i++) {
            cout << " ";
        }
    }

};


#endif // #ifndef PARA_ELEMENT_H
