#ifndef element_cap_H
#define element_cap_H

#include "element.h"


class element_cap : public element
{
    public:
        complex<double> init_value;
        element_cap(){};
        element_cap(char* input_name , char* n1 , char* n2 , complex<double> D_v , complex<double> i_v)
        {
            element(input_name , n1 , n2 , D_v);

            init_value = i_v;
        }

};
#endif
