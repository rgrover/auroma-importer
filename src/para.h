#ifndef PARA_H
#define PARA_H

#include "paraElementContainer.h"
#include "stringParaElement.h"

class Para : public ParaElementContainer
{
public:
    Para(void)
        {
            cout << "creating a new paragraph" << endl;
        }
    ~Para(void)
        {
        }

    void append(const char *str);
};

#endif
