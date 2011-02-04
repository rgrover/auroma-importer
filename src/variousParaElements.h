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

#ifndef VARIOUS_PARA_ELEMENTS
#define VARIOUS_PARA_ELEMENTS

#include <iostream>
#include <string>
using namespace std;

#include "paraElement.h"

class StringParaElement : public ParaElement
{
public:
    StringParaElement(const char *strIn)
        : str(strIn), prevSep(true)
        {
            // empty
        }

    bool separatedFromPrevBySpace(void) {
        return prevSep;
    }

    void unsetPrevSep(void) {
        prevSep = false;
    }

    void display(void);

private:
    string str;
    bool   prevSep;
};

class DotsParaElement : public ParaElement
{
public:
    bool separatedFromPrevBySpace(void) {
        return false;
    }
    void display(void);
};

class TstarParaElement : public ParaElement
{
public:
    void display(void);
};

class LineBreakParaElement : public ParaElement
{
public:
    bool separatedFromPrevBySpace(void) {
        return false;
    }
    void display(void);
};

class PageBreakParaElement : public ParaElement
{
public:
    bool separatedFromPrevBySpace(void) {
        return false;
    }
    PageBreakParaElement(const char *number)
        : pageNumber(number)
        {
        }

    void display(void);

private:
    string pageNumber;
};

class NDashParaElement : public ParaElement
{
public:
    bool separatedFromPrevBySpace(void) {
        return false;
    }
    void display(void);
};

class MDashParaElement : public ParaElement
{
public:
    bool separatedFromPrevBySpace(void) {
        return false;
    }
    void display(void);
};

class OpeningSingleQuoteParaElement : public ParaElement
{
public:
    void display(void);
};

class OpeningDoubleQuotesParaElement : public ParaElement
{
public:
    void display(void);
};

class ClosingDoubleQuotesParaElement : public ParaElement
{
public:
    bool separatedFromPrevBySpace(void) {
        return false;
    }
    void display(void);
};

#endif /* #ifdef VARIOUS_PARA_ELEMENTS */
