

#ifndef model_res_linear_INCLUDED
#define model_res_linear_INCLUDED

#include "default_model.h"
#include "./element/element_res.h"

class model_res_linear: public default_model
{
    private:
        struct res_linear_node
        {
            element_res res;
            res_linear_node *next;

            res_linear_node(char * name , char* n1 , char *n2, complex<double> v = 0 ,res_linear_node *p = NULL)
            {
                res.element_name = name;
                res.node1 = n1;
                res.node2 = n2;
                res.DC_value = v;

                next = p;
            }
            res_linear_node():next(NULL){}
        };

        int currentLength;
        res_linear_node *head;


    public:
       model_res_linear();
       ~model_res_linear(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 ,  char* n2 , complex<double> v );
       //void stamp();
       void traverse();

       type_node* organize_address( complex<double> **stamp , complex<double> *RHS , char_node **node_array , char_node **name_array , type_node* start )
       {
           res_linear_node *p = head -> next;
           int n1 , n2 , i ;
           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(1, p->res.element_name);

                n1 = search( p -> res.node1 , node_array) - 1;
                n2 = search( p -> res.node2 , node_array) - 1;

                //cout << "n1  n2 = " << n1 << ' ' << n2 << endl;
                if( n1 == -1 || n2 == -1)
                {
                    address_node *t0 = new address_node;
                    t0 -> next = NULL;
                    t0 -> value = 1.0/(p -> res.DC_value);
                    if( n1 == -1) t0 -> address = &stamp[n2][n2];
                    else if( n2 == -1) t0 -> address = &stamp[n1][n1];

                    tmp -> head -> next = t0;
                }
                else
                {
                    complex<double> v = 1.0/(p -> res.DC_value);

                    address_node *t3 = new address_node( v ,  &stamp[n2][n2] , NULL);
                    address_node *t2 = new address_node( -v , &stamp[n2][n1] , t3);
                    address_node *t1 = new address_node( -v , &stamp[n1][n2] , t2);
                    address_node *t0 = new address_node( v ,  &stamp[n1][n1] , t1);
                    //cout <<"rrrrr"<< n1 << ' '<< n2 << endl;
                    tmp -> head -> next = t0;
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
