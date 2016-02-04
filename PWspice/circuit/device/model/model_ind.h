

#ifndef model_ind_INCLUDED
#define model_ind_INCLUDED

#include "default_model.h"
#include "./element/element_ind.h"

class model_ind: public default_model
{
    private:
        struct ind_node
        {
            element_ind ind;
            ind_node *next;

            ind_node(char * name , char* n1 , char *n2, complex<double> v = 0 , complex<double> v_init = 0 , ind_node *p = NULL)
            {
                ind.element_name = name;
                ind.node1 = n1;
                ind.node2 = n2;
                ind.DC_value = v;
                ind.init_value = v_init;

                next = p;
            }
            ind_node():next(NULL){}
        };

        int currentLength;
        ind_node *head;


    public:
       model_ind();
       ~model_ind(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 ,  char* n2 , complex<double> v , complex<double> v_init );
       //void stamp();
       void traverse();

       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start)
       {
           ind_node *p = head -> next;
           int n1 , n2 , i ,branch_num;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(3, p->ind.element_name);

                n1 = search( p -> ind.node1 , node_array) - 1;
                n2 = search( p -> ind.node2 , node_array) - 1;
                branch_num = search( p -> ind.element_name , name_array) - 1;

                node_num_node *o0 = new node_num_node(branch_num , NULL);
                tmp -> node_num_head -> next = o0;

                address_node *r0 = new address_node(-(p->ind.DC_value)  , &RHS[branch_num] , NULL , (p->ind.init_value));
                tmp -> rhs_head -> next = r0;
                //cout << "n1  n2 = " << n1 << ' ' << n2 << endl;
                if( n1 == -1 || n2 == -1)
                {
                    address_node *t2 = new address_node(- p->ind.DC_value , &stamp[branch_num][branch_num] , NULL);
                    if( n1 == -1)
                    {
                        address_node *t1 = new address_node( -1 , &stamp[branch_num][n2] , t2);
                        address_node *t0 = new address_node( -1 , &stamp[n2][branch_num] , t1);
                        tmp -> head -> next = t0;
                    }
                    else if(n2 == -1)
                    {
                        address_node *t1 = new address_node( 1 , &stamp[branch_num][n1] , t2);
                        address_node *t0 = new address_node( 1 , &stamp[n1][branch_num] , t1);
                        tmp -> head -> next = t0;
                    }
                }
                else
                {
                    complex<double> v = p -> ind.DC_value;
                    //cout<<n1<<' '<<n2<<' '<<branch_num<<endl;
                    address_node *t4 = new address_node( -v ,  &stamp[branch_num][branch_num] , NULL);
                    address_node *t3 = new address_node( -1 , &stamp[branch_num][n2] , t4);
                    address_node *t2 = new address_node( 1 , &stamp[branch_num][n1] , t3);
                    address_node *t1 = new address_node( -1 ,  &stamp[n2][branch_num] , t2);
                    address_node *t0 = new address_node( 1 ,  &stamp[n1][branch_num] , t1);
                    //cout <<"llllllllll"<< n1 << ' '<< n2 <<' '<< branch_num<<endl;

                    tmp -> head -> next = t0;

                }

                start -> next = tmp;
                start = tmp;

                p = p -> next;
           }
           return start;
       }

};

#endif
