
#include "model_nmos.h"

model_nmos::model_nmos()
{
    head = new nmos_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_nmos :: clear()
{
    nmos_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_nmos :: append( char* name , char* n1 , char* n2 , char* n3 , complex<double> w , complex<double> l )
{
    nmos_node *tmp;
    nmos_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new nmos_node(name,n1,n2,n3,w,l,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_nmos :: traverse()
{
    nmos_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> nmos.element_name << '\t' << p -> nmos.node1 << '\t' << p -> nmos.node2 << '\t'
             << p -> nmos.source << '\t' << p -> nmos.DC_value << '\t' << p -> nmos.length << endl;
        p = p->next;
    }
}

