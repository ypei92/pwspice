
#include "model_diode.h"

model_diode::model_diode()
{
    head = new diode_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_diode :: clear()
{
    diode_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_diode :: append( char* name , char* n1 ,  char* n2 , complex<double> v)
{
    diode_node *tmp;
    diode_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new diode_node(name,n1,n2,v,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_diode :: traverse()
{
    diode_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> diode.element_name << '\t' << p -> diode.node1 << '\t' << p -> diode.node2 << '\t' << p ->diode.DC_value << endl;
        p = p->next;
    }
}

