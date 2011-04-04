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

#include <cassert>

#include "containerDirective.h"
#include "paraElement.h"

stack<ContainerDirective *> ContainerDirective::directives;

void
ContainerDirective::setCurrentContainerDirective(
    ContainerDirective *newDirective,
    unsigned int       &indentation)
{
    /* If this is the first directive, then simply push it to the stack. */
    if (directives.empty()) {
        assert((newDirective->level == SET) || (newDirective->level == BOOK));
        directives.push(newDirective);

        newDirective->origIndentation =  0;
        indentation                   += ParaElement::INDENT_STEP;

        return;
    }

    /* If this is the end of the top level emit loop, then pop off all
     * directives from the stack. */
    if (newDirective == NULL) {
        while(!directives.empty()) {
            directives.top()->emitEnd();
            directives.pop();

            indentation -= ParaElement::INDENT_STEP;
        }
    } else {
        /* If the type of the new directive is more important than that of
         * the top directive, then we need to pop enough directives until
         * we find one whose type is more important than that of the new
         * directive to be pushed. */
        while(directives.top()->level >= newDirective->level) {
            directives.top()->emitEnd();
            directives.pop();
            assert(!directives.empty());

            indentation -= ParaElement::INDENT_STEP;
        }

        newDirective->origIndentation  = indentation;
        indentation                   += ParaElement::INDENT_STEP;
        directives.push(newDirective);
    }
}
