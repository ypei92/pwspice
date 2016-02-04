

#ifndef model_cap_INCLUDED
#define model_cap_INCLUDED

#include "default_model.h"
#include "./element/element_cap.h"

class model_cap: public default_model
{
    private:
        struct cap_node
        {
            element_cap cap;
            cap_node *next;

            cap_node(char * name , char* n1 , char *n2, complex<double> v = 0 , complex<double> v_init = 0 , cap_node *p = NULL)
            {
                cap.element_name = name;
                cap.node1 = n1;
                cap.node2 = n2;
                cap.DC_value = v;
                cap.init_value = v_init;

                next = p;
            }
            cap_node():next(NULL){}
        };

        int currentLength;
        cap_node *head;


    public:
       model_cap();
       ~model_cap(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 ,  char* n2 , complex<double> v , complex<double> v_init );
       //void stamp();
       void traverse();

       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start)
       {
           cap_node *p = head -> next;
           int n1 , n2 , i ;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(2, p->cap.element_name);

                n1 = search( p -> cap.node1 , node_array) - 1;
                n2 = search( p -> cap.node2 , node_array) - 1;

                node_num_node *o1 = new node_num_node(n2 , NULL);
                node_num_node *o0 = new node_num_node(n1 , o1);
                tmp -> node_num_head -> next = o0;

                //cout << "cccccc n1  n2 = " << n1 << ' ' << n2 << endl;
                if( n1 == -1 || n2 == -1)
                {
                    address_node *t0 = new address_node;
                    address_node *r0 = new address_node;
                    //node_num_node *o0 = new node_num_node;

                    t0 -> value = p -> cap.DC_value;

                    r0 -> value = (p -> cap.DC_value);
                    r0 -> value2 = p -> cap.init_value;

                    if( n1 == -1)
                    {
                        t0 -> address = &stamp[n2][n2];
                        r0 -> address = &RHS[n2];
                        //o0 -> node_num = n2;
                    }
                    else if(n2 == -1)
                    {
                        t0 -> address = &stamp[n1][n1];
                        r0 -> address = &RHS[n1];
                       // o0 -> node_num = n1;
                    }

                    tmp -> head -> next = t0;
                    tmp -> rhs_head -> next = r0;
                   // tmp -> node_num_head -> next = o0;
                }
                else
                {
                    complex<double> v = p -> cap.DC_value;

                    address_node *t3 = new address_node( v ,  &stamp[n2][n2] , NULL);
                    address_node *t2 = new address_node( -v , &stamp[n2][n1] , t3);
                    address_node *t1 = new address_node( -v , &stamp[n1][n2] , t2);
                    address_node *t0 = new address_node( v ,  &stamp[n1][n1] , t1);
                    tmp -> head -> next = t0;

                    address_node *r1 = new address_node( -v  , &RHS[n2] , NULL , p->cap.init_value);
                    address_node *r0 = new address_node(  v  , &RHS[n1] , r1 , p->cap.init_value);
                    tmp -> rhs_head -> next = r0;

                }

                start -> next = tmp;
                start = tmp;

                p = p -> next;
           }
           //cout << "branch_start = " << branch_start << endl;
           return start;
       }

};

#endif
