#ifndef QUEUEPT_H
#define QUEUEPT_H

#include <iostream>

using namespace std;

template <class T>
class queue;

template <class T>
class node{
  friend class queue<T>;
  node *next;
  T value;
};

template <class T>
class queue{
public:
  queue(){
    head = nullptr;
    tail = nullptr;
    s = 0;
  }

  ~queue(){
    while(!empty())
      pop_front();
  }

  bool empty(){
    return (head == nullptr);
  }

  int size(){ return s;}

  void push_front(T v){
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

  void pop_front(){

    node<T> *tmp = head;
    head = head->next;
    delete tmp;
    s--;

  }

  T top(){return head->value;}

  void printCoda (){
    int i;
    i=0;
    while (i<size()){

      cout<<i+1<<"->"<<top()<<endl;
      push_front(top());
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
