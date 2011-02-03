#ifndef PARA_H
#define PARA_H

#include <vector>
using namespace std;

#include "paraElement.h"
#include "stringParaElement.h"

class Para {
public:
    Para(void);
    ~Para(void);

    void append(const char *str);

    /* static Para *curPara(void); */

private:
    vector<ParaElement *> elements;
    /* static Para *__curPara; */
};

inline
Para::Para(void)
{
    // nothing for now
    cout << "creating a new paragraph" << endl;
}

inline
Para::~Para(void)
{
    vector<ParaElement *>::iterator iter;

    for (iter = elements.begin(); iter != elements.end(); iter++) {
        delete *iter;
    }
}

/* inline Para * */
/* Para::curPara(void) */
/* { */
/*     return Para::__curPara; */
/* } */

#endif
