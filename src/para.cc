#include "para.h"
#include "paraElement.h"

// Para *Para::__curPara = NULL;

void
Para::append(const char *str)
{
    StringParaElement *p = new StringParaElement(str);
    elements.push_back(NULL);
}

