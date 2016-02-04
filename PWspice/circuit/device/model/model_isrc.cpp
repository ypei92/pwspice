
#include "model_isrc.h"

model_isrc::model_isrc()
{
    head = new isrc_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_isrc :: clear()
{
    isrc_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_isrc :: append( char* name , char* n1 ,  char* n2 , complex<double> v)
{
    isrc_node *tmp;
    isrc_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new isrc_node(name,n1,n2,v,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_isrc :: traverse()
{
    isrc_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> isrc.element_name << '\t' << p -> isrc.node1 << '\t' << p -> isrc.node2 << '\t' << p ->isrc.DC_value << endl;
        p = p->next;
    }
}

