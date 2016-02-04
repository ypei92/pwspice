
#include "DIODE_DEVICE.h"
void DIODE_DEVICE :: traverse()
{
    diode -> traverse();
    return;
}

void DIODE_DEVICE :: append(/*int type ,*/ char * name , char* n1 , char *n2, complex<double> v)
{

    diode -> append(name,n1,n2,v);
    return;
}
