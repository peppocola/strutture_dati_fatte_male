#ifndef QUEUEPT_H
#define QUEUEPT_H

#include <iostream>

using namespace std;

template <class T>
class queue;

template <class T>
class node{
public:
  friend class queue<T>;
  node(){
    next=nullptr;
  }
  node(node<T>&n){
    value=n.value;
    next=nullptr;
  }
  template<class K>
  friend ostream& operator<<(ostream& os, const queue<K>& q);

private:
  node *next;
  T value;
};

template <class T>
class queue{
public:
  queue();
  queue(const queue<T>& q);
  ~queue();
  bool empty();
  int size();
  void push(T v);
  void pop();
  T top();
  void print();

  queue<T>& operator=(const queue<T>&);

  template<class K>
  friend ostream& operator<<(ostream& os, const queue<K>& q);

private:
  node <T>* head;
  node <T>* tail;
  int s;
};

template <class T>
queue<T>::queue(){
  head = nullptr;
  tail = nullptr;
  s = 0;
}

template <class T>
queue<T>::queue(const queue<T>& q){

  head=tail=nullptr;
  s=0;
  node<T>*tmp=q.head;

  while(tmp!=nullptr){

    push(tmp->value);
    tmp=tmp->next;
  }
}

template <class T>
queue<T>::~queue(){
  while(!empty())
    pop();
}

template <class T>
bool queue<T>::empty(){
  return (head == nullptr);
}

template <class T>
int queue<T>::size(){ return s;}

template <class T>
void queue<T>::push(T v){
  node<T> *tmp = new node<T>;

  if (empty()){

    head = tail = tmp;

  }else{

    tail->next = tmp;

  }

  tmp->next = nullptr;
  tmp->value = v;
  tail = tmp;
  s++;

}

template <class T>
void queue<T>::pop(){

  node<T> *tmp = head;
  head = head->next;
  delete tmp;
  s--;

}

template <class T>
T queue<T>::top(){return head->value;}

template <class T>
void queue<T>::print(){

  node<T>* tmp = head;
  int i=0;
  while(tmp!=nullptr){
    cout<<i<<" :["<<tmp->value<<"]"<<endl;
    tmp=tmp->next;
    i++;
  }
}

template <class T>
queue<T>& queue<T>::operator=(const queue<T>&q){

  if (this==&q) return *this;

  while(!empty()){
    pop();
  }
  node<T>* tmp = q.head;
  while(tmp!=nullptr){
    push(tmp->value);
    tmp=tmp->next;
  }
  return *this;
}

template<class K>
ostream& operator<<(ostream& os, const queue<K>& q){

  node<K>* tmp = q.head;
  int i=0;
  while(tmp!=nullptr){
    os<<i<<" :["<<tmp->value<<"]"<<endl;
    tmp=tmp->next;
    i++;
  }

  return os;
}

#endif
