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

#include "auromaParser.ih"

void
auromaParser::newPara(void)
{
    // cout << "creating new para" << endl;

    // create a new paragraph and push it to the stack
    assert(containerStack.empty());
    Para *p = new Para();
    containerStack.push(p);
}

void
auromaParser::finishPara(void)
{
    Para *para;

    // cout << "finished creating para" << endl;

    // get the paragraph at the top of the containerStack
    para = reinterpret_cast<Para *>(containerStack.top());
    containerStack.pop();
    assert(containerStack.empty());

    // push this paragraph to our vector of global paragraphs
    paragraphs.push_back(para);
}

void
auromaParser::pushSubContainer(void)
{
    assert(0);                  // for now
}

void
auromaParser::popSubContainer(void)
{
    assert(0);                  // for now
}


void
auromaParser::display(void)
{
    // cout << "in display" << endl;

    // free up all the paragraphs
    vector<Para *>::iterator iter;
    for (iter = paragraphs.begin(); iter != paragraphs.end(); iter++) {
        cout << "PARA: ";
        (*iter)->display();
    }
}
