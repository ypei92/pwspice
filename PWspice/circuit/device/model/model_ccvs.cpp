
#include "model_ccvs.h"


model_ccvs::model_ccvs()
{
    head = new ccvs_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_ccvs :: clear()
{
    ccvs_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_ccvs :: append( char* name , char* n1 , char* n2 , char* vname , complex<double> v )
{
    ccvs_node *tmp;
    ccvs_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new ccvs_node(name,n1,n2,vname,v,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_ccvs :: traverse()
{
    ccvs_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> ccvs.element_name << '\t' << p -> ccvs.node1 << '\t' << p -> ccvs.node2 << '\t'
             << p -> ccvs.vname << '\t' << p -> ccvs.DC_value << endl;
        p = p->next;
    }
}

