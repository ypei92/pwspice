

#ifndef model_nmos_INCLUDED
#define model_nmos_INCLUDED

#include "default_model.h"
#include "./element/element_nmos.h"

class model_nmos: public default_model
{
    private:
        struct nmos_node
        {
            element_nmos nmos;
            nmos_node *next;

            nmos_node( char* name , char* n1 , char* n2 , char* n3 , complex<double> w , complex<double> l , nmos_node *p = NULL)
            {
                nmos.element_name = name;
                nmos.node1 = n1;
                nmos.node2 = n2;
                nmos.DC_value = w;

                nmos.source = n3;
                nmos.length = l;

                next = p;
            }
            nmos_node():next(NULL){}
        };

        int currentLength;
        nmos_node *head;


    public:
       model_nmos();
       ~model_nmos(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 , char* n2 , char* n3 , complex<double> w , complex<double> l );
       //void stamp();
       void traverse();
       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start)
       {
           nmos_node *p = head -> next;
           int nd , ng , ns , i;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(11, p->nmos.element_name);



                nd = search( p -> nmos.node1 , node_array) - 1;
                ng = search( p -> nmos.node2 , node_array) - 1;
                ns = search( p -> nmos.source , node_array) - 1;
                //cout << "nnnnnnnnnnnnnnnnnnnnnn" << nd << ' ' << ng <<' ' << ns << endl;
                node_num_node *o2 = new node_num_node(ns , NULL);
                node_num_node *o1 = new node_num_node(ng , o2);
                node_num_node *o0 = new node_num_node(nd , o1);
                tmp -> node_num_head -> next = o0;

                bool gs = (ng != -1 && ns != -1);
                bool sd = (nd != -1 && ns != -1);
                bool dg = (nd != -1 && ng != -1);
                bool s  = (ns != -1);
                bool d  = (nd != -1);
                //bool g  = (ng != -1);


                address_node *t5 = new address_node( p -> nmos.DC_value ,  (gs)? &stamp[ns][ng] : NULL, NULL , p->nmos.length);
                address_node *t4 = new address_node( p -> nmos.DC_value ,  (s) ? &stamp[ns][ns] : NULL , t5 , p->nmos.length);
                address_node *t3 = new address_node( p -> nmos.DC_value ,  (sd)? &stamp[ns][nd] : NULL , t4 , p->nmos.length);
                address_node *t2 = new address_node( p -> nmos.DC_value ,  (dg)? &stamp[nd][ng] : NULL , t3 , p->nmos.length);
                address_node *t1 = new address_node( p -> nmos.DC_value ,  (sd)? &stamp[nd][ns] : NULL , t2 , p->nmos.length);
                address_node *t0 = new address_node( p -> nmos.DC_value ,  (d) ? &stamp[nd][nd] : NULL , t1 , p->nmos.length);
                tmp -> head -> next = t0;

                address_node *r1 = new address_node( p -> nmos.DC_value ,  (s) ?&RHS[ns] : NULL , NULL , p->nmos.length);
                address_node *r0 = new address_node( p -> nmos.DC_value ,  (d) ?&RHS[nd] : NULL , r1   , p->nmos.length);
                tmp -> rhs_head -> next = r0;


                start -> next = tmp;
                start = tmp;

                p = p -> next;
           }
           return start;
       }

};


#endif
