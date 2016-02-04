#include "model_cap.h"

model_cap::model_cap()
{
    head = new cap_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_cap :: clear()
{
    cap_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_cap :: append( char* name , char* n1 ,  char* n2 , complex<double> v , complex<double> v_init)
{
    cap_node *tmp;
    cap_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new cap_node(name,n1,n2,v,v_init,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_cap :: traverse()
{
    cap_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> cap.element_name << '\t' << p -> cap.node1 << '\t' << p -> cap.node2 << '\t' << p -> cap.DC_value <<'\t'<< p -> cap.init_value << endl;
        p = p->next;
    }
}
