#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

#include "paraElementContainer.h"
#include "variousParaElements.h"

void
ParaElementContainer::emitXML(unsigned            indentation,
                              bool               &parentStartedElements,
                              set<FontModifiers> &fontModifiers) const
{
    // The parent of a paraElementContainer should not have started an
    // <elements>...
    assert(parentStartedElements == false);

    bool startedElements = false;
    vector<ParaElement *>::const_iterator iter;
    bool seenNonPhantom = false;
    for (iter = elements.begin(); iter != elements.end(); iter++) {
        if (iter == elements.begin() || (seenNonPhantom == false)) {
            (*iter)->emitXML(indentation, startedElements, fontModifiers);
            if ((*iter)->isPhantom() == false) {
                seenNonPhantom = true;
            }
        } else {
            if ((*iter)->separatedFromPrevBySpace()) {
                if (startedElements) {
                    cout << " "; // add a white space to precede this element
                }
            }
            (*iter)->emitXML(indentation, startedElements, fontModifiers);
        }
    }

    if (startedElements) {
        cout << "</elements>" << endl;
        startedElements = false;
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
