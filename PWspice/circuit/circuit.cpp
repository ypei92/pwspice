//The cpp for circuit.h

#include "circuit.h"
#include "mySolver.h"
#include <iomanip>
#include <fstream>

circuit :: circuit()
{
    device_res_head = new RES_DEVICE;
    device_cap_head = new CAP_DEVICE;
    device_ind_head = new IND_DEVICE;
    device_mos_head = new MOS_DEVICE;
    device_vsrc_head = new VSRC_DEVICE;
    device_isrc_head = new ISRC_DEVICE;
    device_diode_head = new DIODE_DEVICE;
    device_cont_cc_head = new CONT_CC_DEVICE;
    device_cont_vc_head = new CONT_VC_DEVICE;

    stamp_size = 0;
    branch_size = 0;
    node_table_size = 1;
    name_table_size = 0;

    name_array = new char_node*[255];
    node_array = new char_node*[255];
    address_structure_head = new type_node;
    //address_structure_head -> next = NULL;

    for( int i = 0 ; i < 255 ; ++i)
    {
        name_array[i] = new char_node;
        node_array[i] = new char_node;
    }

    char *tmp_0 = new char[2];
    tmp_0[0] = '0';
    tmp_0[1] = '\0';

    char_node *tmp = new char_node( tmp_0 , 0 );
    node_array[ 48 ] -> next = tmp;
}

circuit :: ~circuit()
{
    delete device_cap_head;
    delete device_diode_head;
    delete device_ind_head;
    delete device_isrc_head;
    delete device_mos_head;
    delete device_res_head;
    delete device_vsrc_head;
    delete device_cont_cc_head;
    delete device_cont_vc_head;

    for(int i = 0 ; i < 255 ; ++i)
    {
        char_node *q , *p = node_array[i] -> next;
        char_node *s , *t = name_array[i] -> next;

        while(p != NULL)
        {
            q = p;
            p = p -> next;
            delete q;
        }
        node_array[i] -> next = NULL ;

        while( t != NULL)
        {
            s = t;
            t = t -> next;
            delete s;
        }
        name_array[i] -> next = NULL ;

        //delete[] stamp[i];
    }

    for( int i = 0 ; i < stamp_size - 1 ; ++i) delete[] stamp[i];

    delete[] node_array;
    delete[] name_array;
    delete[] stamp;
    delete[] RHS;
    delete[] current_ans;
}



void circuit :: append_RES_DEVICE(  char* name , char* n1 , char* n2 , complex<double> v /*, int type*/)
{
    device_res_head -> append( name , n1 , n2 , v);
    append_name_array(name);
    append_node_array(n1);
    append_node_array(n2);
    return;
}

void circuit :: append_CAP_DEVICE(  char* name , char* n1 , char* n2 , complex<double> v , complex<double> v_init/*, int type*/)
{
    device_cap_head -> append( name , n1 , n2 , v , v_init);
    append_name_array(name);
    append_node_array(n1);
    append_node_array(n2);
    return;
}

void circuit :: append_IND_DEVICE(  char* name , char* n1 , char* n2 , complex<double> v , complex<double> v_init/*, int type*/)
{
    device_ind_head -> append( name , n1 , n2 , v , v_init);
    append_name_array(name , true);
    append_node_array(n1);
    append_node_array(n2);
    //++branch_size;
    return;
}

void circuit :: append_MOS_DEVICE(  char* name , char* n1 , char* n2 , char* n3 , char* type , complex<double> w , complex<double> l )
{
    int n_or_p = -1;
    if( type[0] == 'n' || type[0] == 'N' ) n_or_p = 0;
    if( type[0] == 'p' || type[0] == 'P' ) n_or_p = 1;
    device_mos_head -> append( name , n1 , n2 , n3 , n_or_p , w , l);
    append_name_array(name);
    append_node_array(n1);
    append_node_array(n2);
    append_node_array(n3);
    return;
}

void circuit :: append_VSRC_DEVICE( char* name , char* n1 , char* n2 , complex<double> v /*, int type*/)
{
    device_vsrc_head -> append( name , n1 , n2 , v);
    append_name_array(name , true);
    append_node_array(n1);
    append_node_array(n2);
    //++branch_size;
    return;
}

void circuit :: append_ISRC_DEVICE( char* name , char* n1 , char* n2 , complex<double> v /*, int type*/)
{
    device_isrc_head -> append( name , n1 , n2 , v);
    append_name_array(name);
    append_node_array(n1);
    append_node_array(n2);
    return;
}

void circuit :: append_DIODE_DEVICE(char* name , char* n1 , char* n2 , complex<double> v /*, int type*/)
{
    device_diode_head -> append( name , n1 , n2 , v);
    append_name_array(name);
    append_node_array(n1);
    append_node_array(n2);
    return;
}

void circuit :: append_CONT_CC_DEVICE( char* name , char* n1 , char* n2 , char* vname , complex<double> v , int type)
{
    device_cont_cc_head -> append( name , n1 , n2 , vname , v , type);
    if( type == 0 ) append_name_array(name , false);
    if( type == 1 ) append_name_array(name , true);
    //append_name_array(vname, true);
    append_node_array(n1);
    append_node_array(n2);
    return;
}

void circuit :: append_CONT_VC_DEVICE( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v , int type)
{
    device_cont_vc_head -> append( name , n1 , n2 , n1c , n2c , v , type);
    if( type == 1) append_name_array(name , true);
    else append_name_array(name, false);
    append_node_array(n1);
    append_node_array(n2);
    append_node_array(n1c);
    append_node_array(n2c);

    return;
}






//-------------------------------------organize_address()------------------------------
void circuit :: organize_address()
{
    int i ;
    branch_arrange();

    stamp_size = node_table_size + branch_size;
    RHS = new complex<double>[stamp_size - 1];
    current_ans = new complex<double>[stamp_size - 1];
    previous_ans= new complex<double>[stamp_size - 1];
    stamp = new complex<double>*[stamp_size - 1];
    for( i = 0 ; i < stamp_size - 1 ; ++i)
    {
        RHS[i] = 0;
        current_ans[i] = 0;
        previous_ans[i] = 0;
        stamp[i] = new complex<double>[stamp_size - 1];
        for(int j = 0 ; j < stamp_size - 1 ; ++j) stamp[i][j] = 0;
    }


    //int branch_start  = node_table_size - 1;
    type_node *p = address_structure_head;

    p = device_res_head -> organize_address( stamp , RHS , node_array , name_array , p);
    p = device_cap_head -> organize_address( stamp , RHS , node_array , name_array , p);
    p = device_ind_head -> organize_address( stamp , RHS , node_array , name_array , p);
    p = device_vsrc_head-> organize_address( stamp , RHS , node_array , name_array , p);
    p = device_isrc_head-> organize_address( stamp , RHS , node_array , name_array , p);

    p = device_cont_cc_head -> organize_address( stamp , RHS , node_array , name_array , p);
    p = device_cont_vc_head -> organize_address( stamp , RHS , node_array , name_array , p);

    iter_start_diode = p ;
    p = device_diode_head -> organize_address( stamp , RHS , node_array , name_array , p);
    iter_start_diode = iter_start_diode -> next;

    iter_start_mos = p ;
    p = device_mos_head   -> organize_address( stamp , RHS , node_array , name_array , p);
    iter_start_mos = iter_start_mos -> next;

    initial_stamp_dc();
    initial_RHS_dc();

    /*bool yorn = */mySolve( stamp_size - 1 , stamp, RHS, current_ans);


//    cout << "The Stamp is :" << endl;
//    for( i = 0 ; i < stamp_size - 1 ; ++i )
//    {
//        for( int j = 0 ; j < stamp_size - 1 ; ++j) cout << stamp[i][j] << '\t';
//        cout << ' ' << ' ' <<  RHS[i] << endl;
//    }
//    cout << endl;
//
//    cout << "current_ans" << endl;
//    for( i = 0 ; i < stamp_size - 1 ; ++i) cout << current_ans[i] << endl;

}

//-----------------------------------------Initial stamp dc-------------------------------
void circuit :: initial_stamp_dc()
{
    int i = 0;
    complex<double> Gds , Gm;
    type_node *p = address_structure_head -> next;

    while( p != NULL && p -> type < 10 )
    {
        address_node *s = p -> head -> next;
        while( s != NULL)
        {
            *(s -> address) += s -> value;
            s = s -> next;
        }
        p = p -> next;
    }
    //cout << " p -> type" <<  p -> type << endl;
    while( p != NULL && p -> type < 11)
    {
        address_node *s = p -> head -> next;

        complex<double> tmp = diode_g0( 0 , s -> value);
        while( s != NULL)
        {
            *(s -> address) += tmp * s -> value2;
            s = s -> next;
        }
        p = p -> next;
    }

    while( p != NULL )
    {
        i = 0;
        address_node *s = p -> head -> next;
        int type = p -> type - 11;
        //cout<<"123456"<<p->type<<endl;

        if (type == 0)
        {
            Gds = mos_Gds( type , 0 , 1 , 0 , s -> value , s -> value2 , nmos0_parameter);
            Gm  = mos_Gm ( type , 0 , 1 , 0 , s -> value , s -> value2 , nmos0_parameter);
        }
        else
        {
            Gds = mos_Gds( type , 0 , -1 , 0 , s -> value , s -> value2 , pmos0_parameter);
            Gm  = mos_Gm ( type , 0 , -1 , 0 , s -> value , s -> value2 , pmos0_parameter);
        }
        //cout<<"initializing: Gds="<<Gds<<" Gm="<<Gm<<endl;

        if( s -> address != NULL) *(s -> address) +=  Gds ;       s = s -> next;
        if( s -> address != NULL) *(s -> address) += -Gds - Gm ;  s = s -> next;
        if( s -> address != NULL) *(s -> address) +=  Gm  ;       s = s -> next;
        if( s -> address != NULL) *(s -> address) += -Gds ;       s = s -> next;
        if( s -> address != NULL) *(s -> address) +=  Gds + Gm ;  s = s -> next;
        if( s -> address != NULL) *(s -> address) += -Gm  ;

        p = p -> next;
    }
}
//---------------------------------------------Initial RHS DC-----------------------------
void circuit :: initial_RHS_dc()
{
    complex<double> rhs_mos_i0;

    type_node *p = address_structure_head -> next;

    while( p != NULL && p -> type < 10 )
    {
        address_node *s = p -> rhs_head -> next;
        while( s != NULL)
        {
            if( p -> type == 2 || p -> type == 3) *(s -> address) += s->value*s->value2;
            else *(s -> address) += s -> value;
            s = s -> next;
        }
        p = p -> next;
    }

    while( p != NULL && p -> type < 11)
    {
        address_node *s = p -> rhs_head -> next;

        complex<double> tmp = diode_i0( 0 , s -> value);
        while( s != NULL)
        {
            *(s -> address) += tmp * s -> value2;
            s = s -> next;
        }
        p = p -> next;
    }

    while( p != NULL)
    {
        address_node *s = p -> rhs_head -> next;

        int type = p -> type - 11;
        //cout<<p->type;
        if (type == 0)
        {
            rhs_mos_i0 = mos_I0( type , 0 , 1 , 0 , s -> value , s -> value2 , nmos0_parameter);
        }
        else
        {
            rhs_mos_i0 = mos_I0( type , 0 , -1 , 0 , s -> value , s -> value2 , pmos0_parameter);
        }

        if( s -> address != NULL) *(s -> address) += -rhs_mos_i0; s = s -> next;
        if( s -> address != NULL) *(s -> address) +=  rhs_mos_i0;

        p = p -> next;
    }

}

//-------------------------------------append_node_array-------------------------------
void circuit :: append_node_array(char * node)
{
    if( strcmp( node , "0") == 0)return;

    int location = hash( node , 255);

    char_node *p = node_array[location];
    while (p -> next != NULL)
    {
        if(p != node_array[location] && strcmp(p -> name , node) == 0) break;
        p = p -> next;
    }


    if( p != node_array[location] && strcmp(p -> name , node) == 0 ) return;

    char_node *tmp = new char_node( node , node_table_size );
    p -> next = tmp;

    ++node_table_size;
    /*cout <<" node_size:" <<node_table_size << endl;*/
}

//-------------------------------------append_name_array-------------------------------
void circuit :: append_name_array(char * name , bool if_branch)
{
    int location = hash( name , 255);

    char_node *p =name_array[location];
    while (p -> next != NULL)
    {
        if(p != name_array[location] && strcmp(p -> name , name) == 0) break;
        p = p -> next;
    }

    if( p != name_array[location] && strcmp(p -> name , name) == 0 ) return;

    int a = (if_branch)? branch_size : -1;

    char_node *tmp = new char_node( name , a );
    p -> next = tmp;

    if(if_branch) ++branch_size;
    ++name_table_size;
    /*cout <<" name_size: " << name_table_size << endl;*/
    /*cout <<" branch_size: " << branch_size << endl;*/
}

//---------------------------------for right branch_number---------------------------
void circuit :: branch_arrange()
{
    for( int i = 0 ; i < 255 ; ++i)
    {
        char_node *p = name_array[i] -> next;
        while( p != NULL)
        {
            if( p -> name_id != -1 ) p -> name_id += node_table_size;
            p = p -> next;
        }
    }
}


//-------------------------------Thte g0 and i0 of diode----------------------------------
complex<double> circuit :: diode_g0(complex<double> a , complex<double> co)
{
    return 0.001 * co * exp( co * a);
}

complex<double> circuit :: diode_i0(complex<double> a , complex<double> co)
{
    complex<double> tmp = diode_g0(a , co) * a;
    return tmp + 0.001*(1.0 - exp( co * a));
}
//--------------------------------The calculation of Gds Gm I0-----------------------------
complex<double> circuit :: mos_Ids(int type , complex<double> vd , complex<double> vg , complex<double> vs , complex<double> w , complex<double> l , mos_model m)
{
    complex<double> k = w/l*m.Cox*m.mobility;
    complex<double> tmp;
    complex<double> vov,vds,vgs;
    bool direction = (real(vd) >= real(vs));

    if (direction==true)
    {
        vds = vd - vs;
        if (type == 0) vgs = vg - vs;
        else vgs = vg - vd;
    }
    else
    {
        vds = vs - vd;
        if (type == 0) vgs = vg - vd;
        else vgs = vg - vs;
    }

    if (type == 0) vov = vgs - m.threshold;
    else vov = m.threshold - vgs;

    if (real(vov) <= 0)
    {
        tmp = 0;
    }
    else if (real(vds) <= real(vov))
    {
        tmp = k*(vov*vds - 0.5*vds*vds)*(1.0+m.lambda*vds);
    }
    else
    {
        tmp = k*0.5*vov*vov*(1.0+m.lambda*vds);
    }
    //cout<<"vov="<<vov<<" vds="<<vds<<endl;
    return (direction==true) ? tmp : -tmp;
}
complex<double> circuit :: mos_Gds(int type , complex<double> vd , complex<double> vg , complex<double> vs , complex<double> w , complex<double> l , mos_model m)
{
    //complex<double> h = 1e-13;
    complex<double> h = 0.00000001;
    complex<double> Ids2 = mos_Ids(type , vd+h , vg , vs , w , l , m);
    complex<double> Ids1 = mos_Ids(type , vd , vg , vs , w , l , m);
    return (Ids2 - Ids1)/h;
}
complex<double> circuit :: mos_Gm(int type , complex<double> vd , complex<double> vg , complex<double> vs , complex<double> w , complex<double> l , mos_model m)
{
    //complex<double> h = 1e-13;
    complex<double> h = 0.00000001;
    complex<double> Ids2 = mos_Ids(type , vd , vg+h , vs , w , l , m);
    complex<double> Ids1 = mos_Ids(type , vd , vg , vs , w , l , m);
    return (Ids2 - Ids1)/h;
}
complex<double> circuit :: mos_I0(int type , complex<double> vd , complex<double> vg , complex<double> vs , complex<double> w , complex<double> l , mos_model m)
{
    complex<double> tmp = mos_Ids(type , vd , vg , vs , w , l , m);
    //cout<<"Ids="<<tmp<<endl;
    tmp -= (vd - vs) * mos_Gds(type , vd , vg , vs , w , l , m);
    tmp -= (vg - vs) * mos_Gm(type , vd , vg , vs , w , l , m);
    return tmp;
}

//---------------------------------Judge whether the iteration should be end----------------------
bool circuit :: judge_iter_end( complex<double> *v , complex<double> *v_pre , int n)
{
    complex<double> tmp0 , tmp1 ;
    int i ;
    bool flag = true;

    //cout<<"judge:"<<endl;
    for( i = 0 ; i < n ; ++i)
    {
        //cout<<"v:"<<v[i]<<"    v_pre:"<<v_pre[i]<<endl;
        tmp0 = abs(v[i] - v_pre[i]);
        tmp1 = 0.000001 + 0.00000001 * abs(v_pre[i]);
        if( (abs(tmp0) - abs(tmp1)) > 0)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

//-------------------------------exchange the value of v and v_pre--------------------------------
//complex<double>* circuit :: exchange_v( complex<double> *v , complex<double> *v_pre , int n )
void circuit :: exchange_v()
{
    int i;
    for( i=0 ; i < stamp_size -1 ;++i) previous_ans[i] = current_ans[i];
    //return v_pre;
}

/*
//-------------------------------iter_step--------------------------------------------------------
void circuit :: cap_iter( type_node *p , complex<double> *v , complex<double> *v_pre)
{
    node_num_node *t = p -> node_num_head -> next;
    address_node *s = p ->rhs_head -> next;

    int n1 = t ->node_num;
    int n2 = t ->next ->node_num;

    complex<double> v_tmp = ((n1 == -1)? 0 : v[n1]) - ((n2 == -1)?0 : v[n2]);
    complex<double> v_tmp_pre = ((n1 == -1)? 0 : v_pre[n1]) - ((n2 == -1)?0 : v_pre[n2]);
    while( s != NULL)
    {
        *(s -> address) += s -> value * (v_tmp - v_tmp_pre);
        s = s -> next;
    }
}
void circuit :: ind_iter( type_node *p , complex<double> *v , complex<double> *v_pre)
{
    address_node *s = p -> rhs_head -> next;
    int branch_n = p -> node_num_head -> next ->node_num;

    complex<double> i_tmp = v[branch_n];
    complex<double> i_tmp_pre = v_pre[branch_n];
    *( s -> address) += s -> value * (i_tmp - i_tmp_pre);
}


void circuit :: diode_iter( type_node *p , complex<double> *v , complex<double> *v_pre)
{
    node_num_node *t = p -> node_num_head -> next;
    int n1 = t ->node_num;
    int n2 = t ->next ->node_num;

    complex<double> v_tmp = ((n1 == -1)? 0 : v[n1]) - ((n2 == -1)?0 : v[n2]);
    complex<double> v_tmp_pre = ((n1 == -1)? 0 : v_pre[n1]) - ((n2 == -1)?0 : v_pre[n2]);

    address_node *w = p -> rhs_head -> next;
    address_node *u = p -> head -> next;

    complex<double> tmp_g0 , tmp_i0 , tmp_g0_pre , tmp_i0_pre;
    tmp_g0 = diode_g0( v_tmp , u -> value);
    tmp_i0 = diode_i0( v_tmp , u -> value);
    tmp_g0_pre = diode_g0( v_tmp_pre , u -> value);
    tmp_i0_pre = diode_i0( v_tmp_pre , u -> value);
    cout<<"parameters:"<<endl;
    cout<<"tmp_g0="<<tmp_g0<<endl;
    cout<<"tmp_i0="<<tmp_i0<<endl;
    cout<<"tmp_g0_pre="<<tmp_g0_pre<<endl;
    cout<<"tmp_i0_pre="<<tmp_i0_pre<<endl;


    while( u != NULL )
    {
        *( u -> address) += (tmp_g0 - tmp_g0_pre) * u -> value2;
        u = u -> next;
    }

    while( w != NULL )
    {
        *( w -> address) += (tmp_i0 - tmp_i0_pre) * w -> value2;
        w = w -> next;
    }
}

void circuit :: mos_iter(type_node *p , complex<double> *v , complex<double> *v_pre)
{
    node_num_node *t = p -> node_num_head -> next;
    int nd = t ->node_num;
    int ng = t ->next ->node_num;
    int ns = t ->next ->next->node_num;


    complex<double> vd = ((nd == -1)? 0 : v[nd]);
    complex<double> vg = ((ng == -1)? 0 : v[ng]);
    complex<double> vs = ((ns == -1)? 0 : v[ns]);
    complex<double> vd_pre = ((nd == -1)? 0 : v_pre[nd]);
    complex<double> vg_pre = ((ng == -1)? 0 : v_pre[ng]);
    complex<double> vs_pre = ((ns == -1)? 0 : v_pre[ns]);

    int type = p->type - 11;
    address_node *u = p -> head -> next;
    address_node *w = p -> rhs_head -> next;

    complex<double> Gds = mos_Gds( type , vd , vg , vs , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);
    complex<double> Gm  = mos_Gm ( type , vd , vg , vs , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);
    complex<double> I0  = mos_I0 ( type , vd , vg , vs , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);

    complex<double> Gds_pre = mos_Gds( type , vd_pre , vg_pre , vs_pre , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);
    complex<double> Gm_pre  = mos_Gm ( type , vd_pre , vg_pre , vs_pre , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);
    complex<double> I0_pre  = mos_I0 ( type , vd_pre , vg_pre , vs_pre , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);


    if( u -> address != NULL) *(u -> address) +=  Gds - Gds_pre ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) += -Gds - Gm + Gds_pre + Gm_pre;  u = u -> next;
    if( u -> address != NULL) *(u -> address) +=  Gm  - Gm_pre  ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) += -Gds + Gds_pre ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) +=  Gds + Gm - Gds_pre - Gm_pre;  u = u -> next;
    if( u -> address != NULL) *(u -> address) += -Gm  + Gm_pre ;

    if( w -> address != NULL) *(w -> address) += -I0 + I0_pre ; w = w -> next;
    if( w -> address != NULL) *(w -> address) +=  I0 - I0_pre;
}

*/

//------------------------traverse----------------------------------
void circuit::traverse()
{
    device_res_head -> traverse();
    device_cap_head -> traverse();
    device_ind_head -> traverse();
    device_vsrc_head -> traverse();
    device_isrc_head -> traverse();
    device_mos_head -> traverse();
    device_cont_cc_head -> traverse();
    device_cont_vc_head -> traverse();
    device_diode_head -> traverse();
}

//------------------------------------display_char_node-------------------------------
void circuit :: display_char_node()
{
    cout << "name_array" << endl;
    for( int i = 0 ; i < 255 ; ++i)
    {
        char_node *p = name_array[i] -> next;
        if( p == NULL) continue;
        while( p != NULL)
        {
            cout << p -> name <<' ' << p -> name_id << "-> \t";
            p = p -> next;
        }
        cout << endl;
    }

    cout << "node_array" << endl;
    for( int i = 0 ; i < 255 ; ++i)
    {
        char_node *p = node_array[i] -> next;
        if( p == NULL) continue;
        while( p != NULL)
        {
            cout << p -> name <<' ' << p -> name_id << "-> \t";
            p = p -> next;
        }
        cout << endl;
    }

    cout << "address_structure" << endl;
    type_node *q = address_structure_head -> next;
    while( q != NULL)
    {
        cout << "type = " << q -> type << '\t' ;
        address_node *s = q -> head -> next;
        address_node *t = q ->rhs_head -> next;
        cout << "value = ";
        while( s != NULL)
        {
            cout << s -> value << '\t';
        //  cout << s -> address;
            s = s -> next;
        }
        cout << endl;
        cout << "RHS =        ";
        while( t != NULL)
        {
            cout << t -> value << '\t';
        //  cout << s -> address;
            t = t -> next;
        }
        cout << endl;
        q = q -> next;
    }
}

//-------------------------------------------------ITER_FOR_EVERY_TYPE----------------------------------------------
void circuit :: res_iter( type_node *p )
{
    address_node *s = p -> head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
}

void circuit :: cap_iter_dc( type_node *p )
{
//    address_node *s = p -> head -> next;
//    address_node *t = p -> rhs_head -> next;
//    while( s != NULL)
//    {
//        *(s -> address) += s -> value;
//        s = s -> next;
//    }
//    while( t != NULL)
//    {
//        *(t -> address) += t -> value;
//        t = t -> next;
//    }
}
void circuit :: cap_iter_tran( type_node *p , complex<double> *v , complex<double> h ,int times)
{
    complex<double> significant_small=0.0000000000000000001;
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    node_num_node *q = p->node_num_head->next;
    int n1 = q->node_num;
    int n2 = q->next->node_num;
    complex<double> v_pre;
    if (n1 == 0) v_pre = 0.0 - v[n2];
    else if (n2 == 0) v_pre = v[n1];
    else v_pre = v[n1] - v[n2];
    if (times == 0)
    {
        while( s != NULL)
        {
            *(s -> address) += s -> value / significant_small;
            //cout<<s->value<<endl;
            s = s -> next;
        }
        while( t != NULL)
        {
            *(t -> address) += t -> value * t -> value2 / significant_small;
            //cout<<t->value<<endl;
            t = t -> next;
        }
    }
    else
    {
        while( s != NULL)
        {
            *(s -> address) += s -> value / h;
            //cout<<s->value<<endl;
            s = s -> next;
        }
        while( t != NULL)
        {
            *(t -> address) += t -> value * v_pre / h;
            //cout<<t->value<<endl;
            t = t -> next;
        }
    }
}
void circuit :: cap_iter_ac( type_node *p , complex<double> f , complex<double> * dc_solution)
{
    complex<double> pi = 3.1415926535897932384626;
    complex<double> i(0,1);
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;

    node_num_node *q = p->node_num_head->next;
    int n1 = q->node_num;
    int n2 = q->next->node_num;
    complex<double> v_dc;
    if (n1 == 0) v_dc = 0.0 - dc_solution[n2];
    else if (n2 == 0) v_dc = dc_solution[n1];
    else v_dc = dc_solution[n1] - dc_solution[n2];

    while( s != NULL)
    {
        *(s -> address) += s -> value * f * 2.0 * pi * i;
        s = s -> next;
    }
    while( t != NULL)
    {
        *(t -> address) += t -> value * v_dc;
        t = t -> next;
    }
}
void circuit :: ind_iter_dc( type_node *p )
{
    address_node *s = p -> head ;
//   address_node *t = p -> rhs_head -> next;
    while( s->next != NULL)
    {
        s = s -> next;
        if (s->next != NULL) *(s -> address) += s -> value;
    }
}
void circuit :: ind_iter_tran( type_node *p , complex<double> *v , complex<double> h , int times)
{
    complex<double> significant_small=0.0000000000000000001;
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    node_num_node *q = p->node_num_head->next;
    int n = q->node_num;

    if (times == 0)
    {
        while( s != NULL)
        {
            if (s->next != NULL) *(s -> address) += s -> value;
            else *(s -> address) += s -> value / significant_small;
            s = s -> next;
        }
        while( t != NULL)
        {
            *(t -> address) += t -> value * t -> value2 / significant_small;
            t = t -> next;
        }
    }
    else
    {
        while( s != NULL)
        {
            if (s->next != NULL) *(s -> address) += s -> value;
            else *(s -> address) += s -> value / h;
            s = s -> next;
        }
        while( t != NULL)
        {
            *(t -> address) += t -> value * v[n] / h;
            t = t -> next;
        }
    }

//    while( s != NULL)
//    {
//        *(s -> address) += s -> value;
//        cout<<s -> value<<endl;
//        s = s -> next;
//    }
//    while( t != NULL)
//    {
//        *(t -> address) += t -> value;
//        cout<<t -> value2<<endl;
//        t = t -> next;
//    }
}
void circuit :: ind_iter_ac( type_node *p , complex<double> f , complex<double> * dc_solution)
{
    complex<double> pi = 3.1415926535897932384626;
    complex<double> i(0,1);
    address_node *s = p -> head -> next ;
    address_node *t = p -> rhs_head -> next;
    node_num_node *q = p->node_num_head->next;
    int n = q->node_num;
    //cout<<"---------------------"<<endl;
    while( s != NULL)
        {
            //cout<<s -> value<<endl;
            if (s->next != NULL) *(s -> address) += s -> value;
            else *(s -> address) += 1.0 * (s -> value * f * 2.0 * pi * i);
            s = s -> next;
        }
        while( t != NULL)
        {
            //cout<<-dc_solution[n]<<endl;
            *(t -> address) += dc_solution[n] * t -> value;
            //cout<<"t->value="<<t->value<<endl;
            t = t -> next;
        }
}
void circuit :: cccs_iter( type_node *p)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    while( t != NULL)
    {
        *(t -> address) += t -> value;
        t = t -> next;
    }
}
void circuit :: ccvs_iter( type_node *p)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    while( t != NULL)
    {
        *(t -> address) += t -> value;
        t = t -> next;
    }
}
void circuit :: vccs_iter( type_node *p)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    while( t != NULL)
    {
        *(t -> address) += t -> value;
        t = t -> next;
    }
}
void circuit :: vcvs_iter( type_node *p)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    while( t != NULL)
    {
        *(t -> address) += t -> value;
        t = t -> next;
    }
}
void circuit :: vsrc_iter( type_node *p)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    *(t -> address) += t -> value;
}
void circuit :: vsrc_iter_dc( type_node *p , complex<double> value)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    *(t -> address) += value;
}
void circuit :: vsrc_iter_ac( type_node *p , complex<double> value)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    *(t -> address) += value;
}
void circuit :: isrc_iter( type_node *p)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    while( t != NULL)
    {
        *(t -> address) += t -> value;
        t = t -> next;
    }
}
void circuit :: isrc_iter_dc( type_node *p , complex<double> value)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    while( t != NULL)
    {
        *(t -> address) += value * (t -> value2);
        t = t -> next;
    }
}
void circuit :: isrc_iter_ac( type_node *p , complex<double> value)
{
    address_node *s = p -> head -> next;
    address_node *t = p -> rhs_head -> next;
    while( s != NULL)
    {
        *(s -> address) += s -> value;
        s = s -> next;
    }
    while( t != NULL)
    {
        *(t -> address) += value * (t -> value2);
        t = t -> next;
    }
}
void circuit :: diode_iter( type_node *p , complex<double> *v )
{
    node_num_node *t = p -> node_num_head -> next;
    int n1 = t ->node_num;
    int n2 = t ->next ->node_num;

    complex<double> v_tmp = ((n1 == -1)? 0 : v[n1]) - ((n2 == -1)?0 : v[n2]);

    address_node *w = p -> rhs_head -> next;
    address_node *u = p -> head -> next;

    complex<double> tmp_g0 , tmp_i0;
    tmp_g0 = diode_g0( v_tmp , u -> value);
    tmp_i0 = diode_i0( v_tmp , u -> value);

    while( u != NULL )
    {
        *( u -> address) += (tmp_g0) * u -> value2;
        u = u -> next;
    }

    while( w != NULL )
    {
        *( w -> address) += (tmp_i0) * w -> value2;
        w = w -> next;
    }

    //cout<<"parameters:"<<endl;
    //cout<<"tmp_g0="<<tmp_g0<<endl;
    //cout<<"tmp_i0="<<tmp_i0<<endl;
}
void circuit :: diode_iter_ac( type_node *p , complex<double> *v )
{
    node_num_node *t = p -> node_num_head -> next;
    int n1 = t ->node_num;
    int n2 = t ->next ->node_num;

    complex<double> v_tmp = ((n1 == -1)? 0 : v[n1]) - ((n2 == -1)?0 : v[n2]);

    address_node *w = p -> rhs_head -> next;
    address_node *u = p -> head -> next;

    complex<double> tmp_g0 , tmp_i0;
    tmp_g0 = diode_g0( v_tmp , u -> value);
    tmp_i0 = 0;

    while( u != NULL )
    {
        *( u -> address) += (tmp_g0) * u -> value2;
        u = u -> next;
    }

    while( w != NULL )
    {
        *( w -> address) += (tmp_i0) * w -> value2;
        w = w -> next;
    }

    //cout<<"parameters:"<<endl;
    //cout<<"tmp_g0="<<tmp_g0<<endl;
    //cout<<"tmp_i0="<<tmp_i0<<endl;
}
void circuit :: mos_iter(type_node *p , complex<double> *v )
{
    node_num_node *t = p -> node_num_head -> next;
    int nd = t ->node_num;
    int ng = t ->next ->node_num;
    int ns = t ->next ->next->node_num;


    complex<double> vd = ((nd == -1)? 0 : v[nd]);
    complex<double> vg = ((ng == -1)? 0 : v[ng]);
    complex<double> vs = ((ns == -1)? 0 : v[ns]);

    int type = p->type - 11;
    address_node *u = p -> head -> next;
    address_node *w = p -> rhs_head -> next;

    complex<double> Gds = mos_Gds( type , vd , vg , vs , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);
    complex<double> Gm  = mos_Gm ( type , vd , vg , vs , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);
    complex<double> I0  = mos_I0 ( type , vd , vg , vs , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);
    //cout<<"stamping: Gds="<<Gds<<" Gm="<<Gm<<" I0="<<I0<<endl;

    if( u -> address != NULL) *(u -> address) +=  Gds       ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) += -Gds - Gm  ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) +=  Gm        ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) += -Gds       ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) +=  Gds + Gm  ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) += -Gm        ;

    if( w -> address != NULL) *(w -> address) += -I0 ; w = w -> next;
    if( w -> address != NULL) *(w -> address) +=  I0 ;
}

void circuit :: mos_iter_ac(type_node *p , complex<double> *v)
{
    node_num_node *t = p -> node_num_head -> next;
    int nd = t ->node_num;
    int ng = t ->next ->node_num;
    int ns = t ->next ->next->node_num;


    complex<double> vd = ((nd == -1)? 0 : v[nd]);
    complex<double> vg = ((ng == -1)? 0 : v[ng]);
    complex<double> vs = ((ns == -1)? 0 : v[ns]);

    int type = p->type - 11;
    address_node *u = p -> head -> next;
    address_node *w = p -> rhs_head -> next;

    complex<double> Gds = mos_Gds( type , vd , vg , vs , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);
    complex<double> Gm  = mos_Gm ( type , vd , vg , vs , u -> value , u -> value2 , (type == 0)? nmos0_parameter : pmos0_parameter);
    complex<double> I0  = 0;
    //cout<<"stamping: Gds="<<Gds<<" Gm="<<Gm<<" I0="<<I0<<endl;

    if( u -> address != NULL) *(u -> address) +=  Gds       ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) += -Gds - Gm  ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) +=  Gm        ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) += -Gds       ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) +=  Gds + Gm  ;               u = u -> next;
    if( u -> address != NULL) *(u -> address) += -Gm        ;

    if( w -> address != NULL) *(w -> address) += -I0 ; w = w -> next;
    if( w -> address != NULL) *(w -> address) +=  I0 ;
}

char** circuit :: return_name( int &c)
{
    type_node *p = address_structure_head;
    int counter = 0;

    while( p -> next != NULL && p -> next -> type < 6)
    {
        if( p -> next -> type == 4 || p -> next -> type == 5)
        {
            ++counter;
        }
        p = p -> next;
    }
    char** a = new char*[counter];
    for( int i = 0 ; i < counter ; ++i)
        a[i] =  new char[64];

    p = address_structure_head;
    counter = 0;
    while( p -> next != NULL && p -> next -> type < 6)
    {
        if( p -> next -> type == 4 || p -> next -> type == 5)
        {
            strcpy( a[counter++] , p ->next->name);
        }
        p = p -> next;
    }
    c = counter;
    return a;
}

//================= Iter_step===================================================================
void circuit :: do_iter()
{
    int counter=0;
    int i,j;
    do
    {
        type_node *p = address_structure_head->next;
        //cout<<"iter:"<<counter<<"times=============================================================="<<endl;
        for (i=0; i<stamp_size-1; i++)
        {
            for (j=0; j<stamp_size-1; j++)
            {
                stamp[i][j]=0;
            }
            RHS[i]=0;
        }
        while (p != NULL && p->type == 1)
        {
            res_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 2)
        {
            cap_iter_dc( p );
            p = p->next;
        }
        while (p != NULL && p->type == 3)
        {
            ind_iter_dc( p );
            p = p->next;
        }
        while (p != NULL && p->type == 4)
        {
            vsrc_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 5)
        {
            isrc_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 6)
        {
            cccs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 7)
        {
            ccvs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 8)
        {
            vccs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 9)
        {
            vcvs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 10)
        {
            diode_iter( p , current_ans );
            p = p->next;
        }
        while (p != NULL && p->type == 11)
        {
            mos_iter( p , current_ans );
            p = p->next;
        }
        while (p != NULL && p->type == 12)
        {
            mos_iter( p , current_ans );
            p = p->next;
        }

        //mos_iter();
        exchange_v();
        bool yorn;
        yorn = mySolve( stamp_size - 1 , stamp, RHS, current_ans);
        if (yorn == 0) cout<<"Solver meets singular matrix!!!"<<endl;
        counter++;


//        cout << "The Stamp is :" << endl;
//        for( i = 0 ; i < stamp_size - 1 ; ++i )
//        {
//            for( j = 0 ; j < stamp_size - 1 ; ++j) cout << stamp[i][j] << '\t';
//            cout << ' ' << ' ' <<  RHS[i] << endl;
//        }
//        cout << endl;
//
//        cout << "current_ans" << endl;
//        for( i = 0 ; i < stamp_size - 1 ; ++i) cout << current_ans[i] << endl;
//        cout << endl;
    }
    while (!judge_iter_end( current_ans , previous_ans , stamp_size-1));
    //while (counter<100);
}

void circuit :: do_iter_dc(type_node *pp, complex<double> current_value)
{
    int counter=0;
    int i,j;
    do
    {
        type_node *p = address_structure_head->next;
        //cout<<"iter:"<<counter<<"times=============================================================="<<endl;
        for (i=0; i<stamp_size-1; i++)
        {
            for (j=0; j<stamp_size-1; j++)
            {
                stamp[i][j]=0;
            }
            RHS[i]=0;
        }
        while (p != NULL && p->type == 1)
        {
            res_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 2)
        {
            cap_iter_dc( p );
            p = p->next;
        }
        while (p != NULL && p->type == 3)
        {
            ind_iter_dc( p );
            p = p->next;
        }
        while (p != NULL && p->type == 4)
        {
            if (p != pp) vsrc_iter( p );
            else vsrc_iter_dc( p , current_value );
            p = p->next;
        }
        while (p != NULL && p->type == 5)
        {
            if (p != pp) isrc_iter( p );
            else isrc_iter_dc( p , current_value );
            p = p->next;
        }
        while (p != NULL && p->type == 6)
        {
            cccs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 7)
        {
            ccvs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 8)
        {
            vccs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 9)
        {
            vcvs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 10)
        {
            diode_iter( p , current_ans );
            p = p->next;
        }
        while (p != NULL && p->type == 11)
        {
            mos_iter( p , current_ans );
            p = p->next;
        }
        while (p != NULL && p->type == 12)
        {
            mos_iter( p , current_ans );
            p = p->next;
        }

        //mos_iter();
        exchange_v();
        bool yorn;
        yorn = mySolve( stamp_size - 1 , stamp, RHS, current_ans);
        if (yorn == 0) cout<<"Solver meets singular matrix!!!"<<endl;
        counter++;


//        cout << "The Stamp is :" << endl;
//        for( i = 0 ; i < stamp_size - 1 ; ++i )
//        {
//            for( j = 0 ; j < stamp_size - 1 ; ++j) cout << stamp[i][j] << '\t';
//            cout << ' ' << ' ' <<  RHS[i] << endl;
//        }
//        cout << endl;
//
//        cout << "current_ans" << endl;
//        for( i = 0 ; i < stamp_size - 1 ; ++i) cout << current_ans[i] << endl;
//        cout << endl;
    }
    while (!judge_iter_end( current_ans , previous_ans , stamp_size-1));
    //while (counter<100);
}

void circuit :: do_iter_tran(complex<double> h, int times, complex<double> * last_result)
{
    int counter=0;
    int i,j;
    do
    {
        type_node *p = address_structure_head->next;
        //cout<<"iter:"<<counter<<"times=============================================================="<<endl;
        for (i=0; i<stamp_size-1; i++)
        {
            for (j=0; j<stamp_size-1; j++)
            {
                stamp[i][j]=0;
            }
            RHS[i]=0;
        }
        while (p != NULL && p->type == 1)
        {
            res_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 2)
        {
            cap_iter_tran( p, last_result , h , times);
            p = p->next;
        }
        while (p != NULL && p->type == 3)
        {
            ind_iter_tran( p, last_result , h , times);
            p = p->next;
        }
        while (p != NULL && p->type == 4)
        {
            vsrc_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 5)
        {
            isrc_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 6)
        {
            cccs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 7)
        {
            ccvs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 8)
        {
            vccs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 9)
        {
            vcvs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 10)
        {
            diode_iter( p , current_ans );
            p = p->next;
        }
        while (p != NULL && p->type == 11)
        {
            mos_iter( p , current_ans );
            p = p->next;
        }
        while (p != NULL && p->type == 12)
        {
            mos_iter( p , current_ans );
            p = p->next;
        }

        //mos_iter();
        exchange_v();
        bool yorn;
        yorn = mySolve( stamp_size - 1 , stamp, RHS, current_ans);
        if (yorn == 0) cout<<"Solver meets singular matrix!!!"<<endl;
        counter++;


//        cout << "The Stamp is :" << endl;
//        for( i = 0 ; i < stamp_size - 1 ; ++i )
//        {
//            for( j = 0 ; j < stamp_size - 1 ; ++j) cout << stamp[i][j] << '\t';
//            cout << ' ' << ' ' <<  RHS[i] << endl;
//        }
//        cout << endl;
//
//        cout << "current_ans" << endl;
//        for( i = 0 ; i < stamp_size - 1 ; ++i) cout << current_ans[i] << endl;
//        cout << endl;
    }
    while (!judge_iter_end( current_ans , previous_ans , stamp_size-1));
    //while (counter<100);
}

void circuit :: do_iter_ac(type_node *pp, complex<double> current_value , complex<double> * dc_solution)
{
    int counter=0;
    int i,j;
    do
    {
        type_node *p = address_structure_head->next;
        //cout<<"iter:"<<counter<<"times=============================================================="<<endl;
        for (i=0; i<stamp_size-1; i++)
        {
            for (j=0; j<stamp_size-1; j++)
            {
                stamp[i][j]=0;
            }
            RHS[i]=0;
        }
        while (p != NULL && p->type == 1)
        {
            res_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 2)
        {
            cap_iter_ac( p , current_value , dc_solution);
            p = p->next;
        }
        while (p != NULL && p->type == 3)
        {
            ind_iter_ac( p , current_value , dc_solution);
            p = p->next;
        }
        while (p != NULL && p->type == 4)
        {
            if (p != pp) vsrc_iter_ac( p , 0 );
            else vsrc_iter_ac( p , 1 );
            p = p->next;
        }
        while (p != NULL && p->type == 5)
        {
            if (p != pp) isrc_iter_ac( p , 0 );
            else isrc_iter_ac( p , 1 );
            p = p->next;
        }
        while (p != NULL && p->type == 6)
        {
            cccs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 7)
        {
            ccvs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 8)
        {
            vccs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 9)
        {
            vcvs_iter( p );
            p = p->next;
        }
        while (p != NULL && p->type == 10)
        {
            diode_iter_ac( p , dc_solution );
            p = p->next;
        }
        while (p != NULL && p->type == 11)
        {
            mos_iter_ac( p , dc_solution );
            p = p->next;
        }
        while (p != NULL && p->type == 12)
        {
            mos_iter_ac( p , dc_solution );
            p = p->next;
        }

        //mos_iter();
        exchange_v();
        bool yorn;
        yorn = mySolve( stamp_size - 1 , stamp, RHS, current_ans);
        if (yorn == 0) cout<<"Solver meets singular matrix!!!"<<endl;
        counter++;


//        cout << "The Stamp is :" << endl;
//        for( i = 0 ; i < stamp_size - 1 ; ++i )
//        {
//            for( j = 0 ; j < stamp_size - 1 ; ++j) cout << stamp[i][j] << '\t';
//            cout << ' ' << ' ' <<  RHS[i] << endl;
//        }
//        cout << endl;
//
//        cout << "current_ans" << endl;
//        for( i = 0 ; i < stamp_size - 1 ; ++i) cout << current_ans[i] << endl;
//        cout << endl;
    }
    while (!judge_iter_end( current_ans , previous_ans , stamp_size-1));
    //while (counter<100);
}

bool circuit :: dc_simulation(char * name, complex<double> start, complex<double> end, complex<double> step)
{
    ofstream fout("dc_result.txt");
    fout<<1<<endl;
    fout<<name<<' '<<real(start)<<' '<<real(end)<<' '<<real(step)<<endl;
    cout<<"================================================="<<endl;
    cout<<"dc "<<name<<' '<<real(start)<<' '<<real(end)<<' '<<real(step)<<endl;
    cout<<"*********"<<endl;

    type_node *p = address_structure_head;
    while (p->next != NULL)
    {
        if (strcmp(p->next->name, name) == 0) break;
        p = p->next;
    }
    if (p->next == NULL) return false;
    p = p->next;

    complex<double> current_point;
    int total_steps=0;
    if (real(start)>real(end) || real(step)<=0) return false;
    for (current_point=start; real(current_point)<=real(end); current_point=current_point+step )
    {
        total_steps++;
    }
    fout<<total_steps<<' '<<stamp_size-1<<endl;

    int ii;
    for( ii = 0 ; ii < 255 ; ++ii)
    {
        char_node *q = node_array[ii] -> next;
        if( q == NULL) continue;
        while( q != NULL)
        {
            if (q->name_id > 0) fout<<q -> name<<' ';
            q = q -> next;
        }
    }
    for( ii = 0 ; ii < 255 ; ++ii)
    {
        char_node *q = name_array[ii] -> next;
        if( q == NULL) continue;
        while( q != NULL)
        {
            if (q->name_id > 0) fout<<"I("<<q->name<<") ";
            q = q -> next;
        }
    }
    fout<<endl;

    fout<< setprecision(16);
    for (current_point=start; real(current_point)<=real(end); current_point=current_point+step )
    {
        cout<<"dc @ "<<real(current_point)<<endl;
        do_iter_dc(p, current_point);
        //for( i = 0 ; i < stamp_size - 1 ; ++i) fout << real(current_ans[i]) << ' ';
        for( ii = 0 ; ii < 255 ; ++ii)
        {
            char_node *q = node_array[ii] -> next;
            if( q == NULL) continue;
            while( q != NULL)
            {
                if (q->name_id > 0) fout<<real(current_ans[q->name_id-1])<<' ';
                q = q -> next;
            }
        }
        for( ii = 0 ; ii < 255 ; ++ii)
        {
            char_node *q = name_array[ii] -> next;
            if( q == NULL) continue;
            while( q != NULL)
            {
                if (q->name_id > 0) fout<<real(current_ans[q->name_id-1])<<' ';
                q = q -> next;
            }
        }
        fout << endl;
    }

    return true;
}

bool circuit :: tran_simulation(complex<double> h, complex<double> total_time)
{
    ofstream fout("tran_result.txt");
    fout<<2<<endl;
    fout<<real(h)<<' '<<real(total_time)<<endl;
    cout<<"================================================="<<endl;
    cout<<"tran "<<real(h)<<' '<<real(total_time)<<endl;
    cout<<"*********"<<endl;

    if (real(total_time) < 0 || real(h)<=0) return false;

    complex<double> *last_result = new complex<double> [stamp_size-1];
    complex<double> current_point;
    int total_steps=0;
    for (current_point=0; real(current_point)<=real(total_time); current_point=current_point+h)
    {
        total_steps++;
    }
    fout<<total_steps<<' '<<stamp_size-1<<endl;

    int ii;
    for( ii = 0 ; ii < 255 ; ++ii)
    {
        char_node *q = node_array[ii] -> next;
        if( q == NULL) continue;
        while( q != NULL)
        {
            if (q->name_id > 0) fout<<q -> name<<' ';
            q = q -> next;
        }
    }
    for( ii = 0 ; ii < 255 ; ++ii)
    {
        char_node *q = name_array[ii] -> next;
        if( q == NULL) continue;
        while( q != NULL)
        {
            if (q->name_id > 0) fout<<"I("<<q->name<<") ";
            q = q -> next;
        }
    }
    fout<<endl;

    fout<< setprecision(16);

    int times=0;int i;
    complex<double> tmp_h=h;
    for (current_point=0; real(current_point)<=real(total_time); current_point=current_point+h)
    {
        cout<<"tran @ "<<real(current_point)<<endl;
        //fout<<real(current_point)<<' ';
        do_iter_tran(tmp_h, times, last_result );
        //if ( abs(real(last_result[1]) - real(current_ans[1])) < 0.01)
        if ( abs(real(last_result[1]) - real(current_ans[1])) < 0)
        {
            cout<<"change pace!!"<<endl;
            tmp_h += h;
            current_point += tmp_h - h;
        }
        else
        {
            tmp_h = h;
        }
        for( i = 0 ; i < stamp_size - 1 ; ++i) last_result[i] = current_ans[i];
        //for( i = 0 ; i < stamp_size - 1 ; ++i) fout << real(current_ans[i]) << ' ';
        for( ii = 0 ; ii < 255 ; ++ii)
        {
            char_node *q = node_array[ii] -> next;
            if( q == NULL) continue;
            while( q != NULL)
            {
                if (q->name_id > 0) fout<<real(current_ans[q->name_id-1])<<' ';
                q = q -> next;
            }
        }
        for( ii = 0 ; ii < 255 ; ++ii)
        {
            char_node *q = name_array[ii] -> next;
            if( q == NULL) continue;
            while( q != NULL)
            {
                if (q->name_id > 0) fout<<real(current_ans[q->name_id-1])<<' ';
                q = q -> next;
            }
        }
        times++;
        fout << endl;
    }

    //cout<<total_steps<<endl;

    //do_iter_tran(h, 0, last_result );


    return true;
}

bool circuit :: ac_simulation(char * name, complex<double> start, complex<double> end, complex<double> step)
{
    type_node *p = address_structure_head;
    while (p->next != NULL)
    {
        if (strcmp(p->next->name, name) == 0) break;
        p = p->next;
    }
    if (p->next == NULL) return false;
    p = p->next;

    do_iter();
    complex<double> *dc_solution = new complex<double> [stamp_size - 1];
    int i;
    for( i = 0 ; i < stamp_size - 1 ; ++i) dc_solution[i] = current_ans[i];


    ofstream fout("ac_result.txt");
    fout<<3<<endl;
    fout<<name<<' '<<real(start)<<' '<<real(end)<<' '<<real(step)<<endl;
    cout<<"================================================="<<endl;
    cout<<"ac "<<name<<' '<<real(start)<<' '<<real(end)<<' '<<real(step)<<endl;
    cout<<"*********"<<endl;

    complex<double> current_point;
    i=0; int total_steps=0;
    if (real(start)>real(end) || real(step)<=0) return false;

    complex<double> min,max,imax;
    min = log(real(start));
    max = log(real(end));
    imax = step;
    complex<double> lstep = ( real(max) - real(min) ) / real(imax);
    lstep = (real(lstep) == 0)? 1.0 : lstep;

    for (current_point=start; real(current_point)<=real(end)+0.0000001; current_point=exp( log(current_point)+lstep ) )
    {
        //cout<<current_point<<endl;
        total_steps++;
    }
    fout<<total_steps<<' '<<stamp_size-1<<endl;

    int ii;
    for( ii = 0 ; ii < 255 ; ++ii)
    {
        char_node *q = node_array[ii] -> next;
        if( q == NULL) continue;
        while( q != NULL)
        {
            if (q->name_id > 0) fout<<q -> name<<' ';
            q = q -> next;
        }
    }
    for( ii = 0 ; ii < 255 ; ++ii)
    {
        char_node *q = name_array[ii] -> next;
        if( q == NULL) continue;
        while( q != NULL)
        {
            if (q->name_id > 0) fout<<"I("<<q->name<<") ";
            q = q -> next;
        }
    }
    fout<<endl;

    fout<< setprecision(16);
    for (current_point=start; real(current_point)<=real(end)+0.0000001; current_point=exp( log(current_point)+lstep ) )
    {
        cout<<"ac @ "<<real(current_point)<<endl;
        do_iter_ac(p, current_point , dc_solution);
        //for( i = 0 ; i < stamp_size - 1 ; ++i) fout << current_ans[i] << ' ';
        //for( i = 0 ; i < stamp_size - 1 ; ++i) fout << real(current_ans[i]) << ' ' << imag(current_ans[i]) << ' ';
        for( ii = 0 ; ii < 255 ; ++ii)
        {
            char_node *q = node_array[ii] -> next;
            if( q == NULL) continue;
            while( q != NULL)
            {
                if (q->name_id > 0) fout<<current_ans[q->name_id-1]<<' ';
                //if (q->name_id > 0) fout<<real(current_ans[q->name_id-1])<<' '<<imag(current_ans[q->name_id-1])<<' ';
                q = q -> next;
            }
        }
        for( ii = 0 ; ii < 255 ; ++ii)
        {
            char_node *q = name_array[ii] -> next;
            if( q == NULL) continue;
            while( q != NULL)
            {
                if (q->name_id > 0) fout<<current_ans[q->name_id-1]<<' ';
                //if (q->name_id > 0) fout<<real(current_ans[q->name_id-1])<<' '<<imag(current_ans[q->name_id-1])<<' ';
                q = q -> next;
            }
        }
        fout << endl;
    }

    return true;
}
