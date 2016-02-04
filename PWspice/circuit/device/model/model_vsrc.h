

#ifndef model_vsrc_INCLUDED
#define model_vsrc_INCLUDED

#include "default_model.h"
#include "./element/element_vsrc.h"

class model_vsrc: public default_model
{
    private:
        struct vsrc_node
        {
            element_vsrc vsrc;
            vsrc_node *next;

            vsrc_node(char * name , char* n1 , char *n2, complex<double> v = 0 ,vsrc_node *p = NULL)
            {
                vsrc.element_name = name;
                vsrc.node1 = n1;
                vsrc.node2 = n2;
                vsrc.DC_value = v;

                next = p;
            }
            vsrc_node():next(NULL){}
        };

        int currentLength;
        vsrc_node *head;


    public:
       model_vsrc();
       ~model_vsrc(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 ,  char* n2 , complex<double> v );
       //void stamp();
       void traverse();

       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start)
       {
           vsrc_node *p = head -> next;
           int n1 , n2 , i , branch_num ;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(4, p->vsrc.element_name);

                n1 = search( p -> vsrc.node1 , node_array) - 1;
                n2 = search( p -> vsrc.node2 , node_array) - 1;
                branch_num = search( p -> vsrc.element_name , name_array) - 1;

                address_node *r0 = new address_node( p->vsrc.DC_value , &RHS[branch_num] , NULL);
                tmp -> rhs_head -> next = r0;
                //cout << "n1  n2 = " << n1 << ' ' << n2 << endl;
                if( n1 == -1 || n2 == -1)
                {
                    if( n1 == -1)
                    {
                        address_node *t1 = new address_node( -1 , &stamp[branch_num][n2] , NULL);
                        address_node *t0 = new address_node( -1 , &stamp[n2][branch_num] , t1);
                        tmp -> head -> next = t0;
                    }
                    else if(n2 == -1)
                    {
                        address_node *t1 = new address_node( 1 , &stamp[branch_num][n1] , NULL);
                        address_node *t0 = new address_node( 1 , &stamp[n1][branch_num] , t1);
                        tmp -> head -> next = t0;
                    }
                }
                else
                {
                    //complex<double> v = p -> ind.DC_value / h;

                    address_node *t3 = new address_node( -1 ,  &stamp[branch_num][n2] , NULL);
                    address_node *t2 = new address_node(  1 ,  &stamp[branch_num][n1] , t3);
                    address_node *t1 = new address_node( -1 ,  &stamp[n2][branch_num] , t2);
                    address_node *t0 = new address_node(  1 ,  &stamp[n1][branch_num] , t1);
                    tmp -> head -> next = t0;
                    //cout <<"vvvvvvv"<< n1 << ' '<< n2 << ' ' << branch_num<<endl;

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
