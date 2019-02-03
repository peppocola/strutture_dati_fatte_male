#ifndef GRAPHLIST_H
#define GRAPHLIST_H
#define DEFAULTSIZE 10

#include "graph.h"
#include "linked_list.h"

class NodoG{
 public:
  NodoG(int i){
    nodoId = i;
  }
  NodoG(){
  }
  int getId()const{ return nodoId; }
  void setId(int id) {nodoId = id;}
  friend ostream& operator<<(ostream&, const NodoG&);
 private:
  int nodoId;
};

ostream& operator<<(ostream& os, const NodoG& n){
  os<<n.nodoId;
  return os;
}


template<class P>
class InfoArco {
 public:
  P peso;
  NodoG _to;
  bool operator==(const InfoArco<P>& a)const{
    if(a._to.getId()==this->_to.getId())return true;
    return false;
  }
};


template<class E, class P>
  class InfoNodo {
 public:
  E   etichetta;
  bool vuoto;
  void* info;
  Linked_list<InfoArco<P> > archi;

  InfoNodo(){
    info = 0;
    vuoto = true;
  }
};



template<class E, class P>
  class GraphList : public Graph<E, P, NodoG > {
 public:
    typedef E Etichetta;
    typedef P Peso;
    typedef NodoG Nodo;
    typedef Arco_<Peso, Nodo> Arco;
    typedef Graph<Etichetta, Peso, Nodo> Graph_;
    typedef typename Graph_::ListaNodi ListaNodi;
    typedef typename Graph_::ListaNodiPos ListaNodiPos;

    GraphList();
    GraphList(int);
    ~GraphList();

    bool vuoto() const;
    void insNodo(NodoG&);
    void insArco(Nodo, Nodo, Peso);
    void cancNodo(Nodo);
    void cancArco(Nodo, Nodo);
    bool esisteNodo(Nodo);
    bool esisteArco(Nodo, Nodo);
    ListaNodi Adiacenti(Nodo) const ;
    ListaNodi list_nodi() const ;
    Etichetta leggiEtichetta(Nodo) const ;
    void scriviEtichetta(Nodo, Etichetta) ;
    Peso leggiPeso(Nodo, Nodo) const ;
    void scriviPeso(Nodo, Nodo, Peso) ;

    int numNodi(){
      return nodi;
    };
    int numArchi(){
      return archi;
    };


 private:
    InfoNodo<E,P>* matrice;
    int dimensione;
    int nodi;
    int archi;
};


template<class E, class P>
  GraphList<E, P>::GraphList(){
  dimensione = DEFAULTSIZE;
  nodi = 0;
  archi = 0;
  matrice = new InfoNodo<E,P>[dimensione];
  for (int i=0; i<dimensione; i++)
    matrice[i].archi.create();
}

template<class E, class P>
  GraphList<E, P>::GraphList(int _dimensione){
  dimensione = _dimensione;
  nodi = 0;
  archi = 0;
  matrice = new InfoNodo<E,P>[dimensione];
  for (int i=0; i<dimensione; i++)
    matrice[i].archi.create();
}

template<class E, class P>
  GraphList<E, P>::~GraphList() {
  delete [] matrice;
}

template<class E, class P>
  bool GraphList<E, P>::vuoto() const {
  return (nodi == 0);
}

template<class E, class P>
  void GraphList<E, P>::insNodo(Nodo& N) {
  int n = 0;
  if (nodi < dimensione){
    while (matrice[n].vuoto == false)
      n++;
    nodi++;
    matrice[n].vuoto = false;
  }
  N.setId(n);
}

template<class E, class P>
  void GraphList<E, P>::insArco(Nodo n1, Nodo n2, P peso) {

  if (esisteNodo(n1)&&esisteNodo(n2)){
    InfoArco<P> I;
    I.peso = peso;
    I._to = n2;
    matrice[n1.getId()].archi.insert(I, matrice[n1.getId()].archi.begin());
    archi++;
  }
}
//CHECK

template<class E, class P>
  void GraphList<E, P>::cancNodo(Nodo n) {
  // ATTENZIONE: controllare prima che non ci siano archi uscenti o entranti in n
  bool canc = true;
  int i;
  if (!matrice[n.getId()].archi.empty())
    canc = false;
  // TODO: implementare il controllo sugli archi entranti
  for (i=0; i < dimensione && canc; i++){

    if(!matrice[i].vuoto){
      Linked_list<InfoArco<P>> archi=matrice[i].archi;
      typename Linked_list<InfoArco<P>>::position tmp=archi.begin();

      while(canc && !archi.end(tmp)){
        if(archi.read(tmp)._to.getId()==n.getId()){
           canc=false;
        }else tmp=archi.next(tmp);
      }
    }
  }
  if (canc){
    // la lista  matrice[n.getId()].archi Ã¨ vuota;
    matrice[n.getId()].vuoto = true;
  }
}

template<class E, class P>
  void GraphList<E, P>::cancArco(Nodo n1, Nodo n2){
	typename Linked_list<InfoArco<P> >::position p;
	p = matrice[n1.getId()].archi.begin();
	bool trovato = false;
	while (!matrice[n1.getId()].archi.end(p) && !trovato){
		if (matrice[n1.getId()].archi.read(p)._to.getId() == n2.getId())
			trovato = true;
		else
				p = matrice[n1.getId()].archi.next(p);
	}
	if (trovato)
		matrice[n1.getId()].archi.erase(p);
  archi--;
}

template<class E, class P>
  typename GraphList<E, P>::ListaNodi GraphList<E, P>::Adiacenti(Nodo n) const{
  ListaNodi list;
  typename Linked_list<InfoArco<P>>::position p = matrice[n.getId()].archi.begin();
  while(!matrice[n.getId()].archi.end(p)){
    list.insert(new NodoG (matrice[n.getId()].archi.read(p)._to.getId()), list.begin());
    p=matrice[n.getId()].archi.next(p);
  }
  return list;

}

template<class E, class P>
  typename GraphList<E, P>::ListaNodi GraphList<E, P>::list_nodi() const {
  ListaNodi list;
  for (int i = 0; i < dimensione; i++)
    if (!matrice[i].vuoto)
      list.insert(new NodoG(i), list.begin());
  return list;
}

template<class E, class P>
  E GraphList<E, P>::leggiEtichetta(Nodo n) const {
  return matrice[n.getId()].etichetta;
}

template<class E, class P>
  void GraphList<E, P>::scriviEtichetta(Nodo n, E etichetta) {
  matrice[n.getId()].etichetta = etichetta;
}

template<class E, class P>
  P GraphList<E, P>::leggiPeso(Nodo n1, Nodo n2) const {
	typename Linked_list<InfoArco<P> >::position p;
	p = matrice[n1.getId()].archi.begin();
	bool trovato = false;
	while (!matrice[n1.getId()].archi.end(p) && !trovato){
		if (matrice[n1.getId()].archi.read(p)._to.getId() == n2.getId())
			trovato = true;
		else
				p = matrice[n1.getId()].archi.next(p);
	}
	if (trovato)
		return matrice[n1.getId()].archi.read(p).peso;
}

template<class E, class P>
  void GraphList<E, P>::scriviPeso(Nodo n1, Nodo n2, P peso) {
	typename Linked_list<InfoArco<P> >::position p;
	p = matrice[n1.getId()].archi.begin();
	bool trovato = false;
	while (!matrice[n1.getId()].archi.end(p) && !trovato){
		if (matrice[n1.getId()].archi.read(p)._to.getId() == n2.getId())
			trovato = true;
		else
				p = matrice[n1.getId()].archi.next(p);
	}
	if (trovato){
		InfoArco<P> I;
		I.peso = peso;
		I._to = n2;
		matrice[n1.getId()].archi.write(I,p);
	}
}

template<class E, class P>
bool GraphList<E, P>::esisteNodo(Nodo n){
  if (n.getId()>=dimensione) return false;
  if (matrice[n.getId()].vuoto) return false;
  return true;
}

template<class E, class P>
bool GraphList<E, P>::esisteArco(Nodo nodo1, Nodo nodo2){
  if (nodo1.getId()>=dimensione) return false;
  if (nodo2.getId()>=dimensione) return false;
  if (matrice[nodo1.getId()].vuoto) return false;
  if (matrice[nodo2.getId()].vuoto) return false;

  typename Linked_list<InfoArco<P> >::position p = matrice[nodo1.getId()].archi.begin();;

	while (!matrice[nodo1.getId()].archi.end(p)){
		if (matrice[nodo1.getId()].archi.read(p)._to.getId() == nodo2.getId())
			return true;
		else
				p = matrice[nodo1.getId()].archi.next(p);
	}
  return false;
}

#endif
