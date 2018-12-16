#ifndef DEQUEPT_H
#define DEQUEPT_H

#include <iostream>

using namespace std;

template <class T>
class deque;

template <class T>
class node{
  friend class deque<T>;
  node *next;
  node *prev;
  T value;
};

template <class T>
class deque{
public:
  deque(){
    head = nullptr;
    tail = nullptr;
    s = 0;
  }

  ~deque(){
    while(!empty()){
      pop_front();
    }
  }
  bool empty(){
    return (head == nullptr);
  }

  int size(){ return s;}

  void push_front(T v){
    node<T> *tmp = new node<T>;

    tmp->value = v;
    tmp->prev = nullptr;
    tmp->next = head;

    if (empty()){
      head = tail = tmp;

    }else{

      head->prev = tmp;
      head = tmp;

    }

    s++;

  }

  void push_back(T v){
    node<T> *tmp = new node<T>;

    tmp->value = v;
    tmp->prev = tail;
    tmp->next = nullptr;

    if (empty()){

      head = tail = tmp;

    }else{

      tail->next = tmp;
      tail = tmp;

    }

    s++;

  }

  void pop_front(){

    if (size()==1){

      s--;
      delete head;
      head=nullptr;

    }else if (!empty()){

      node<T> *tmp = head;
      head->next->prev=nullptr;
      head = head->next;
      delete tmp;
      s--;

    }
  }

  void pop_back(){

    if (size()==1){

      s--;
      delete tail;
      tail=nullptr;

    }else if (!empty()){

      node<T> *tmp = tail;
      tail->prev->next=nullptr;
      tail = tail->prev;
      delete tmp;
      s--;

    }
  }

  T top(){return head->value;}

  T bot(){return tail->value;}

  void printCoda (){
    int i;
    i=0;
    while (i<size()){

      cout<<i+1<<"->"<<top()<<endl;
      push_back(top());
      pop_front();

      i++;


    }



  }

private:
  node <T>* head;
  node <T>* tail;
  int s;
};


#endif
