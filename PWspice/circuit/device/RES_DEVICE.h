

#ifndef RES_DEVICE_H
#define RES_DEVICE_H

#include "./model/model_res_linear.h"

class RES_DEVICE : public default_model
{
    private:
        model_res_linear *l_res;

    public:
        RES_DEVICE()
        {
            l_res = new model_res_linear;
        }
        ~RES_DEVICE()
        {
            delete l_res;
        }

        void traverse();
        void append( /*int type ,*/ char * name , char* n1 , char *n2, complex<double> v );
        type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start )
        {
            type_node* tmp = l_res -> organize_address(stamp , RHS , node_array , name_array , start);
            return tmp;
        }
};

#endif
