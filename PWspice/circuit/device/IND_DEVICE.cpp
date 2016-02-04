
#include "IND_DEVICE.h"

void IND_DEVICE :: traverse()
{
    c_ind -> traverse();

    return;
}

void IND_DEVICE :: append(/*int type ,*/ char * name , char* n1 , char *n2, complex<double> v , complex<double> v_init)
{
   // switch(type)
    c_ind -> append(name , n1 , n2 , v , v_init);

    return;
}
