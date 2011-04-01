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

#include "utils.h"
#include "variousContainerDirectives.h"
#include "paraElement.h"

void
Set::emit(outputMode_t mode, unsigned indentationIn)
{
    assert(mode == DOCBOOK);

    /* update the emit-stack of containerDirectives */
    assert(ContainerDirective::directives.empty());
    outputMode  = mode;
    indentation = indentationIn;
    ContainerDirective::setCurrentContainerDirective(this);

    spaces(indentation);
    cout << "<set xmlns=\"http://docbook.org/ns/docbook\">" << endl;

    string title = getTitle();
    string author = getAuthor();

    /* emit the info block */
    if ((title != "") || (author != "")) {
        spaces(indentation + ParaElement::INDENT_STEP);
        cout << "<info>" << endl;
        spaces(indentation + 2 * ParaElement::INDENT_STEP);
        cout << "<title>"
             << ((title == "") ? "PLEASE FILL IN THE TITLE HERE" : title)
             << "</title>"
             << endl;
        spaces(indentation + 2 * ParaElement::INDENT_STEP);
        cout << "<author><personname>"
             << ((author == "") ? "[PLEASE UPDATE AS NECESSARY]Sri Aurobindo" : author)
             << "</personname></author>"
             << endl;
        spaces(indentation + 2 * ParaElement::INDENT_STEP);
        cout << "<copyright>" << endl;
        spaces(indentation + 3 * ParaElement::INDENT_STEP);
        cout << "<year>[PLEASE UPDATE AS NECESSARY]2010</year>" << endl;
        spaces(indentation + 3 * ParaElement::INDENT_STEP);
        cout << "<holder>[PLEASE UPDATE AS NECESSARY]Sri Aurobindo Ashram Trust, Pondicherry, India.</holder>" << endl;
        spaces(indentation + 2 * ParaElement::INDENT_STEP);
        cout << "</copyright>" << endl;
        spaces(indentation + ParaElement::INDENT_STEP);
        cout << "</info>" << endl;
    }
}

void
Set::emitEnd(void) const
{
    assert(outputMode == DOCBOOK);

    spaces(indentation);
    cout << "</set>" << endl;
}

void
Book::emit(outputMode_t mode, unsigned indentation)
{
}

void
Book::emitEnd(void) const
{
    assert(outputMode == DOCBOOK);

    spaces(indentation);
    cout << "</book>" << endl;
}

void
Part::emit(outputMode_t mode, unsigned indentation)
{
}

void
Part::emitEnd(void) const
{
    assert(outputMode == DOCBOOK);

    spaces(indentation);
    cout << "</part>" << endl;
}


void
Preface::emit(outputMode_t mode, unsigned indentation)
{
}

void
Preface::emitEnd(void) const
{
    assert(outputMode == DOCBOOK);

    spaces(indentation);
    cout << "</preface>" << endl;
}

void
Chapter::emit(outputMode_t mode, unsigned indentation)
{
}

void
Chapter::emitEnd(void) const
{
    assert(outputMode == DOCBOOK);

    spaces(indentation);
    cout << "</chapter>" << endl;
}
