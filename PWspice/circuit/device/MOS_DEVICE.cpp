
#include "MOS_DEVICE.h"

void MOS_DEVICE :: traverse()
{
    nmos -> traverse();
    pmos -> traverse();
    return;
}

void MOS_DEVICE :: append( char * name , char* n1 , char *n2 , char* n3 , int type , complex<double> w , complex<double> l )
{

    switch(type)
    {
        case 0 : nmos -> append( name , n1 , n2 , n3 , w , l);break;
        case 1 : pmos -> append( name , n1 , n2 , n3 , w , l);break;
    }

    return;
}
