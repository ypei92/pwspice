

#ifndef model_ccvs_INCLUDED
#define model_ccvs_INCLUDED

#include "default_model.h"
#include "./element/element_ccvs.h"

class model_ccvs: public default_model
{
    private:
        struct ccvs_node
        {
            element_ccvs ccvs;
            ccvs_node *next;

            ccvs_node(char* name , char* n1 , char* n2 , char* vname , complex<double> v , ccvs_node *p = NULL)
            {
                ccvs.element_name = name;
                ccvs.node1 = n1;
                ccvs.node2 = n2;
                ccvs.DC_value = v;
                ccvs.vname = vname;

                next = p;
            }
            ccvs_node():next(NULL){}
        };

        int currentLength;
        ccvs_node *head;


    public:
       model_ccvs();
       ~model_ccvs(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 , char* n2 , char* vname , complex<double> v );
       //void stamp();
       void traverse();
       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start )
       {
           ccvs_node *p = head -> next;
           int n1 , n2 , i ,branch_num0 , branch_num1;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(7, p->ccvs.element_name);

                n1 = search( p -> ccvs.node1 , node_array) - 1;
                n2 = search( p -> ccvs.node2 , node_array) - 1;
                branch_num0 = search( p -> ccvs.element_name , name_array ) - 1;
                branch_num1 = search( p -> ccvs.vname , name_array ) - 1;

                //cout << "n1  n2 = " << n1 << ' ' << n2 << endl;
                if( n1 == -1 || n2 == -1)
                {
                    address_node *t2 = new address_node(  - p -> ccvs.DC_value , &stamp[branch_num0][branch_num1] , NULL);
                    if( n1 == -1)
                    {
                        address_node *t1 = new address_node(  -1 , &stamp[branch_num0][n2] , t2);
                        address_node *t0 = new address_node(  -1 , &stamp[n2][branch_num0] , t1);
                        tmp -> head -> next = t0;
                    }
                    else if(n2 == -1)
                    {
                        address_node *t1 = new address_node(   1 , &stamp[branch_num0][n1] , t2);
                        address_node *t0 = new address_node(   1 , &stamp[n1][branch_num0] , t1);
                        tmp -> head -> next = t0;
                    }
                }
                else
                {
                    //complex<double> v = p -> ind.DC_value / h;
                    address_node *t4 = new address_node(  - p -> ccvs.DC_value ,  &stamp[branch_num0][branch_num1] , NULL);
                    address_node *t3 = new address_node(  -1 ,  &stamp[branch_num0][n2] , t4);
                    address_node *t2 = new address_node(   1 ,  &stamp[branch_num0][n1] , t3);
                    address_node *t1 = new address_node(  -1 ,  &stamp[n2][branch_num0] , t2);
                    address_node *t0 = new address_node(   1 ,  &stamp[n1][branch_num0] , t1);
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
