

#ifndef VSRC_DEVICE_H
#define VSRC_DEVICE_H

#include "./model/model_vsrc.h"

class VSRC_DEVICE : public default_model
{
    private:
        model_vsrc *vsrc;

    public:
        VSRC_DEVICE()
        {
            vsrc = new model_vsrc;
        }
        ~VSRC_DEVICE()
        {
            delete vsrc;
        }

        void traverse();
        void append( /*int type , */char * name , char* n1 , char *n2, complex<double> v );
        type_node* organize_address( complex<double> **stamp , complex<double> *RHS , char_node **node_array , char_node **name_array , type_node* start)
        {
            type_node* tmp = vsrc -> organize_address(stamp , RHS , node_array , name_array , start);
            return tmp;
        }
};

#endif
