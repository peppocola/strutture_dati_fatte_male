#ifndef PILAVT_H
#define PILAVT_H
#define DEFAULTSIZE 100

#include <iostream>

using namespace std;


template <class T>
class mystack
  {
  public:
    typedef T tipoelem;
    mystack();
    mystack(int);
    mystack(const mystack<T>& s);
    ~mystack();
    void create();
    bool empty() const;
    tipoelem top() const;
    void pop();
    void push(tipoelem);

    mystack<T>& operator=(const mystack<T>& s);

    template <class K>
    friend ostream& operator<<(ostream& os, const mystack<K>&s);

  private:
    tipoelem *elems;
    int MAXLENGTH;
    int head;
  };

template <class T>
mystack<T>::mystack()
{
  elems = new tipoelem[DEFAULTSIZE]; // dimensione standard della pila
  MAXLENGTH = DEFAULTSIZE;
  create();
}

template <class T>
mystack<T>::mystack(int N)
{
  if (N>0){
    elems = new tipoelem[N]; // dimensione N della pila
    MAXLENGTH = N;
    create();
  }else{
    elems = new tipoelem[DEFAULTSIZE];
    MAXLENGTH = DEFAULTSIZE;
    create();
  }
}

template <class T>
mystack<T>::mystack(const mystack<T>& s){

  MAXLENGTH=s.MAXLENGTH;
  head=s.head;
  elems=new tipoelem[MAXLENGTH];
  for(int i=0; i<head; i++){
    elems[i]=s.elems[i];
  }

}

template <class T>
mystack<T>::~mystack()
{
  delete[] elems;
};

template <class T>
void mystack<T>::create()
{
  head=0;
}

template <class T>
bool mystack<T>::empty() const
  {
    return head==0;
  }

template <class T>
T mystack<T>::top() const
  {
    return elems[head-1];
  }

template <class T>
void mystack<T>::pop()
{
  if (!empty())
    {
      head-=1;
    }
  else
    {
      cout<<"nessun elemento nella pila"<<endl;
    }
}

template <class T>
void mystack<T>::push(tipoelem el)
{
  if (head==MAXLENGTH)
    {
      cout<<"raggiunta capacità massima della pila"<<endl;
    }
  else
    {
      elems[head]=el;
      head++;
    }
}

template <class T>
mystack<T>& mystack<T>::operator=(const mystack<T>& s){

  if (this==&s) return *this;

  if(MAXLENGTH!=s.MAXLENGTH){
    delete[]elems;
    MAXLENGTH=s.MAXLENGTH;
  }
  elems=new tipoelem[MAXLENGTH];
  head=s.head;
  for(int i=0; i<head; i++){
    elems[i]=s.elems[i];
  }

  return *this;

}

template<class K>
ostream& operator<<(ostream& os, const mystack<K>&s){

  os<<"BOT[";
  if(!s.empty()){
    int i=0;
    while(i<s.head-1){
      os<<s.elems[i]<<"|";
      i++;
    }
    os<<s.elems[i];
  }
  os<<"]TOP"<<endl;

  return os;
}


#endif // _PILAVT_H
