
#ifndef model_diode_INCLUDED
#define model_diode_INCLUDED

#include "default_model.h"
#include "./element/element_diode.h"

class model_diode: public default_model
{
    private:
        struct diode_node
        {
            element_diode diode;
            diode_node *next;

            diode_node(char * name , char* n1 , char *n2, complex<double> v = 0 ,diode_node *p = NULL)
            {
                diode.element_name = name;
                diode.node1 = n1;
                diode.node2 = n2;
                diode.DC_value = v;

                next = p;
            }
            diode_node():next(NULL){}
        };

        int currentLength;
        diode_node *head;

        //static complex<double> coefficient;

    public:
       model_diode();
       ~model_diode(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 ,  char* n2 , complex<double> v );
       //void stamp();
       void traverse();
       //complex<double> countG0(complex<double> in);
       //complex<double> countI0(complex<double> in);

       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start)
       {
           diode_node *p = head -> next;
           int n1 , n2 , i;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(10, p->diode.element_name);

                n1 = search( p -> diode.node1 , node_array) - 1;
                n2 = search( p -> diode.node2 , node_array) - 1;

                node_num_node *o1 = new node_num_node(n2 , NULL);
                node_num_node *o0 = new node_num_node(n1 , o1);
                tmp -> node_num_head -> next = o0;

                //address_node *r0 = new address_node( p -> diode.DC_value , &RHS[] , NULL);
                //tmp -> rhs_head -> next = r0;
                //cout << "n1  n2 = " << n1 << ' ' << n2 << endl;
                if( n1 == -1)
                {
                    address_node *t0 = new address_node( p -> diode.DC_value ,  &stamp[n2][n2] , NULL , 1);
                    address_node *r0 = new address_node( p -> diode.DC_value ,  &RHS[n2] , NULL , -1);
                    tmp -> head -> next = t0;
                    tmp -> rhs_head -> next = r0;
                }
                else if( n2 == -1)
                {
                    address_node *t0 = new address_node( p -> diode.DC_value ,  &stamp[n1][n1] , NULL , 1);
                    address_node *r0 = new address_node( p -> diode.DC_value ,  &RHS[n1] , NULL , 1);
                    tmp -> head -> next = t0;
                    tmp -> rhs_head -> next = r0;
                }
                else
                {
                    address_node *t3 = new address_node( p -> diode.DC_value ,  &stamp[n2][n2] , NULL , 1);
                    address_node *t2 = new address_node( p -> diode.DC_value ,  &stamp[n2][n1] , t3   ,-1);
                    address_node *t1 = new address_node( p -> diode.DC_value ,  &stamp[n1][n2] , t2   ,-1);
                    address_node *t0 = new address_node( p -> diode.DC_value ,  &stamp[n1][n1] , t1   , 1);

                    address_node *r1 = new address_node( p -> diode.DC_value ,  &RHS[n2] , NULL ,  -1);
                    address_node *r0 = new address_node( p -> diode.DC_value ,  &RHS[n1] , r1   , 1);

                    tmp -> head -> next = t0;
                    tmp -> rhs_head -> next = r0;
                }

                start -> next = tmp;
                start = tmp;

                p = p -> next;
           }
           //++branch_start;
           //cout << "branch_start = " << branch_start << endl;
           return start;
       }

};

#endif
