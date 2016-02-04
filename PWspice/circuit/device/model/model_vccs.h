

#ifndef model_vccs_INCLUDED
#define model_vccs_INCLUDED

#include "default_model.h"
#include "./element/element_vccs.h"

class model_vccs: public default_model
{
    private:
        struct vccs_node
        {
            element_vccs vccs;
            vccs_node *next;

            vccs_node( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v , vccs_node *p = NULL)
            {
                vccs.element_name = name;
                vccs.node1 = n1;
                vccs.node2 = n2;
                vccs.DC_value = v;

                vccs.node1c = n1c;
                vccs.node2c = n2c;

                next = p;
            }
            vccs_node():next(NULL){}
        };

        int currentLength;
        vccs_node *head;


    public:
       model_vccs();
       ~model_vccs(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v );
       //void stamp();
       void traverse();
       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start )
       {
           vccs_node *p = head -> next;
           int n1 , n2 , n1c , n2c , i;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(8, p->vccs.element_name);

                n1 = search( p -> vccs.node1 , node_array) - 1;
                n2 = search( p -> vccs.node2 , node_array) - 1;
                n1c= search( p -> vccs.node1c, node_array) - 1;
                n2c= search( p -> vccs.node2c, node_array) - 1;

                if( n1 == -1)
                {
                    if( n1c == -1)
                    {
                        address_node *t0 = new address_node(  1.0*p -> vccs.DC_value , &stamp[n2][n2c] , NULL);
                        tmp -> head -> next = t0;
                    }
                    else if(n2c == -1)
                    {
                        address_node *t0 = new address_node( -1.0*p -> vccs.DC_value , &stamp[n2][n1c] , NULL);
                        tmp -> head -> next = t0;
                    }
                    else
                    {
                        address_node *t1 = new address_node(  1.0*p -> vccs.DC_value , &stamp[n2][n2c] , NULL);
                        address_node *t0 = new address_node( -1.0*p -> vccs.DC_value , &stamp[n2][n1c] , t1);
                        tmp -> head -> next = t0;
                    }
                }
                else if( n2 == -1)
                {
                    if( n1c == -1)
                    {
                        address_node *t0 = new address_node( -1.0*p -> vccs.DC_value , &stamp[n1][n2c] , NULL);
                        tmp -> head -> next = t0;
                    }
                    else if(n2c == -1)
                    {
                        address_node *t0 = new address_node(  1.0*p -> vccs.DC_value , &stamp[n1][n1c] , NULL);
                        tmp -> head -> next = t0;
                    }
                    else
                    {
                        address_node *t1 = new address_node( -1.0*p -> vccs.DC_value , &stamp[n1][n2c] , NULL);
                        address_node *t0 = new address_node(  1.0*p -> vccs.DC_value , &stamp[n1][n1c] , t1);
                        tmp -> head -> next = t0;
                    }

                }
                else if( n1c == -1)
                {
                    address_node *t1 = new address_node(  1.0*p -> vccs.DC_value , &stamp[n2][n2c] , NULL);
                    address_node *t0 = new address_node( -1.0*p -> vccs.DC_value , &stamp[n1][n2c] , t1);
                    tmp -> head -> next = t0;
                }
                else if( n2c == -1)
                {
                    address_node *t1 = new address_node( -1.0*p -> vccs.DC_value , &stamp[n2][n1c] , NULL);
                    address_node *t0 = new address_node(  1.0*p -> vccs.DC_value , &stamp[n1][n1c] , t1);
                    tmp -> head -> next = t0;
                }
                else
                {
                    //complex<double> v = p -> ind.DC_value / h;
                    address_node *t3 = new address_node(  1.0*p -> vccs.DC_value ,  &stamp[n2][n2c] , NULL);
                    address_node *t2 = new address_node( -1.0*p -> vccs.DC_value ,  &stamp[n2][n1c] , t3);
                    address_node *t1 = new address_node( -1.0*p -> vccs.DC_value ,  &stamp[n1][n2c] , t2);
                    address_node *t0 = new address_node(  1.0*p -> vccs.DC_value ,  &stamp[n1][n1c] , t1);

                    tmp -> head -> next = t0;
                }

                start -> next = tmp;
                start = tmp;

                p = p -> next;
           }
           //cout << "branch_num = " << branch_num << endl;
           return start;
       }

};



#endif
