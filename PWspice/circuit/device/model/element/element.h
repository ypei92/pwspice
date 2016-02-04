//element.h
//By PY&WYH
//2014.3.22

#ifndef element_h
#define element_h

#include <stdio.h>
#include <stdlib.h>
#include <complex>
//#include <iostream>
using namespace std;

class element
{
    public:
        char* element_name;
        char* node1;
        char* node2;

        complex<double> DC_value;

        element(){};
        element(char* input_name , char* n1 , char* n2 , complex<double> D_v)
        {
            element_name = input_name;
            node1 = n1 ;
            node2 = n2 ;

            DC_value = D_v;
        }
         ~element(){}
};

#endif
