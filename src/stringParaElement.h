#ifndef STRING_PARA_ELEMENT
#define STRING_PARA_ELEMENT

#include <iostream>
#include <string>
using namespace std;

#include "paraElement.h"

class StringParaElement : public ParaElement {
public:
    StringParaElement(const char *strIn)
        : str(strIn)
        {
            // empty
        }

    void display(void);

private:
    string str;
};


#endif /* #ifdef STRING_PARA_ELEMENT */
