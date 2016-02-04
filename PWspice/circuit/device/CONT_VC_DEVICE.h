

#ifndef CONT_VC_DEVICE_H
#define CONT_VC_DEVICE_H

#include "./model/model_vccs.h"
#include "./model/model_vcvs.h"

class CONT_VC_DEVICE : public default_model
{
    private:
        model_vccs *vccs;
        model_vcvs *vcvs;

    public:
        CONT_VC_DEVICE()
        {
            vccs = new model_vccs;
            vcvs = new model_vcvs;
        }
        ~CONT_VC_DEVICE()
        {
            delete vccs;
            delete vcvs;
        }

        void traverse();
        void append( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v , int type );
        type_node* organize_address( complex<double> **stamp , complex<double> *RHS , char_node **node_array , char_node **name_array , type_node* start)
        {
            type_node* tmp;
            tmp = vccs -> organize_address(stamp , RHS , node_array , name_array , start);
            tmp = vcvs -> organize_address(stamp , RHS , node_array , name_array , tmp);
            return tmp;
        }
};


#endif
