#ifndef PARA_ELEMENT_CONTAINER
#define PARA_ELEMENT_CONTAINER

#include <vector>
using namespace std;

#include "paraElement.h"

class ParaElementContainer
{
public:
    // empty constructor
    ParaElementContainer()
        {
        }

    // destructor
    virtual ~ParaElementContainer()
        {
            vector<ParaElement *>::iterator iter;

            for (iter = elements.begin(); iter != elements.end(); iter++) {
                delete (*iter);
            }
        }


    void appendParaElement(ParaElement *element);
    void display(void);

protected:
    vector<ParaElement *> elements;
};


#endif /* PARA_ELEMENT_CONTAINER */
