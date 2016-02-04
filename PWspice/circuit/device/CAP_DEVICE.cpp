#include "CAP_DEVICE.h"

void CAP_DEVICE :: traverse()
{
    c_cap -> traverse();

    return;
}

void CAP_DEVICE :: append(/*int type ,*/ char * name , char* n1 , char *n2, complex<double> v , complex<double> v_init)
{
   // switch(type)
    c_cap -> append(name , n1 , n2 , v , v_init);

    return;
}

