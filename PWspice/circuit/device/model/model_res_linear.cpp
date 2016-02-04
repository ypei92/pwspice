
#include "model_res_linear.h"

model_res_linear::model_res_linear()
{
    head = new res_linear_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_res_linear :: clear()
{
    res_linear_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_res_linear :: append( char* name , char* n1 ,  char* n2 , complex<double> v)
{
    res_linear_node *tmp;
    res_linear_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new res_linear_node(name,n1,n2,v,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_res_linear :: traverse()
{
    res_linear_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> res.element_name << '\t' << p -> res.node1 << '\t' << p -> res.node2 << '\t' << p ->res.DC_value << endl;
        p = p->next;
    }
}

