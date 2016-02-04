#ifndef element_cccs_H
#define element_cccs_H

#include "element.h"


class element_cccs : public element
{
    public:
        //complex<double> valueFK;
        char* vname;

        element_cccs(){};
        element_cccs(char* input_name , char* n1 , char* n2 , char* v_n , complex<double> vFK)
        {
            element(input_name , n1 , n2 , vFK);

            vname = v_n;
        }

};
#endif
