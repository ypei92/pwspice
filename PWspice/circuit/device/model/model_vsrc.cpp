
#include "model_vsrc.h"

model_vsrc::model_vsrc()
{
    head = new vsrc_node;
    head -> next = NULL;

    currentLength = 0;
}

void model_vsrc :: clear()
{
    vsrc_node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q = p;
        p = p -> next;
        delete q;
    }
    head -> next = NULL ;
}

void model_vsrc :: append( char* name , char* n1 ,  char* n2 , complex<double> v)
{
    vsrc_node *tmp;
    vsrc_node *p = head;
    int i = 0;
    for( i = 0 ; i < currentLength ; ++i) p = p -> next;

    tmp = new vsrc_node(name,n1,n2,v,NULL);
    p -> next = tmp;

    ++currentLength;
}

void model_vsrc :: traverse()
{
    vsrc_node *p = head -> next ;
    while (p != NULL)
    {
        cout << p -> vsrc.element_name << '\t' << p -> vsrc.node1 << '\t' << p -> vsrc.node2 << '\t' << p ->vsrc.DC_value << endl;
        p = p->next;
    }
}

