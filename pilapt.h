#ifndef PILAPT_H
#define PILAPT_H
#include <iostream>

using namespace std;

template <class T>
class mystackpt;

template <class T>
class cell{
public:
  friend class mystackpt<T>;
  cell(){
    prev=nullptr;
  }
  template <class K>
  friend ostream& operator<<(ostream& os, const mystackpt<K>&);
private:
  T value;
  cell *prev;
};

template <class T>
class mystackpt
  {
  public:
    typedef T tipoelem;

    mystackpt();
    mystackpt(const mystackpt<T>&);
    ~mystackpt();

    void create();
    bool empty() const;
    tipoelem top() const;
    void pop();
    void push(tipoelem);

    mystackpt<T>& operator=(const mystackpt<T>&);

    template <class K>
    friend ostream& operator<<(ostream& os, const mystackpt<K>&);

  private:
    cell<T>* head;
  };

template <class T>
mystackpt<T>::mystackpt()
{
  head = nullptr;
}

template <class T>
mystackpt<T>::mystackpt(const mystackpt<T>& p){

  if(!p.empty()){
    head=new cell<T>();
    head->value=p.head->value;

    cell<T>* tocpy=p.head->prev;
    cell<T>* whcpy=head;

    while(tocpy!=nullptr){

      cell<T>*tmp=new cell<T>();
      tmp->value=tocpy->value;

      whcpy->prev=tmp;

      tocpy=tocpy->prev;
      whcpy=whcpy->prev;
    }
  }else throw "can't copy empty stack";
}


template <class T>
mystackpt<T>::~mystackpt()
{
  while (!empty())
    pop();
};

template <class T>
void mystackpt<T>::create()
{
  head=nullptr;
}

template <class T>
bool mystackpt<T>::empty() const
  {
    return head==nullptr;
  }

template <class T>
T mystackpt<T>::top() const
  {
    return head->value;
  }

template <class T>
void mystackpt<T>::pop()
{
  if (!empty())
    {
      cell<T> *tmp = head;
      head = head->prev;
      delete tmp;
    }
}

template <class T>
void mystackpt<T>::push(tipoelem el)
{
  cell<T> *tmp = new cell<T>();
  tmp->value = el;
  tmp->prev = head;
  head = tmp;
}

template <class T>
mystackpt<T>& mystackpt<T>::operator=(const mystackpt<T>&p){

    if(this==&p) return *this;

    if(!p.empty()){

      while (!empty())
        pop();

      head=new cell<T>();
      head->value=p.head->value;

      cell<T>* tocpy=p.head->prev;
      cell<T>* whcpy=head;

      while(tocpy!=nullptr){

        cell<T>*tmp=new cell<T>();
        tmp->value=tocpy->value;

        whcpy->prev=tmp;

        tocpy=tocpy->prev;
        whcpy=whcpy->prev;

      }

    }else throw "can't copy empty stack";

    return *this;
}

template <class K>
ostream& operator<<(ostream& os, const mystackpt<K>&p){

  os<<"TOP[";

  if(!p.empty()){
    cell<K>* tmp=p.head;

    while(tmp->prev!=nullptr) {
      os<<tmp->value<<"|";
      tmp=tmp->prev;
    }
    os<<tmp->value;
  }
  
  os<<"]BOT"<<endl;

  return os;
}

#endif // _PILAVT_H
