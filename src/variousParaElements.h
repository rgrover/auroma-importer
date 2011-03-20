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

#ifndef VARIOUS_PARA_ELEMENTS
#define VARIOUS_PARA_ELEMENTS

#include <iostream>
#include <string>
using namespace std;

#include "paraElement.h"
#include "paraElementContainer.h"

class StringParaElement : public ParaElement
{
public:
    StringParaElement(string strIn)
        : ParaElement(), str(strIn)
        {
            // empty
        }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;

private:
    string str;
};


class FootnoteParaElement : public ParaElement
{
public:
    FootnoteParaElement(ParaElementContainer *blockIn)
        : block(blockIn)
        {
            prevSep = false;
        }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;

private:
    ParaElementContainer *block;
};


class ReferenceParaElement : public ParaElement
{
public:
    ReferenceParaElement(ParaElementContainer *blockIn)
        : block(blockIn)
        {
        }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;

private:
    ParaElementContainer *block;
};


class ModifierParaElement : public ParaElement
{
public:
    ModifierParaElement(FontModifiers mod)
        : ParaElement(), modifier(mod)
        {
            prevSep = false;
        }

    /*
     * Modifier paraElements are phantoms when it comes to the notion
     * of 'separatedFromPrevBySpace'. This virtual function returns
     * false by default, but should be overridden by all phantom
     * elements to return true in order to handle spaces properly.
     */
    bool isPhantom(void) const {
        return true;
    }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;

private:
    FontModifiers modifier;
};

class DotsParaElement : public ParaElement
{
public:

    DotsParaElement()
        : ParaElement()
        {
            prevSep = false;
        }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;
};

class TstarParaElement : public ParaElement
{
public:
    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;
};

class LineBreakParaElement : public ParaElement
{
public:
    LineBreakParaElement()
        : ParaElement()
        {
            prevSep = false;
        }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;
};

class PageBreakParaElement : public ParaElement
{
public:
    PageBreakParaElement()
        : ParaElement()
        {
            prevSep = false;
        }

    PageBreakParaElement(string number)
        : ParaElement(), pageNumber(number)
        {
            prevSep = false;
        }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;

private:
    string pageNumber;
};

class NDashParaElement : public ParaElement
{
public:
    NDashParaElement()
        : ParaElement()
        {
            prevSep = false;
        }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;
};

class MDashParaElement : public ParaElement
{
public:
    MDashParaElement()
        : ParaElement()
        {
            prevSep = false;
        }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;
};

class OpeningSingleQuoteParaElement : public ParaElement
{
public:
    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;
};

class OpeningDoubleQuotesParaElement : public ParaElement
{
public:
    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;
};

class ClosingDoubleQuotesParaElement : public ParaElement
{
public:
    ClosingDoubleQuotesParaElement()
        : ParaElement()
        {
            prevSep = false;
        }

    void emit(outputMode_t        mode,
              unsigned            indentation,
              bool               &parentStartedElements,
              set<FontModifiers> &fontModifiers,
              bool                firstElement = false
        ) const;
};

#endif /* #ifdef VARIOUS_PARA_ELEMENTS */
