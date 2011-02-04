#ifndef PARA_ELEMENT_H
#define PARA_ELEMENT_H

class ParaElement {
public:
    /* nothing for now */
    ParaElement(void)
        {
        }
    virtual ~ParaElement()
        {
        }

    virtual void display(void) = 0;

private:
};

#endif // #ifndef PARA_ELEMENT_H
