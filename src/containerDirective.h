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

#ifndef PARA_CONTAINER
#define PARA_CONTAINER

#include <string>
#include <stack>

#include "paraOrDirective.h"
#include "outputMode.h"

using namespace std;

enum ContainerLevel
{
    UNKNOWN = -1,
    SET,
    BOOK,
    PART,
    PREFACE,
    CHAPTER,
};

class ContainerDirective: public ParaOrDirective
{
public:
    ContainerDirective(ContainerLevel l): level(l)
        {
        }

    bool isDirective(void) const
        {
            return true;
        }

    virtual void setTitle(string t)
        {
            title = t;
        }

    string getTitle(void)
        {
            return title;
        }

    virtual void   setAuthor(string author) = 0;
    virtual string getAuthor(void)          = 0;

    static ContainerDirective *currentParaContainer(void)
        {
            return containers.top();
        }
    /* static void setCurrentParaContainer(ContainerDirective *newContainer); */

protected:
    ContainerLevel level;
    string         title;

    /* The stack of para containers */
    static stack<ContainerDirective *> containers;
};

#endif /* PARA_CONTAINER */
