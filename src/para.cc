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
 * - Neither Rohit Grover, nor Aurokruti, nor the names of its
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

#include <cassert>
#include "para.h"

#include "auromaParser.ih"

unsigned Para::currentLevel = 1;

extern auromaFlexLexer *lexer;

void
Para::pushContainerLevel(void)
{
    ++currentLevel;
}

void
Para::popContainerLevel(void)
{
    assert(currentLevel > 1);
    --currentLevel;
}

void
Para::setAttribute(ParaAttributes attr)
{
    // cout << "seting PARA attribute: " << attr << endl;
    switch (attr) {
    case FLUSH_LEFT:
        attributes[FLUSH_LEFT] = true;
        attributes[CENTER]     = false;
        break;
    case HEADING_TITLE:
        if (attributes[HEADING_NUMBER]) {
            std::cerr << "\033[01;31mpaser: line "
                      << lexer->lineno() << ":\033[00m "
                      << "attempting to set heading title and "
                      << "heading number within the same paragraph" << endl;
            return;
        }
        attributes[HEADING_TITLE] = true;
        break;
    case HEADING_NUMBER:
        if (attributes[HEADING_TITLE]) {
            std::cerr << "\033[01;31mpaser: line "
                      << lexer->lineno() << ":\033[00m "
                      << "attempting to set heading title and "
                      << "heading number within the same paragraph" << endl;
            return;
        }
        attributes[HEADING_NUMBER] = true;
        break;
    default:
        attributes[attr] = true;
        break;
    }
}

void
Para::unsetAttribute(ParaAttributes attr)
{
    // cout << "unseting PARA attribute: " << attr << endl;
    attributes[attr] = false;
}

bool
Para::setEnumerationBlock(ParaElementContainer *block)
{
    assert(block != NULL);

    /*
     * Ensure that we did not already have an enumeration attribute
     * for this paragraph
     */
    if (enumBlock != NULL) {
        return (false);
    }

    setAttribute(ENUMERATION);
    enumBlock = block;
    return (true);
}

void
Para::emitXML(unsigned indentation) const
{
    spaces(indentation);
    cout << "<para";

    if (attributes[HEADING_NUMBER] ||
        attributes[HEADING_TITLE] ||
        (attributes[INDENT] == false) ||
        attributes[CENTER] ||
        (attributes[FLUSH_LEFT] == false) ||
        attributes[DROP] ||
        attributes[QUOTE] ||
        attributes[POEM] ||
        attributes[FOOTER] ||
        attributes[ENUMERATION] ||
        attributes[HEAD_QUOTE]) {
        cout << " attributes=\"";

        bool someAttributeEmitted = false;
        for (unsigned i = 0; i < attributes.size(); ++i) {
            switch (i) {
            case HEADING_NUMBER:
                if (attributes[i]) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "heading_number";
                    someAttributeEmitted = true;
                }
                break;
            case HEADING_TITLE:
                if (attributes[i]) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "heading_title";
                    someAttributeEmitted = true;
                }
                break;
            case INDENT:
                if (attributes[i] == false) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "noindent";
                    someAttributeEmitted = true;
                }
                break;
            case CENTER:
                if (attributes[i]) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "center";
                    someAttributeEmitted = true;
                }
                break;
            case FLUSH_LEFT:
                if (attributes[i] == false) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "flushright";
                    someAttributeEmitted = true;
                }
                break;
            case DROP:
                if (attributes[i]) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "drop";
                    someAttributeEmitted = true;
                }
                break;
            case QUOTE:
                if (attributes[i]) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "quote";
                    someAttributeEmitted = true;
                }
                break;
            case POEM:
                if (attributes[i]) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "poem";
                    someAttributeEmitted = true;
                }
                break;
            case FOOTER:
                if (attributes[i]) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "footer";
                    someAttributeEmitted = true;
                }
                break;
            case ENUMERATION:
                if (attributes[i]) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "enumeration";
                    someAttributeEmitted = true;
                    // if (enumBlock) {
                    //     cout << "[";
                    //     enumBlock->display();
                    //     cout << "]";
                    // }
                }
                break;
            case HEAD_QUOTE:
                if (attributes[i]) {
                    if (someAttributeEmitted) {
                        cout << ",";
                    }
                    cout << "headquote";
                    someAttributeEmitted = true;
                }
                break;
            default:
                assert(0);
            }
        }
        cout << "\"";
        if (attributes[HEADING_NUMBER] || attributes[HEADING_TITLE]) {
            cout << " level=\"" << level << "\"";
        }
    }
    cout << ">" << endl;

    bool startedElements = false;
    set<FontModifiers> fontModifiers;
    ParaElementContainer::emitXML(indentation + INDENT_STEP,
                                  startedElements,
                                  fontModifiers);

    spaces(indentation);
    cout << "</para>" << endl;
}
