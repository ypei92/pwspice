

#ifndef ISRC_DEVICE_H
#define ISRC_DEVICE_H

#include "./model/model_isrc.h"

class ISRC_DEVICE : public default_model
{
    private:
        model_isrc *isrc;

    public:
        ISRC_DEVICE()
        {
            isrc = new model_isrc;
        }
        ~ISRC_DEVICE()
        {
            delete isrc;
        }

        void traverse();
        void append( /*int type , */char * name , char* n1 , char *n2, complex<double> v );
        type_node* organize_address( complex<double> **stamp , complex<double> *RHS , char_node **node_array , char_node **name_array , type_node* start)
        {
            type_node* tmp = isrc -> organize_address(stamp , RHS , node_array , name_array , start);
            return tmp;
        }
};

#endif
