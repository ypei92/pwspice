
#include "model_vcvs.h"

model_vcvs::model_vcvs()
{
    head = new vcvs_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_vcvs :: clear()
{
    vcvs_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_vcvs :: append( char* name , char* n1 , char* n2 , char* n1c , char* n2c , complex<double> v )
{
    vcvs_node *tmp;
    vcvs_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new vcvs_node(name,n1,n2,n1c,n2c,v,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_vcvs :: traverse()
{
    vcvs_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> vcvs.element_name << '\t' << p -> vcvs.node1 << '\t' << p -> vcvs.node2 << '\t'
             << p -> vcvs.node1c << '\t' << p -> vcvs.node2c << '\t' << p -> vcvs.DC_value << endl;
        p = p->next;
    }
}

