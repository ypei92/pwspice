#include "model_cccs.h"

model_cccs::model_cccs()
{
    head = new cccs_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_cccs :: clear()
{
    cccs_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_cccs :: append( char* name , char* n1 , char* n2 , char* vname , complex<double> v )
{
    cccs_node *tmp;
    cccs_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new cccs_node(name,n1,n2,vname,v,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_cccs :: traverse()
{
    cccs_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> cccs.element_name << '\t' << p -> cccs.node1 << '\t' << p -> cccs.node2 << '\t'
             << p -> cccs.vname << '\t' << p -> cccs.DC_value << endl;
        p = p->next;
    }
}
