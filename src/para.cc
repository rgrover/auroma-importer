#include "para.h"
#include "stringParaElement.h"

void
Para::append(const char *str)
{
    ParaElement *p = new StringParaElement(str);

    appendParaElement(p);
}

