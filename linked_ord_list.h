#ifndef _LINKED_ORD_LIST_H
#define _LINKED_ORD_LIST_H

#include "linked_list.h"

template<class T>
class Linked_ord_list : public Linked_list<T>{
public:
  typedef typename Linear_list<T, List_node<T>*>::value_type value_type;
  typedef typename Linear_list<T, List_node<T>*>::position position;
  Linked_ord_list(); //di default crescente
  Linked_ord_list(bool);
  ~Linked_ord_list();
  bool getCrescente()const;
  void setCrescente(bool x); //solo se empty()==true
  void write(const value_type&); //trova la posizione giusta e inserisce
  bool is_in(const T);
  void merge(const Linked_ord_list<T>&);
  void merge2(const Linked_ord_list<T>&);

private:
  void insert(const value_type&, position);
  int length;
  List_node<T> * _pHead;
  bool crescente;
};

template <class T>
Linked_ord_list<T>::Linked_ord_list(){
  _pHead=new List_node<T>;
  _pHead->_pPrev=_pHead;
  _pHead->_pNext=_pHead;
  length=0;
  crescente=true;
}

template <class T>
Linked_ord_list<T>::Linked_ord_list(bool x){
  crescente=x;
  _pHead=new List_node<T>;
  _pHead->_pPrev=_pHead;
  _pHead->_pNext=_pHead;
  length=0;
}

template <class T>
Linked_ord_list< T >::~Linked_ord_list(){
	while(!this->Linked_list<T>::empty()){
		this->Linked_list<T>::erase(this->Linked_list<T>::begin());
	}
	delete _pHead;
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
	  length++;
}

template <class T>
void Linked_ord_list<T>::merge(const Linked_ord_list<T>& L){

//this merge doesnt check if both the list are ascending or descending
  position p;
  p=L.Linked_list<T>::begin();
  while(!L.Linked_list<T>::end(p)){
    write(p->value);
    p=p->_pNext;
    length++;

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
          length++;

        }else{

          p1=p1->_pNext;

        }

      }

      while(!L.Linked_list<T>::end(p2)){

        this->insert(p2->value, p1);
        p2=p2->_pNext;
        length++;

      }

    }else{

      position p1=this->Linked_list<T>::begin();
      position p2=L.Linked_list<T>::begin();

      while (!this->Linked_list<T>::end(p1) && !L.Linked_list<T>::end(p2)){

        if(p2->value<p1->value){

          this->insert(p2->value, p1);
          p2=p2->_pNext;
          length++;

        }else{

          p1=p1->_pNext;;

        }

      }

      while(!L.Linked_list<T>::end(p2)){
        this->insert(p2->value, p1);
        p2=p2->_pNext;
        length++;

      }

    }

  }

}
template <class T>
bool Linked_ord_list<T>::is_in(const T v){

  if (Linked_list<T>::search(v)!=nullptr)
    return true;
  return false;
}

#endif //_LINKED_ORD_LIST_H
