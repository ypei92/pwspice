#ifndef element_ccvs_H
#define element_ccvs_H

#include "element.h"


class element_ccvs : public element
{
    public:
        char* vname;

        element_ccvs(){};
        element_ccvs(char* input_name , char* n1 , char* n2 , char* v_n , complex<double> vHK)
        {
            element(input_name , n1 , n2 , vHK);

            vname = v_n;
        }

};
#endif
