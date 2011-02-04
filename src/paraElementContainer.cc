#include <iostream>
#include <vector>
using namespace std;

#include "paraElementContainer.h"

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
ParaElementContainer::appendParaElement(ParaElement *element)
{
    elements.push_back(element);
}
