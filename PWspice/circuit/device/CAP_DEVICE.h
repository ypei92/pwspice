

#ifndef CAP_DEVICE_H
#define CAP_DEVICE_H

#include "./model/model_cap.h"

class CAP_DEVICE : public default_model
{
    private:
        model_cap *c_cap;

    public:
        CAP_DEVICE()
        {
            c_cap = new model_cap;
        }
        ~CAP_DEVICE()
        {
            delete c_cap;
        }

        void traverse();
        void append( /*int type , */char * name , char* n1 , char *n2, complex<double> v, complex<double> v_init = 0 );

        type_node* organize_address( complex<double> **stamp , complex<double> *RHS , char_node **node_array , char_node **name_array ,  type_node* start)
        {
            type_node* tmp = c_cap -> organize_address(stamp , RHS , node_array , name_array , start);
            return tmp;
        }
};






#endif

