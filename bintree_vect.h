#ifndef _BINTREE_VECT_H_
#define _BINTREE_VECT_H_
#include <iostream>
#define NIL -1

template <class T>
class bintree_vect{

public:

typedef T value_type;
typedef int Nodo;

  struct _cella{
      Nodo genitore;
      Nodo sinistro;
      Nodo destro;
      value_type valore;
    };

  typedef struct _cella Cella;

  // costruttori e distruttori
  bintree_vect();
  bintree_vect(int);
  ~bintree_vect();

  // operatori
  void create();
  bool empty() const;

  Nodo root() const;
  Nodo parent(Nodo) const;
  Nodo sx(Nodo) const;
  Nodo dx(Nodo) const;
  bool sx_empty(Nodo) const;
  bool dx_empty(Nodo) const;

  //void costr(bintree_vect<T>);
  void erase(Nodo);

  T read(Nodo) const;
  void write(Nodo , value_type );

  void ins_root(value_type);
  void ins_sx(Nodo, value_type);
  void ins_dx(Nodo, value_type);
  void print() const;

private:
  void printSubTree(const Nodo) const;
  int MAXLUNG;
  Cella *spazio;
  int nNodi;
  Nodo inizio; //radice
  Nodo libera; //prima posizione libera
};

template <class T>
bintree_vect<T>::bintree_vect()
{
MAXLUNG = 100;
spazio = new Cella[MAXLUNG];
create();
}

template <class T>
bintree_vect<T>::bintree_vect(int nNodi): MAXLUNG(nNodi)
{
spazio = new Cella[nNodi];
create();
}


template <class T>
bintree_vect<T>::~bintree_vect()
{
erase(inizio);
delete[] spazio;
}

template <class T>
void bintree_vect<T>::create()
{
inizio = NIL;
for (int i = 0; i < MAXLUNG; i++)
  {
    spazio[i].sinistro = (i+1) % MAXLUNG; //inizializza tutte le parti sinistre a (successiva posizione libera) (sono tutte libere ora)
  }

libera = 0;
nNodi = 0;
}

template <class T>
bool bintree_vect<T>::empty() const
{
return(nNodi == 0);
}

template <class T>
typename bintree_vect<T>::Nodo bintree_vect<T>::root() const
{
return(inizio);
}

template <class T>
typename bintree_vect<T>::Nodo bintree_vect<T>::parent(Nodo n) const
{
if (n != inizio)
  return (spazio[n].genitore);
else
  return(n);
}

template <class T>
typename bintree_vect<T>::Nodo bintree_vect<T>::sx(Nodo n) const
{
if (!sx_empty(n))
  return (spazio[n].sinistro);
else
  return(n);
};

template <class T>
typename bintree_vect<T>::Nodo bintree_vect<T>::dx(Nodo n) const
{
if (!dx_empty(n))
  return (spazio[n].destro);
else
  return(n);
}

template <class T>
bool bintree_vect<T>::sx_empty(bintree_vect<T>::Nodo n) const
{
return (spazio[n].sinistro == NIL);
}

template <class T>
bool bintree_vect<T>::dx_empty(bintree_vect<T>::Nodo n) const
{
return (spazio[n].destro == NIL);
}

template <class T>
void bintree_vect<T>::ins_root(bintree_vect<T>::value_type v)
{
if (inizio == NIL)
  {
    inizio = libera;
    libera = spazio[libera].sinistro;
    spazio[inizio].sinistro = NIL;
    spazio[inizio].destro = NIL;
    spazio[inizio].valore = v;
    nNodi++;
  }
else
  throw "a root already exists";
}


template <class T>
void bintree_vect<T>::ins_sx(bintree_vect<T>::Nodo n, bintree_vect<T>::value_type v )
{
  if (inizio == NIL)
    throw "the tree is empty";
  if (n == NIL)
    throw "the node is null";
  if (spazio[n].sinistro != NIL)
    throw "this node already exists";
  if (nNodi >= MAXLUNG)
    throw "reached full size";
  else
  {
    Nodo q = libera;
    libera = spazio[libera].sinistro;
    spazio[n].sinistro = q;
    spazio[q].sinistro = NIL;
    spazio[q].genitore = n;
    spazio[q].destro = NIL;
    spazio[q].valore = v;
    nNodi++;
  }
}

template <class T>
void bintree_vect<T>::ins_dx(bintree_vect<T>::Nodo n, bintree_vect<T>::value_type v )
{
  if (inizio == NIL)
    throw "the tree is empty";
  if (n == NIL)
    throw "the node is null";
  if (spazio[n].destro != NIL)
    throw "this node already exists";
  if (nNodi >= MAXLUNG)
    throw "reached full size";
  else
  {
    Nodo q = libera;
    libera = spazio[libera].sinistro;
    spazio[n].destro = q;
    spazio[q].genitore = n;
    spazio[q].sinistro = NIL;
    spazio[q].destro = NIL;
    spazio[q].valore = v;
    nNodi++;
  }
}

template <class T>
void bintree_vect<T>::erase(bintree_vect<T>::Nodo n)
{
if (n != NIL) {
    if (!sx_empty(n))
      erase(spazio[n].sinistro);
    if (!dx_empty(n))
      erase(spazio[n].destro);
    if (n != inizio) {
        Nodo p = parent(n);
        if (spazio[p].sinistro == n)
          spazio[p].sinistro = NIL;
        else
          spazio[p].destro = NIL;
      }
    else
      inizio = NIL;
    nNodi--;
    spazio[n].sinistro = libera;
    libera = n;
  }
else
  throw "the node is null";
}

template <class T>
T bintree_vect<T>::read(bintree_vect<T>::Nodo n) const
{
if (n != NIL)
  return (spazio[n].valore);
else
  throw "the node is null";
}

template <class T>
void bintree_vect<T>::write(bintree_vect<T>::Nodo n, bintree_vect<T>::value_type a)
{
if (n != NIL)
  spazio[n].valore = a;
else
  throw "the node is null";
}

template <class T>
void bintree_vect<T>::print() const{
	if (!empty())
		printSubTree(root());
	else
		std::cout << "[]" << std::endl;
	std::cout << std::endl;
}

template <class T>
void bintree_vect<T>::printSubTree(const Nodo n) const{
  if (sx_empty(n) && dx_empty(n)){
    std::cout << "[" << read(n) << "]";
    return;
  }
  std::cout << "[" << read(n) << ",";
	if (!sx_empty(n))
		printSubTree(sx(n));
	else std::cout << "[sxNIL]";
	std::cout << ",";
	if (!dx_empty(n))
		printSubTree(dx(n));
	else std::cout << "[dxNIL]";
	std::cout << "]";
}
template<class T>
std::ostream& operator<<(std::ostream& out, const bintree_vect<T>& t) {
    t.print();
    return out;
}

#endif /* _bintree_vect_H_ */
