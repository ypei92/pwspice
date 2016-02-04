#ifndef element_pmos_H
#define element_pmos_H

#include "element.h"


class element_pmos : public element
{
    public:
        char* source;
        complex<double> length;

        element_pmos(){};
        element_pmos(char* input_name , char* n_drain , char* n_gate , char* n_source , complex<double> v_width , complex<double> v_length)
        {
            element(input_name , n_drain , n_gate , v_width);

            source = n_source;
            length = v_length;

        }

};
#endif
