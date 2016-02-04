//The cpp for cont_vc_device.cpp


#include "CONT_VC_DEVICE.h"

void CONT_VC_DEVICE :: traverse()
{
    vccs -> traverse();
    vcvs -> traverse();
    return;
}

void CONT_VC_DEVICE :: append( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v , int type )
{

    switch(type)
    {
        case 0 : vccs -> append( name , n1 , n2 , n1c , n2c , v);break;
        case 1 : vcvs -> append( name , n1 , n2 , n1c , n2c , v);break;
    }

    return;
}


