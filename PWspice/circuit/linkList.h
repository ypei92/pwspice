#ifndef LINKLIST_H
#define LINKLIST_H
//#include<iostream>
//#include<cmath>
//using namespace std;



template <class elemType>
class list
{
    public:
       virtual void clear() = 0;
       virtual int length()const = 0;
       virtual void insert(int i , const elemType &x) = 0;
       virtual void remove(int i) = 0;
       virtual int search(const elemType &x)const = 0;
       virtual elemType visit(int i) const = 0;
       virtual void traverse()const = 0;
       virtual ~list(){};

};

template <class elemType>
class linkList:public list<elemType>
 {
     private:
        struct node
        {   int data;
            node *next;
            node(const int &x, node *p=NULL){data = x; next = p ;}
            node():next(NULL){}
        };
        int currentLength;
        node *head;

     public:
        linkList();
        linkList(const linkList &);
        ~linkList(){clear();delete head;}

        void clear();
        int length()const{return currentLength;}
        void insert(int i, const elemType  &x);
        void remove(int i);
        int search(const elemType &x)const ;
        elemType visit(int i) const;
        void traverse() const;

 };

 template<class elemType>
 linkList<elemType>::linkList()
 {
     head = new node;
     head -> next = NULL;
     currentLength = 0;
 }

 template<class elemType>
 linkList<elemType>::linkList(const linkList &a1)
 {
     head = new node;
     node *p=head , *q = a1.head->next;
     while(q)
     {
         p->next = new node(q->data);
         p = p->next;
         q = q->next;
     }
     currentLength = a1.currentLength;

 }


template<class elemType>
void linkList<elemType>::clear()
{
    node *q ,*p = head -> next  ;
    while(p != NULL)
    {
        q=p;
        p=p->next;
        delete q;
    }
    head -> next = NULL ;
}

template < class elemType >
void linkList <elemType> :: insert(int i , const elemType &x)
{
    node *tmp ,*p = head;
    int j = 0 ;
    for (j = 0,p = head; j<i ; ++j){p = p -> next ;}
    tmp = new node;
    tmp->data = x ;
    tmp->next = p -> next;
    p -> next = tmp ;

    ++currentLength;
}


template<class elemType>
void linkList<elemType>::remove(int i)
{
    node *p = head , *tmp;
    int j = 0;
    for(j = 0 , p=head; j<i ; ++j){p = p -> next;}
    tmp = p-> next;
    p -> next = tmp -> next ;
    delete tmp;
    --currentLength;
}

template<class elemType>
int linkList<elemType>::search(const elemType &x)const
{
    int num = 0;
    node *p = head -> next ;
    while (p!=NULL && p->data!=x)
    {
        ++num;
        p=p->next;
    }
    if(p==NULL) num = -1;
    return num;
}

template<class elemType>
elemType linkList<elemType>::visit(int i) const
{
    int j = 0;
    node *p = head ->next ;
    for( j = 0 , p= head->next ; j<i ; ++j) {p = p -> next;}
    return p -> data ;

}

template< class elemType >
void linkList<elemType>::traverse() const
{
    node *p = head -> next ;
    while (p != NULL)
    {
        cout << p->data;
        p = p->next;
    }
}
#endif
