#include <iostream>
#include <vector>
using namespace std;

#include "paraElementContainer.h"
#include "variousParaElements.h"

void
ParaElementContainer::display(void) const
{
    // cout << elements.size() << endl;

    vector<ParaElement *>::const_iterator iter;
    for (iter = elements.begin(); iter != elements.end(); iter++) {
        if (iter != elements.begin() && (*iter)->separatedFromPrevBySpace()) {
            cout << " ";     // add a white space to precede this element
        }
        (*iter)->display();
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
