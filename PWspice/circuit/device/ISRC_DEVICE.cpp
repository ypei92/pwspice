
#include "ISRC_DEVICE.h"

void ISRC_DEVICE :: traverse()
{
    isrc -> traverse();

    return;
}

void ISRC_DEVICE :: append(/*int type ,*/ char * name , char* n1 , char *n2, complex<double> v)
{
   // switch(type)
    isrc -> append(name , n1 , n2 , v );

    return;
}

