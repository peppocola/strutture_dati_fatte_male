#ifndef PILAPT_H
#define PILAPT_H
#include <iostream>

using namespace std;

template <class T>
class Pila;

template <class T>
class cella{
  friend class Pila<T>;
  T value;
  cella *prev;
};

template <class Elemento>
class Pila
  {
  public:
    typedef Elemento tipoelem;
    Pila();
    ~Pila();
    void creaPila();
    bool empty() const;
    tipoelem top() const;
    void pop();
    void push(tipoelem);
  private:
    cella<Elemento>* head;
  };

template <class Elemento>
Pila<Elemento>::Pila()
{
  head = nullptr;
}


template <class Elemento>
Pila<Elemento>::~Pila()
{
  while (!empty())
    pop();
};

template <class Elemento>
void Pila<Elemento>::creaPila()
{
  head=nullptr;
}

template <class Elemento>
bool Pila<Elemento>::empty() const
  {
    return head==nullptr;
  }

template <class Elemento>
Elemento Pila<Elemento>::top() const
  {
    return head->value;
  }

template <class Elemento>
void Pila<Elemento>::pop()
{
  if (!empty())
    {
      cella<Elemento> *tmp = head;
      head = head->prev;
      delete tmp;
    }
}

template <class Elemento>
void Pila<Elemento>::push(tipoelem el)
{
  cella<Elemento> *tmp = new cella<Elemento>();
  tmp->value = el;
  tmp->prev = head;
  head = tmp;
}

#endif // _PILAVT_H
