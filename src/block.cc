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

#include "block.h"

void
Block::emit(outputMode_t        mode,
            unsigned            indentation,
            bool               &parentStartedElements,
            set<FontModifiers> &fontModifiersIn,
            bool                firstElement
    ) const
{
    if (parentStartedElements) {
        if (mode == XML) {
            cout << "</elements>" << endl;
        }
        parentStartedElements = false;
    }

    bool startedElements = false;
    set<FontModifiers> fontModifiers(fontModifiersIn); // make a copy
                                                       // of the
                                                       // parent's
                                                       // font-modifiers
                                                       // for this
                                                       // block

    if (blockTypeString) {
        /* If this block has a specific typeString associated with it,
         * then emit a separate XML container to wrap the block. */
        spaces(indentation);
        cout << "<block type=\"" << blockTypeString << "\">" << endl;

        ParaElementContainer::emit(mode,
                                   indentation + INDENT_STEP,
                                   startedElements,
                                   fontModifiers);

        spaces(indentation);
        cout << "</block>" << endl;
    } else {
        /* emit the block at the same indentation level as the parent. */
        ParaElementContainer::emit(mode,
                                   indentation, /* same indentation
                                                 * as the parent */
                                   startedElements,
                                   fontModifiers);
    }
}
