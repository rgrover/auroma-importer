#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

#include "paraElementContainer.h"
#include "variousParaElements.h"

void
ParaElementContainer::emit(outputMode_t        mode,
                           unsigned            indentation,
                           bool               &parentStartedElements,
                           set<FontModifiers> &fontModifiers,
                           bool                firstElement /* unused */
    ) const
{
    vector<ParaElement *>::const_iterator iter;
    bool seenNonPhantom = false;
    for (iter = elements.begin(); iter != elements.end(); iter++) {
        if (iter == elements.begin() || (seenNonPhantom == false)) {
            (*iter)->emit(mode,
                          indentation,
                          parentStartedElements,
                          fontModifiers,
                          true /* first element */
                );
            if ((*iter)->isPhantom() == false) {
                seenNonPhantom = true;
            }
        } else {
            if ((*iter)->separatedFromPrevBySpace()) {
                if (parentStartedElements) {
                    cout << " "; // add a white space to precede this element
                }
            }
            (*iter)->emit(mode,
                          indentation,
                          parentStartedElements,
                          fontModifiers);
        }
    }

    if (parentStartedElements) {
        if (mode == XML) {
            cout << "</elements>";
            parentStartedElements = false;
        } else if (mode == WORDPRESS) {
            if (fontModifiers.size()) {
                emitEndFontModifier(mode, fontModifiers);
            }
        }
    }
}

void
ParaElementContainer::append(ParaElement *element)
{
    elements.push_back(element);
}

void
ParaElementContainer::append(const char *str)
{
    ParaElement *p = new StringParaElement(str);
    append(p);
}

void
ParaElementContainer::appendWithoutPrevSep(const char *str)
{
    StringParaElement *s = new StringParaElement(str);
    s->unsetPrevSep();
    append(s);
}
