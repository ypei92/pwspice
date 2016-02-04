

#ifndef CONT_CC_DEVICE_H
#define CONT_CC_DEVICE_H

#include "./model/model_cccs.h"
#include "./model/model_ccvs.h"

class CONT_CC_DEVICE : public default_model
{
    private:
        model_cccs *cccs;
        model_ccvs *ccvs;

    public:
        CONT_CC_DEVICE()
        {
            cccs = new model_cccs;
            ccvs = new model_ccvs;
        }
        ~CONT_CC_DEVICE()
        {
            delete cccs;
            delete ccvs;
        }

        void traverse();
        void append( char* name , char* n1 , char* n2 , char* vname , complex<double> v , int type );
        type_node* organize_address( complex<double> **stamp , complex<double> *RHS , char_node **node_array , char_node **name_array , type_node* start)
        {
            type_node* tmp;
            tmp = cccs -> organize_address(stamp , RHS , node_array , name_array , start);
            tmp = ccvs -> organize_address(stamp , RHS , node_array , name_array , tmp);
            return tmp;
        }
};



#endif
