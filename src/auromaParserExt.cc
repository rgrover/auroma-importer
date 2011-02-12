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

#include <cstring>
#include <cstdlib>
#include "auromaParser.ih"
#include "block.h"

void
auromaParser::newPara(void)
{
    // create a new paragraph and push it to the stack
    assert(containerStack.empty());
    Para *p = new Para();
    containerStack.push(p);

    // cout << "creating new para: " << p << endl;
}

void
auromaParser::finishPara(void)
{
    Para *para;

    // get the paragraph at the top of the containerStack
    para = reinterpret_cast<Para *>(containerStack.top());
    containerStack.pop();
    assert(containerStack.empty());
    // cout << "finished para " << para << endl;

    // push this paragraph to our vector of global paragraphs
    paragraphs.push_back(para);
}

void
auromaParser::pushSubContainer(void)
{
    assert(containerStack.empty() == false);

    ParaElementContainer *container;
    container = new Block();

    containerStack.push(container);
}


void
auromaParser::pushSubContainer(const char *blockType)
{
    assert(containerStack.empty() == false);

    ParaElementContainer *container;
    container = new Block(blockType);

    containerStack.push(container);
}

void
auromaParser::popSubContainer(void)
{
    assert(containerStack.empty() == false);

    // pop the top level container off the stack; the stack shouldn't
    // become empty as a result--there should be a paragraph container
    // at the bottom.
    ParaElementContainer *container;
    container = containerStack.top();
    containerStack.pop();
    // cout << "popped container: " << container << endl;

    assert(containerStack.empty() == false);

    // add this container to the paragraph as an element
}


void
auromaParser::updatePrecedingWhiteSpace(const char *in)
{
    if (precedingWhiteSpace == NULL) {
        if (in != NULL) {
            precedingWhiteSpace = strdup(in);
            assert(precedingWhiteSpace != NULL);
        }
    } else {
        if (in == NULL) {
            free(const_cast<char *>(precedingWhiteSpace));
            precedingWhiteSpace = NULL;
        } else {
            if (strcmp(in, precedingWhiteSpace) != 0) {
                free(const_cast<char *>(precedingWhiteSpace));
                precedingWhiteSpace = strdup(in);
                assert(precedingWhiteSpace != NULL);
            }
        }
    }
}


void
auromaParser::emitXML(void)
{
    cout << "<document>" << endl;
    for (vector<Para *>::iterator iter = paragraphs.begin();
         iter != paragraphs.end();
         iter++) {
        (*iter)->emitXML(4);
    }
    cout << "</document>" << endl;
}
