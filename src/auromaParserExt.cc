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
    assert(elementContainerStack.empty());
    Para *p = new Para();
    elementContainerStack.push(p);

    // cout << "creating new para: " << p << endl;
}

void
auromaParser::finishPara(void)
{
    Para *para;

    // get the paragraph at the top of the elementContainerStack
    para = reinterpret_cast<Para *>(elementContainerStack.top());
    elementContainerStack.pop();
    assert(elementContainerStack.empty());
    // cout << "finished para " << para << endl;

    // push this paragraph to our vector of global paragraphs
    pods.push_back(para);
}

void
auromaParser::newDirective(ContainerDirective *directive)
{
    pods.push_back(directive);
}

void
auromaParser::pushElementSubContainer(void)
{
    assert(elementContainerStack.empty() == false);

    ParaElementContainer *container;
    container = new Block();

    elementContainerStack.push(container);
}


void
auromaParser::pushElementSubContainer(const char *blockType)
{
    assert(elementContainerStack.empty() == false);

    ParaElementContainer *container;
    container = new Block(blockType);

    elementContainerStack.push(container);
}

void
auromaParser::popElementSubContainer(void)
{
    assert(elementContainerStack.empty() == false);

    // pop the top level container off the stack; the stack shouldn't
    // become empty as a result--there should be a paragraph container
    // at the bottom.
    ParaElementContainer *container;
    container = elementContainerStack.top();
    elementContainerStack.pop();
    // cout << "popped container: " << container << endl;

    assert(elementContainerStack.empty() == false);

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
auromaParser::emit(outputMode_t outputMode)
{
    ParaOrDirective *firstPod = pods.front();
    assert(firstPod->isDirective());

    ContainerDirective *firstDirective =
        reinterpret_cast<ContainerDirective *>(firstPod);

    switch (outputMode) {
    case DOCBOOK:
        cout << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;
        break;

    case WORDPRESS:
        cout << "<div id=\"content\">" << endl;
        break;
    }

    /* Loop over all paragraphs and emit code for them. */
    for (vector<ParaOrDirective *>::iterator iter = pods.begin();
         iter != pods.end();
         iter++) {
        (*iter)->emit(outputMode, 4);
        break;
    }

    switch (outputMode) {
    case DOCBOOK:
        ContainerDirective::setCurrentContainerDirective(NULL);
        cout << "</xml>" << endl;
        break;
    case WORDPRESS:
        cout << "</div>" << endl;
        break;
    }
}
