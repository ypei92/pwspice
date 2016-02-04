#ifndef element_vccs_H
#define element_vccs_H

#include "element.h"


class element_vccs : public element
{
    public:
        char* node1c;
        char* node2c;

        element_vccs(){};
        element_vccs(char* input_name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> D_v)
        {
            element(input_name , n1 , n2 , D_v);

            node1c = n1c;
            node2c = n2c;
        }

};
#endif
