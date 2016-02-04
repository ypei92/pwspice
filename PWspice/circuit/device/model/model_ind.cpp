
#include "model_ind.h"

model_ind::model_ind()
{
    head = new ind_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_ind :: clear()
{
    ind_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_ind :: append( char* name , char* n1 ,  char* n2 , complex<double> v , complex<double> v_init)
{
    ind_node *tmp;
    ind_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new ind_node(name,n1,n2,v,v_init,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_ind :: traverse()
{
    ind_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> ind.element_name << '\t' << p -> ind.node1 << '\t' << p -> ind.node2 << '\t' << p -> ind.DC_value <<'\t'<< p -> ind.init_value << endl;
        p = p->next;
    }
}

