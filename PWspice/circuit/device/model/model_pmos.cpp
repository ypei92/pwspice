
#include "model_pmos.h"
model_pmos::model_pmos()
{
    head = new pmos_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_pmos :: clear()
{
    pmos_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_pmos :: append( char* name , char* n1 , char* n2 , char* n3 , complex<double> w , complex<double> l )
{
    pmos_node *tmp;
    pmos_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new pmos_node(name,n1,n2,n3,w,l,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_pmos :: traverse()
{
    pmos_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> pmos.element_name << '\t' << p -> pmos.node1 << '\t' << p -> pmos.node2 << '\t'
             << p -> pmos.source << '\t' << p -> pmos.DC_value << '\t' << p -> pmos.length << endl;
        p = p->next;
    }
}
