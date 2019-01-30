#ifndef _QUEUEVT_H
#define _QUEUEVT_H
#include <iostream>
#define DEFAULTSIZE 10;

using namespace std;

template < class tipoelem >
class queue {

public:

  queue(int n);
  queue(const queue<tipoelem> &q);
  queue();
  ~queue();

  void create();
  bool empty();
  tipoelem top();
  void pop();
  void push(tipoelem a);

  queue<tipoelem>& operator=(const queue<tipoelem>& q);

  template<class tp>
  friend ostream& operator<<(ostream&, const queue<tp>&);

 private:
  tipoelem *elems;
  int head, length, maxlength;
};

template < class tipoelem >
queue<tipoelem>::queue(int n){
  maxlength = n;
  create();
}

template < class tipoelem >
queue<tipoelem>::queue(const queue<tipoelem> &q){

  head=q.head;
  length=q.length;
  maxlength=q.maxlength;
  elems=new tipoelem[q.maxlength];

  for (int i=head; i<length; i++)
    elems[i]=q.elems[i];

}

template < class tipoelem >
queue<tipoelem>::queue(){
  maxlength = DEFAULTSIZE;
  create();
}

template < class tipoelem >
queue<tipoelem>::~queue(){delete[] elems;}

template < class tipoelem >
void queue<tipoelem>::create(){
  elems = new tipoelem[maxlength];
  head = 0;
  length = 0;
}

template < class tipoelem >
bool queue<tipoelem>::empty(){
  return (length == 0);
}

template < class tipoelem >
tipoelem queue<tipoelem>::top(){
  if (!empty())
    return (elems[head]);
}

template < class tipoelem >
void queue<tipoelem>::pop(){
  if (!empty()){
    head = (head + 1) % maxlength;
    length--;
  }
}

template < class tipoelem >
void queue<tipoelem>::push(tipoelem a){
  if (length != maxlength){
    elems[(head+length) % maxlength] = a;
    length++;
  }
}

template < class tipoelem >
queue<tipoelem>& queue<tipoelem>::operator=(const queue<tipoelem>& q){

  if(this==&q) return *this;

  head=q.head;
  length=q.length;

  if(maxlength!=q.maxlength){
    delete[]elems;
    elems=new tipoelem[q.maxlength];
    maxlength=q.maxlength;
  }

  for (int i=head; i<length; i++)
    elems[i]=q.elems[i];

  return *this;

}

template<class tp>
ostream& operator<<(ostream& os, const queue<tp>& q){

  os<<"[";

  int i=q.head;
  while(i<q.length-1){

    os<<q.elems[i]<<", ";

    i++;
  }

  os<<q.elems[i];
  os<<"]"<<endl;

  return os;
}

#endif //QUEUEVT
