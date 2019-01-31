#ifndef _LINKED_ORD_LIST_H
#define _LINKED_ORD_LIST_H

#include "linked_list.h"
#include <iostream>

using namespace std;

template<class T>
class Linked_ord_list : public Linked_list<T>{
public:
  typedef typename Linear_list<T, List_node<T>*>::value_type value_type;
  typedef typename Linear_list<T, List_node<T>*>::position position;
  Linked_ord_list(); //di default crescente
  Linked_ord_list(bool);
  Linked_ord_list(const Linked_ord_list<T>& l);
  bool getCrescente()const;
  void setCrescente(bool x); //solo se empty()==true
  void write(const value_type&); //trova la posizione giusta e inserisce
  bool is_in(const T)const;
  void merge(const Linked_ord_list<T>&);
  void merge2(const Linked_ord_list<T>&);

  Linked_ord_list<T>& operator=(const Linked_ord_list<T>& l);

private:
  void insert(const value_type&, position);
  bool crescente;
};

template <class T>
Linked_ord_list<T>::Linked_ord_list():Linked_list<T>::Linked_list(){
  crescente=true;
}

template <class T>
Linked_ord_list<T>::Linked_ord_list(bool x):Linked_list<T>::Linked_list(){
  crescente=x;
}

template <class T>
Linked_ord_list< T >::Linked_ord_list(const Linked_ord_list<T>& l):Linked_list<T>::Linked_list(l){
  crescente=l.crescente;
}

template <class T>
bool Linked_ord_list<T>::getCrescente()const{

  return crescente;

}

template <class T>
void Linked_ord_list<T>::setCrescente(bool x){
  if(this->Linked_list<T>::empty()){

    crescente=x;

  }
}

template<class T>
void Linked_ord_list<T>::write(const value_type& newvalue){

  position p;
  p=Linked_list<T>::begin();


if (!(this->Linked_list<T>::empty())){

  if(crescente==true){

    while(p->value<newvalue && !(this->Linked_list<T>::end(p))){

      p=p->_pNext;

    }

  }else{

    while(p->value>newvalue && !(this->Linked_list<T>::end(p))){

      p=p->_pNext;

    }

  }

}

  insert(newvalue, p);

}

template<class T>
void Linked_ord_list<T>::insert(const value_type& newvalue, position p){
  position t = new List_node<T>;

    t->value = newvalue;
    t->_pNext = p;
    t->_pPrev = p->_pPrev;
    p->_pPrev->_pNext = t;
    p->_pPrev = t;
	  Linked_list<T>::length++;
}

template <class T>
void Linked_ord_list<T>::merge(const Linked_ord_list<T>& L){

//this merge doesnt check if both the list are ascending or descending
  position p;
  p=L.Linked_list<T>::begin();
  while(!L.Linked_list<T>::end(p)){
    write(p->value);
    p=p->_pNext;
    Linked_list<T>::length++;

  }

}
template <class T>
void Linked_ord_list<T>::merge2(const Linked_ord_list<T>& L){

  if (this->getCrescente()==L.getCrescente()){

    if (this->getCrescente()==false){

      position p1=this->Linked_list<T>::begin();
      position p2=L.Linked_list<T>::begin();

      while (!this->Linked_list<T>::end(p1) && !L.Linked_list<T>::end(p2)){

        if(p2->value>p1->value){

          this->insert(p2->value, p1);
          p2=p2->_pNext;
          Linked_list<T>::length++;

        }else{

          p1=p1->_pNext;

        }

      }

      while(!L.Linked_list<T>::end(p2)){

        this->insert(p2->value, p1);
        p2=p2->_pNext;
        Linked_list<T>::length++;

      }

    }else{

      position p1=this->Linked_list<T>::begin();
      position p2=this->L.Linked_list<T>::begin();

      while (!this->Linked_list<T>::end(p1) && !L.Linked_list<T>::end(p2)){

        if(p2->value<p1->value){

          this->insert(p2->value, p1);
          p2=p2->_pNext;
          Linked_list<T>::length++;

        }else{

          p1=p1->_pNext;;

        }

      }

      while(!L.Linked_list<T>::end(p2)){
        this->insert(p2->value, p1);
        p2=p2->_pNext;
        Linked_list<T>::length++;

      }

    }

  }

}
template <class T>
bool Linked_ord_list<T>::is_in(const T v)const{
  if (Linked_list<T>::search(v)!=nullptr)
    return true;
  return false;
}

template <class T>
Linked_ord_list<T>& Linked_ord_list<T>::operator=(const Linked_ord_list<T>& l){

  if(this==&l) return *this;

  if(!this->empty()) this->clear();

  Linked_list<T>::_pHead=new List_node<T>;
  Linked_list<T>::_pHead->_pPrev=Linked_list<T>::_pHead;
  Linked_list<T>::_pHead->_pNext=Linked_list<T>::_pHead;

  Linked_list<T>::length=0;
  crescente=l.crescente;

  position p=l.begin();

  while(!l.end(p)){
    this->pushback(l.read(p));
    p=l.next(p);
  }

  return *this;
}

#endif //_LINKED_ORD_LIST_H
