

#ifndef DIODE_DEVICE_H
#define DIODE_DEVICE_H

#include "./model/model_diode.h"

class DIODE_DEVICE : public default_model
{
    private:
        model_diode *diode;

    public:
        DIODE_DEVICE()
        {
            diode = new model_diode;
        }
        ~DIODE_DEVICE()
        {
            delete diode;
        }

        void traverse();
        void append( /*int type ,*/ char * name , char* n1 , char *n2, complex<double> v );
        type_node* organize_address( complex<double> **stamp , complex<double> *RHS , char_node **node_array , char_node **name_array , type_node* start)
        {
            type_node* tmp = diode -> organize_address(stamp , RHS , node_array , name_array , start);
            return tmp;
        }
};

#endif
