

#ifndef model_cccs_INCLUDED
#define model_cccs_INCLUDED

#include "default_model.h"
#include "./element/element_cccs.h"

class model_cccs: public default_model
{
    private:
        struct cccs_node
        {
            element_cccs cccs;
            cccs_node *next;

            cccs_node(char* name , char* n1 , char* n2 , char* vname , complex<double> v , cccs_node *p = NULL)
            {
                cccs.element_name = name;
                cccs.node1 = n1;
                cccs.node2 = n2;
                cccs.DC_value = v;
                cccs.vname = vname;

                next = p;
            }
            cccs_node():next(NULL){}
        };

        int currentLength;
        cccs_node *head;


    public:
       model_cccs();
       ~model_cccs(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 , char* n2 , char* vname , complex<double> v );
       //void stamp();
       void traverse();
       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start )
       {
           cccs_node *p = head -> next;
           int n1 , n2 , i ,branch_num;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(6, p->cccs.element_name);

                n1 = search( p -> cccs.node1 , node_array) - 1;
                n2 = search( p -> cccs.node2 , node_array) - 1;

                branch_num = search( p -> cccs.vname , name_array ) - 1;

                //cout << "n1  n2 = " << n1 << ' ' << n2 << endl;
                if( n1 == -1 || n2 == -1)
                {
                    if( n1 == -1)
                    {
                        address_node *t0 = new address_node(  p->cccs.DC_value , &stamp[n2][branch_num] , NULL);
                        tmp -> head -> next = t0;
                    }
                    else if(n2 == -1)
                    {
                        address_node *t0 = new address_node( -p->cccs.DC_value , &stamp[n1][branch_num] , NULL);
                        tmp -> head -> next = t0;
                    }
                }
                else
                {
                    //complex<double> v = p -> ind.DC_value / h;

                    address_node *t1 = new address_node(  p -> cccs.DC_value ,  &stamp[n2][branch_num] , NULL);
                    address_node *t0 = new address_node( -p -> cccs.DC_value ,  &stamp[n1][branch_num] , t1);
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
