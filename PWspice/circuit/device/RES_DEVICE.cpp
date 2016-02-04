
#include "RES_DEVICE.h"

void RES_DEVICE :: traverse()
{
    l_res -> traverse();
    return;
}

void RES_DEVICE :: append(/*int type ,*/ char * name , char* n1 , char *n2, complex<double> v)
{
    l_res -> append(name,n1,n2,v);
    return;
}

