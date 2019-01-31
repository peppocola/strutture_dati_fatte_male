#ifndef _DEQUEVT_H
#define _DEQUEVT_H
#define DEFAULTSIZE 10
#include <iostream>

using namespace std;

template < class tipoelem >
class deque {

public:
  deque();
  deque(int n);
  deque(const deque<tipoelem> &q);
  ~deque();
  void create();
  bool empty()const;
  tipoelem top()const;
  tipoelem bot()const;
  void pop_front();
  void pop_back();
  void push_back(const tipoelem);
  void push_front(const tipoelem);

  deque<tipoelem>& operator=(const deque<tipoelem>& q);

  template<class tp>
  friend ostream& operator<<(ostream&, const deque<tp>&);

 private:
  tipoelem *elems;
  int head, length, tail, maxlength;
};

template < class tipoelem >
deque<tipoelem>::deque(){
  maxlength = 10;
  create();
}

template < class tipoelem >
deque<tipoelem>::deque(int n){
  maxlength = n;
  create();
}

template < class tipoelem >
deque<tipoelem>::deque(const deque<tipoelem> &q){

  head=q.head;
  length=q.length;
  tail=q.tail;
  maxlength=q.maxlength;

  elems=new tipoelem[q.maxlength];
  for (int i=head; i<=length; i++)
    elems[i%maxlength]=q.elems[i%maxlength];
}

template < class tipoelem >
deque<tipoelem>::~deque(){
  delete[] elems;
}

template < class tipoelem >
void deque<tipoelem>::create(){
  elems = new tipoelem[maxlength];
  head = 0;
  tail = 0;
  length = 0;
}

template < class tipoelem >
bool deque<tipoelem>::empty()const{
  return (length==0);
}

template < class tipoelem >
tipoelem deque<tipoelem>::top()const{
  if (!empty()){
    return (elems[head]);
  }
}

template < class tipoelem >
tipoelem deque<tipoelem>::bot()const{
  if (!empty()){
    return elems[tail];
  }
}

template < class tipoelem >
void deque<tipoelem>::pop_front(){
  if (!empty()){
    head++;
    head = head % maxlength;
    length--;
  }

}

template < class tipoelem >
void deque<tipoelem>::pop_back(){
  if (!empty()){
    tail--;
    tail=tail % maxlength;
    length--;
  }
}

template < class tipoelem >
void deque<tipoelem>::push_back(const tipoelem a){

  if (empty()){
    elems[tail]=a;
    length++;
  }else if (length != maxlength){
    tail++;
    tail=tail%maxlength;
    elems[tail] = a;
    length++;
  }

}

template < class tipoelem >
void deque<tipoelem>::push_front(const tipoelem a){

  if(empty()){
    elems[head]=a;
    length++;
  }else if (length != maxlength){
    head--;
    if(head<0){
      head=head+maxlength;
    }
    elems[head] = a;
    length++;
  }

}

template < class tipoelem >
deque<tipoelem>& deque<tipoelem>::operator=(const deque<tipoelem>& q){

  if(this==&q) return *this;

  head=q.head;
  tail=q.tail;
  length=q.length;

  if(maxlength!=q.maxlength){
    delete[]elems;
    elems=new tipoelem[q.maxlength];
    maxlength=q.maxlength;
  }

  for (int i=head; i<=length; i++)
    elems[i%maxlength]=q.elems[i%maxlength];

  return *this;

}

template<class tp>
ostream& operator<<(ostream& os, const deque<tp>& q){

  os<<"[";

  if (!q.empty()){
    int i=q.head;
    int end;

    if (i>q.tail){
      end=q.maxlength+q.tail;
    }else end=q.tail;

    while(i<end){

      os<<q.elems[(i%q.maxlength)]<<", ";

      i++;
    }

    os<<q.elems[(i%q.maxlength)];
  }

  os<<"]"<<endl;

  return os;
}

#endif //DEQUEVT_
