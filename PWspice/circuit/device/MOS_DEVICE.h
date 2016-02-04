

#ifndef MOS_DEVICE_H
#define MOS_DEVICE_H

#include "./model/model_pmos.h"
#include "./model/model_nmos.h"

class MOS_DEVICE : public default_model
{
    private:
        model_pmos *pmos;
        model_nmos *nmos;

    public:
        MOS_DEVICE()
        {
            pmos = new model_pmos;
            nmos = new model_nmos;
        }
        ~MOS_DEVICE()
        {
            delete pmos;
            delete nmos;
        }

        void traverse();
        void append( char * name , char* n1 , char *n2 , char* n3 , int type , complex<double> w , complex<double> l );
        type_node* organize_address( complex<double> **stamp , complex<double> *RHS , char_node **node_array , char_node **name_array , type_node* start)
        {
            type_node* tmp;
            tmp = nmos -> organize_address(stamp , RHS , node_array , name_array , start);
            tmp = pmos -> organize_address(stamp , RHS , node_array , name_array , tmp);
            return tmp;
        }
};

#endif
