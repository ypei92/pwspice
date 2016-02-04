
#include "CONT_CC_DEVICE.h"


void CONT_CC_DEVICE :: traverse()
{
    cccs -> traverse();
    ccvs -> traverse();
    return;
}

void CONT_CC_DEVICE :: append( char* name , char* n1 , char* n2 , char* vname , complex<double> v , int type )
{

    switch(type)
    {
        case 0 : cccs -> append( name , n1 , n2 , vname , v);break;
        case 1 : ccvs -> append( name , n1 , n2 , vname , v);break;
    }

    return;
}

