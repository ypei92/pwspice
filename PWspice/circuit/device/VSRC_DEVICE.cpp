
#include "VSRC_DEVICE.h"

void VSRC_DEVICE :: traverse()
{
    vsrc -> traverse();

    return;
}

void VSRC_DEVICE :: append(/*int type ,*/ char * name , char* n1 , char *n2, complex<double> v )
{
   // switch(type)
    vsrc -> append(name , n1 , n2 , v );

    return;
}

