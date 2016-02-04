

#ifndef default_model_INCLUDED
#define default_model_INCLUDED

#include <iostream>
#include <cstring>
#include <cmath>
#include "./element/element.h"

#include <complex>

using namespace std;

typedef struct
{
    complex<double> lambda;
    complex<double> threshold;
    complex<double> mobility;
    complex<double> Cox;
}mos_model;

class default_model
{
    public:
        static complex<double> h;
        static mos_model nmos0_parameter;
        static mos_model pmos0_parameter;

        struct address_node
        {
            complex<double> *address;
            complex<double> value;
            address_node *next;

            complex<double> value2;

            //address_node( complex<double> v , complex<double>*a , address_node* p = NULL):value(v),address(a),next(p){}
            address_node( complex<double> v , complex<double>*a , address_node* p = NULL , complex<double> v2 = 0)
            {
                value = v;
                address = a;
                next = p;

                value2 = v2;

            }
            address_node():next(NULL){}
        };

        struct node_num_node
        {
            int node_num;
            node_num_node *next;
            node_num_node( int n , node_num_node *p = NULL)
            {
                node_num = n;
                next = p;
            }
            node_num_node():next(NULL){}
        };

        struct type_node
        {
            int type;

            char * name;

            type_node *next;
            address_node *head;
            address_node *rhs_head;
            node_num_node *node_num_head;
            type_node( int t , char * n, type_node* p = NULL)
            {
                name = n;
                type = t;
                next = p;

                head = new address_node;
                rhs_head = new address_node;
                node_num_head = new node_num_node;
            }
            type_node():next(NULL){}
        };

        struct char_node
        {
            char *name;
            int name_id;
            char_node *next;

            char_node( char* n , int id , char_node *p = NULL)
            {
                name = n;
                name_id = id;

                next = p;
            }
            char_node():next(NULL){}
        };

//-------------------------------------hash()-----------------------------------------
        int hash( char* name , int size)
        {
            char *s;
            int i = 0;
            for (s = name ; *s ; s++)
                i += *s;

            return (i % size);
        }


//-------------------------------------search()----------------------------------------
        int search( char* name , char_node** array)
        {
            int location = hash( name , 255);
            char_node *p = array[location] -> next;

            while( p != NULL)
            {
                if( strcmp( name , p -> name) == 0) break;
                p = p -> next;
            }

            if( p == NULL) return -1;
            else return p -> name_id;
        }

};

#endif
