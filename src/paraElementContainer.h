#ifndef PARA_ELEMENT_CONTAINER
#define PARA_ELEMENT_CONTAINER

#include <set>
#include <vector>
using namespace std;

#include "paraElement.h"

class ParaElementContainer : public ParaElement
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

    void append(ParaElement *element);
    void append(string str);

    // append a string with its prevSep turned off
    void appendWithoutPrevSep(string str);

    virtual void emit(outputMode_t        mode,
                      unsigned            indentation,
                      bool               &parentStartedElements,
                      set<FontModifiers> &fontModifiers,
                      bool                firstElement = false
        ) const;

protected:
    vector<ParaElement *> elements;
};


#endif /* PARA_ELEMENT_CONTAINER */
