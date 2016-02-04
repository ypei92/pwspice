

#ifndef model_vcvs_INCLUDED
#define model_vcvs_INCLUDED

#include "default_model.h"
#include "./element/element_vcvs.h"
class model_vcvs: public default_model
{
    private:
        struct vcvs_node
        {
            element_vcvs vcvs;
            vcvs_node *next;

            vcvs_node( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v , vcvs_node *p = NULL)
            {
                vcvs.element_name = name;
                vcvs.node1 = n1;
                vcvs.node2 = n2;
                vcvs.DC_value = v;

                vcvs.node1c = n1c;
                vcvs.node2c = n2c;

                next = p;
            }
            vcvs_node():next(NULL){}
        };

        int currentLength;
        vcvs_node *head;


    public:
       model_vcvs();
       ~model_vcvs(){clear();delete head;}

       void clear();
       void append( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v );
       //void stamp();
       void traverse();

       type_node* organize_address( complex<double> **stamp , complex<double>* RHS , char_node **node_array , char_node **name_array , type_node* start )
       {
           vcvs_node *p = head -> next;
           int n1 , n2 , n1c , n2c , i , branch_num;

           for( i = 0 ; i < currentLength ; ++i)
           {
                type_node* tmp = new type_node(9, p->vcvs.element_name);

                n1 = search( p -> vcvs.node1 , node_array) - 1;
                n2 = search( p -> vcvs.node2 , node_array) - 1;
                n1c= search( p -> vcvs.node1c, node_array) - 1;
                n2c= search( p -> vcvs.node2c, node_array) - 1;

                branch_num = search( p -> vcvs.element_name , name_array) - 1;

                if( n1 == -1)
                {
                    if( n1c == -1)
                    {
                        address_node *t2 = new address_node(  p -> vcvs.DC_value ,  &stamp[branch_num][n2c] , NULL);
                        address_node *t1 = new address_node(  -1 ,  &stamp[n2][branch_num] , t2);
                        address_node *t0 = new address_node(  -1 ,  &stamp[branch_num][n2] , t1);
                        tmp -> head -> next = t0;
                    }
                    else if(n2c == -1)
                    {
                        address_node *t2 = new address_node( -p -> vcvs.DC_value ,  &stamp[branch_num][n1c] , NULL);
                        address_node *t1 = new address_node(  -1 ,  &stamp[n2][branch_num] , t2);
                        address_node *t0 = new address_node(  -1 ,  &stamp[branch_num][n2] , t1);
                        tmp -> head -> next = t0;
                    }

                    else
                    {
                        address_node *t3 = new address_node(  p -> vcvs.DC_value ,  &stamp[branch_num][n2c] , NULL);
                        address_node *t2 = new address_node( -p -> vcvs.DC_value ,  &stamp[branch_num][n1c] , t3);
                        address_node *t1 = new address_node(  -1 ,  &stamp[n2][branch_num] , t2);
                        address_node *t0 = new address_node(  -1 ,  &stamp[branch_num][n2] , t1);
                        tmp -> head -> next = t0;
                    }

                }
                else if( n2 == -1)
                {
                    if( n1c == -1)
                    {
                        address_node *t2 = new address_node(  p -> vcvs.DC_value ,  &stamp[branch_num][n2c] , NULL);
                        address_node *t1 = new address_node(   1 ,  &stamp[n1][branch_num] , t2);
                        address_node *t0 = new address_node(   1 ,  &stamp[branch_num][n1] , t1);
                        tmp -> head -> next = t0;
                    }
                    else if(n2c == -1)
                    {
                        address_node *t2 = new address_node( -p -> vcvs.DC_value ,  &stamp[branch_num][n1c] , NULL);
                        address_node *t1 = new address_node(   1 ,  &stamp[n1][branch_num] , t2);
                        address_node *t0 = new address_node(   1 ,  &stamp[branch_num][n1] , t1);
                        tmp -> head -> next = t0;
                    }

                    else
                    {
                        address_node *t3 = new address_node(  p -> vcvs.DC_value ,  &stamp[branch_num][n2c] , NULL);
                        address_node *t2 = new address_node( -p -> vcvs.DC_value ,  &stamp[branch_num][n1c] , t3);
                        address_node *t1 = new address_node(   1 ,  &stamp[n1][branch_num] , t2);
                        address_node *t0 = new address_node(   1 ,  &stamp[branch_num][n1] , t1);

                        //cout <<"1111111111111111111111111"<< n1c << ' '<< n2c <<' '<< n1<<' ' << branch_num<<endl;
                        tmp -> head -> next = t0;
                    }

                }
                else if( n1c == -1)
                {


                    address_node *t4 = new address_node(  p -> vcvs.DC_value ,  &stamp[branch_num][n2c] , NULL);
                    address_node *t3 = new address_node(  -1 ,  &stamp[branch_num][n2] , t4);
                    address_node *t2 = new address_node(   1 ,  &stamp[branch_num][n1] , t3);
                    address_node *t1 = new address_node(  -1 ,  &stamp[n2][branch_num] , t2);
                    address_node *t0 = new address_node(   1 ,  &stamp[n1][branch_num] , t1);

                    tmp -> head -> next = t0;
                }
                else if( n2c == -1)
                {

                    address_node *t4 = new address_node( -p -> vcvs.DC_value ,  &stamp[branch_num][n1c] , NULL);
                    address_node *t3 = new address_node(  -1 ,  &stamp[branch_num][n2] , t4);
                    address_node *t2 = new address_node(   1 ,  &stamp[branch_num][n1] , t3);
                    address_node *t1 = new address_node(  -1 ,  &stamp[n2][branch_num] , t2);
                    address_node *t0 = new address_node(   1 ,  &stamp[n1][branch_num] , t1);

                    tmp -> head -> next = t0;
                }
                else
                {
                    //complex<double> v = p -> ind.DC_value / h;
                    address_node *t5 = new address_node(  p -> vcvs.DC_value ,  &stamp[branch_num][n2c] , NULL);
                    address_node *t4 = new address_node( -p -> vcvs.DC_value ,  &stamp[branch_num][n1c] , t5);
                    address_node *t3 = new address_node(  -1 ,  &stamp[branch_num][n2] , t4);
                    address_node *t2 = new address_node(   1 ,  &stamp[branch_num][n1] , t3);
                    address_node *t1 = new address_node(  -1 ,  &stamp[n2][branch_num] , t2);
                    address_node *t0 = new address_node(   1 ,  &stamp[n1][branch_num] , t1);
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
