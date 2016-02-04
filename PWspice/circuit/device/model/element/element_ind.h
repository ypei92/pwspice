#ifndef element_ind_H
#define element_ind_H

#include "element.h"


class element_ind : public element
{
    public:
        complex<double> init_value;
        element_ind(){};
        element_ind(char* input_name , char* n1 , char* n2 , complex<double> D_v , complex<double> i_v)
        {
            element(input_name , n1 , n2 , D_v);

            init_value = i_v;
        }

};
#endif
