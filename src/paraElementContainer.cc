#include <iostream>
#include <vector>
using namespace std;

#include "paraElementContainer.h"
#include "variousParaElements.h"

void
ParaElementContainer::display(void)
{
    // cout << elements.size() << endl;

    vector<ParaElement *>::const_iterator iter;
    for (iter = elements.begin(); iter != elements.end(); iter++) {
        (*iter)->display();
        cout << " ";            // add a white space to separate elements
    }

    cout << endl;
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
