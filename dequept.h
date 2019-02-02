#ifndef DEQUEPT_H
#define DEQUEPT_H

#include <iostream>

using namespace std;

template <class T>
class dequept;

template <class T>
class node{
public:
  friend class dequept<T>;
  template<class tp>
  friend ostream& operator<<(ostream&, const dequept<tp>&);
  node(){
    next=nullptr;
    prev=nullptr;
  }
private:
  node *next;
  node *prev;
  T value;
};

template <class T>
class dequept{
public:
  dequept();
  dequept(const dequept<T>& dq);
  ~dequept();
  bool empty()const;
  int size()const;
  void push_front(T v);
  void push_back(T v);
  void pop_front();
  void pop_back();
  T top()const;
  T bot()const;

  dequept<T> operator=(const dequept<T>&);
  template<class tp>
  friend ostream& operator<<(ostream&, const dequept<tp>&);

private:
  node <T>* head;
  node <T>* tail;
  int s;
};

template <class T>
dequept<T>::dequept(){
  head = nullptr;
  tail = nullptr;
  s = 0;
}

template <class T>
dequept<T>::dequept(const dequept<T>& dq){

    s = 0;
    head = nullptr;
    tail = nullptr;
    node<T>*tmp=dq.head;

    while(tmp!=nullptr){
      push_back(tmp->value);
      tmp=tmp->next;
    }


}

template <class T>
dequept<T>::~dequept(){
  while(!empty()){
    pop_front();
  }
}

template <class T>
bool dequept<T>::empty()const{
  return (head == nullptr);
}

template <class T>
int dequept<T>::size()const{ return s;}

template <class T>
void dequept<T>::push_front(T v){

  node<T> *tmp = new node<T>;
  tmp->value = v;

  if (empty()){
    head = tail = tmp;
  }else{
    head->prev = tmp;
    tmp->next = head;
    head = tmp;
  }
  s++;
}

template <class T>
void dequept<T>::push_back(T v){

  node<T> *tmp = new node<T>;
  tmp->value = v;

  if (empty()){
    head = tail = tmp;
  }else{
    tail->next = tmp;
    tmp->prev = tail;
    tail = tmp;
  }
  s++;
}

template <class T>
void dequept<T>::pop_front(){

  if (size()==1){
    s--;
    delete head;
    head=nullptr;
    tail=nullptr;
  }else if (!empty()){
    node<T> *tmp = head;
    head->next->prev=nullptr;
    head = head->next;
    delete tmp;
    s--;
  }
}

template <class T>
void dequept<T>::pop_back(){

  if (size()==1){
    s--;
    delete tail;
    head=nullptr;
    tail=nullptr;
  }else if (!empty()){
    node<T> *tmp = tail;
    tail->prev->next=nullptr;
    tail = tail->prev;
    delete tmp;
    s--;
  }
}

template <class T>
T dequept<T>::top()const{return head->value;}

template <class T>
T dequept<T>::bot()const{return tail->value;}

template <class T>
dequept<T> dequept<T>::operator=(const dequept<T>& dp){

    if (this==&dp) return *this;
    while(!empty()) pop_back();

    node<T>*tmp=dp.head;

    while(tmp!=nullptr){
      push_back(tmp->value);
      tmp=tmp->next;
    }

    return *this;
}

template<class tp>
ostream& operator<<(ostream&os, const dequept<tp>&q){

  os<<"[ ";
  if (!q.empty()){
    node<tp>* tmp = q.head;

    while(tmp->next!=nullptr){
      os<<tmp->value<<", ";
      tmp=tmp->next;
    }
    os<<tmp->value;
  }
  os<<"]"<<endl;
  return os;
}
#endif
