

#ifndef IND_DEVICE_H
#define IND_DEVICE_H

#include "./model/model_ind.h"

class IND_DEVICE : public default_model
{
    private:
        model_ind *c_ind;

    public:
        IND_DEVICE()
        {
            c_ind = new model_ind;
        }
        ~IND_DEVICE()
        {
            delete c_ind;
        }

        void traverse();
        void append( /*int type , */char * name , char* n1 , char *n2, complex<double> v, complex<double> v_init = 0 );
        type_node* organize_address( complex<double> **stamp , complex<double> *RHS , char_node **node_array , char_node **name_array , type_node* start)
        {
            type_node* tmp = c_ind -> organize_address(stamp , RHS , node_array , name_array , start);
            return tmp;
        }
};
#endif
