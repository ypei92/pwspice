

#ifndef model_isrc_INCLUDED
#define model_isrc_INCLUDED

#include "default_model.h"
#include "./element/element_isrc.h"


class model_isrc: public default_model
{
    private:
        struct isrc_node
        {
            element_isrc isrc;
            isrc_node *next;

            isrc_node(char * name , char* n1 , char *n2, complex<double> v = 0 ,isrc_node *p = NULL)
            {
                isrc.element_name = name;
                isrc.node1 = n1;
                isrc.node2 = n2;
                isrc.DC_value = v;

                next = p;
            }
            isrc_node():next(NULL){}
        };

        int currentLength;
        isrc_node *head;


    public:
       model_isrc();
       ~model_isrc(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 ,  char* n2 , complex<double> v );
       //void stamp();
       void traverse();

       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start )
       {
           isrc_node *p = head -> next;
           int n1 , n2 , i ;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(5, p->isrc.element_name);

                n1 = search( p -> isrc.node1 , node_array) - 1;
                n2 = search( p -> isrc.node2 , node_array) - 1;

                //cout << "n1  n2 = " << n1 << ' ' << n2 << endl;
                if( n1 == -1 || n2 == -1)
                {

                    if( n1 == -1)
                    {
                        address_node *r0 = new address_node(  p->isrc.DC_value , &RHS[n2] , NULL,1);
                        tmp -> rhs_head -> next = r0;
                    }
                    else if(n2 == -1)
                    {
                        address_node *r0 = new address_node( -p->isrc.DC_value , &RHS[n1] , NULL,-1);
                        tmp -> rhs_head -> next = r0;
                    }
                }
                else
                {
                    //complex<double> v = p -> ind.DC_value / h;

                    address_node *r1 = new address_node(  p->isrc.DC_value ,  &RHS[n2] , NULL,-1);
                    address_node *r0 = new address_node( -p->isrc.DC_value ,  &RHS[n1] , r1,1);
                    tmp -> rhs_head -> next = r0;

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
