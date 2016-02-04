
#include "model_vccs.h"

model_vccs::model_vccs()
{
    head = new vccs_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_vccs :: clear()
{
    vccs_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_vccs :: append( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v )
{
    vccs_node *tmp;
    vccs_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new vccs_node(name,n1,n2,n1c,n2c,v,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_vccs :: traverse()
{
    vccs_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> vccs.element_name << '\t' << p -> vccs.node1 << '\t' << p -> vccs.node2 << '\t'
             << p -> vccs.node1c << '\t' << p -> vccs.node2c << '\t' << p -> vccs.DC_value << endl;
        p = p->next;
    }
}

