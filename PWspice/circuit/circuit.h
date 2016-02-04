#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "./device/CAP_DEVICE.h"
#include "./device/IND_DEVICE.h"
#include "./device/RES_DEVICE.h"
#include "./device/VSRC_DEVICE.h"
#include "./device/ISRC_DEVICE.h"
#include "./device/MOS_DEVICE.h"
#include "./device/DIODE_DEVICE.h"
#include "./device/CONT_CC_DEVICE.h"
#include "./device/CONT_VC_DEVICE.h"

class circuit : public default_model
{
    private:
        complex<double> **stamp;
        complex<double> *RHS;
        complex<double> *current_ans;
        complex<double> *previous_ans;
        complex<double> **dc_result;


        int stamp_size;
        int branch_size;
        int node_table_size;
        int name_table_size;

        RES_DEVICE *device_res_head;
        CAP_DEVICE *device_cap_head;
        IND_DEVICE *device_ind_head;
        MOS_DEVICE *device_mos_head;
        VSRC_DEVICE *device_vsrc_head;
        ISRC_DEVICE *device_isrc_head;
        DIODE_DEVICE *device_diode_head;
        CONT_CC_DEVICE *device_cont_cc_head;
        CONT_VC_DEVICE *device_cont_vc_head;

        char_node **node_array;
        char_node **name_array;
        type_node *address_structure_head;
        type_node *iter_start_diode;
        type_node *iter_start_mos;


        void res_iter( type_node *p );
        void cap_iter_dc( type_node *p );
        void cap_iter_tran( type_node *p , complex<double> *v , complex<double> h , int times);
        void cap_iter_ac( type_node *p , complex<double> f , complex<double> * dc_solution);
        void ind_iter_dc( type_node *p );
        void ind_iter_tran( type_node *p , complex<double> *v , complex<double> h , int times);
        void ind_iter_ac( type_node *p , complex<double> f , complex<double> * dc_solution);
        void cccs_iter( type_node *p);
        void ccvs_iter( type_node *p);
        void vccs_iter( type_node *p);
        void vcvs_iter( type_node *p);
        void vsrc_iter( type_node *p);
        void vsrc_iter_dc( type_node *p, complex<double> value);
        void vsrc_iter_ac( type_node *p, complex<double> value);
        void isrc_iter( type_node *p);
        void isrc_iter_dc( type_node *p, complex<double> value);
        void isrc_iter_ac( type_node *p, complex<double> value);
        void diode_iter( type_node *p , complex<double> *v );
        void diode_iter_ac( type_node *p , complex<double> *v );
        void mos_iter(type_node *p , complex<double> *v );
        void mos_iter_ac(type_node *p , complex<double> *v1);


    public:
        circuit();
        ~circuit();

        void traverse();
        void append_node_array(char * node );
        void append_name_array(char * name , bool is_branch = false );
        void organize_address();

        void initial_RHS_dc();
        void initial_stamp_dc();

        complex<double> diode_g0( complex<double> a , complex<double> co);
        complex<double> diode_i0( complex<double> a , complex<double> co);

        complex<double> mos_Ids(int type , complex<double> vd , complex<double> vg , complex<double> vs , complex<double> w , complex<double> l , mos_model m);
        complex<double> mos_Gds(int type , complex<double> vd , complex<double> vg , complex<double> vs , complex<double> w , complex<double> l , mos_model m);
        complex<double> mos_Gm (int type , complex<double> vd , complex<double> vg , complex<double> vs , complex<double> w , complex<double> l , mos_model m);
        complex<double> mos_I0 (int type , complex<double> vd , complex<double> vg , complex<double> vs , complex<double> w , complex<double> l , mos_model m);

        void branch_arrange();
        void display_char_node();

        bool judge_iter_end( complex<double> *v , complex<double> *v_pre , int n );
        //complex<double>* exchange_v( complex<double> *v , complex<double> *v_pre , int n );
        void exchange_v();

        void append_RES_DEVICE(  char* name , char* n1 , char* n2 , complex<double> v /*, int type*/);
        void append_CAP_DEVICE(  char* name , char* n1 , char* n2 , complex<double> v , complex<double> v_init = 0 /*, int type*/);
        void append_IND_DEVICE(  char* name , char* n1 , char* n2 , complex<double> v , complex<double> v_init = 0 /*, int type*/);
        void append_MOS_DEVICE(  char* name , char* n1 , char* n2 , char* n3 , char* type , complex<double> w , complex<double> l );
        void append_VSRC_DEVICE( char* name , char* n1 , char* n2 , complex<double> v /*, int type*/);
        void append_ISRC_DEVICE( char* name , char* n1 , char* n2 , complex<double> v /*, int type*/);
        void append_DIODE_DEVICE(char* name , char* n1 , char* n2 , complex<double> v /*, int type*/);
        void append_CONT_CC_DEVICE( char* name , char* n1 , char* n2 , char* vname , complex<double> v , int type);
        void append_CONT_VC_DEVICE( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v , int type);

        void do_iter();
        void do_iter_dc(type_node *pp, complex<double> current_value);
        void do_iter_tran(complex<double> h, int times, complex<double> * last_result);
        void do_iter_ac(type_node *pp, complex<double> current_value , complex<double> * dc_solution);
        bool dc_simulation(char * name, complex<double> start, complex<double> end, complex<double> step);
        bool tran_simulation(complex<double> h, complex<double> total_time);
        bool ac_simulation(char * name, complex<double> start, complex<double> end, complex<double> step);

        char** return_name( int &c);
};

#endif
