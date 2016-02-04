

#ifndef model_pmos_INCLUDED
#define model_pmos_INCLUDED

#include "default_model.h"
#include "./element/element_pmos.h"

class model_pmos: public default_model
{
    private:
        struct pmos_node
        {
            element_pmos pmos;
            pmos_node *next;

            pmos_node( char* name , char* n1 , char* n2 , char* n3 , complex<double> w , complex<double> l , pmos_node *p = NULL)
            {
                pmos.element_name = name;
                pmos.node1 = n1;
                pmos.node2 = n2;
                pmos.DC_value = w;

                pmos.source = n3;
                pmos.length = l;

                next = p;
            }
            pmos_node():next(NULL){}
        };

        int currentLength;
        pmos_node *head;


    public:
       model_pmos();
       ~model_pmos(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 , char* n2 , char* n3 , complex<double> w , complex<double> l );
       //void stamp();
       void traverse();
       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start)
       {
           pmos_node *p = head -> next;
           int nd , ng , ns , i;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(12,p->pmos.element_name);

                nd = search( p -> pmos.node1 , node_array) - 1;
                ng = search( p -> pmos.node2 , node_array) - 1;
                ns = search( p -> pmos.source , node_array) - 1;

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


                address_node *t5 = new address_node( p -> pmos.DC_value ,  (gs)? &stamp[ns][ng] : NULL , NULL , p->pmos.length);
                address_node *t4 = new address_node( p -> pmos.DC_value ,  (s) ? &stamp[ns][ns] : NULL , t5 , p->pmos.length);
                address_node *t3 = new address_node( p -> pmos.DC_value ,  (sd)? &stamp[ns][nd] : NULL , t4 , p->pmos.length);
                address_node *t2 = new address_node( p -> pmos.DC_value ,  (dg)? &stamp[nd][ng] : NULL , t3 , p->pmos.length);
                address_node *t1 = new address_node( p -> pmos.DC_value ,  (sd)? &stamp[nd][ns] : NULL , t2 , p->pmos.length);
                address_node *t0 = new address_node( p -> pmos.DC_value ,  (d) ? &stamp[nd][nd] : NULL , t1 , p->pmos.length);
                tmp -> head -> next = t0;
                //cout<<"ns="<<ns<<" ng="<<ng<<" nd="<<nd<<endl;

                address_node *r1 = new address_node( p -> pmos.DC_value ,  (s) ?&RHS[ns] : NULL , NULL , p->pmos.length);
                address_node *r0 = new address_node( p -> pmos.DC_value ,  (d) ?&RHS[nd] : NULL , r1   , p->pmos.length);
                tmp -> rhs_head -> next = r0;

                start -> next = tmp;
                start = tmp;

                p = p -> next;
           }
           return start;
       }

};


#endif
