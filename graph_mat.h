#ifndef GRAPH_MAT_H
#define GRAPH_MAT_H
#define DEFAULTSIZE 10

#include "graph.h"

template<class P>
class InfoArco {
 public:
	P peso;
	bool vuoto;

	InfoArco(){
		vuoto = true;
	}
};


template<class E, class P>
	class InfoNodo {
 public:
	E   etichetta;
	bool vuoto;
	void* info;
	InfoArco<P>* archi;

	InfoNodo(){
		info = 0;
		vuoto = true;
	}

	~InfoNodo(){
		if (!vuoto)
			delete [] archi;
	}
};


class NodoG{
 public:
	NodoG(int i){
		nodoId = i;
	}
	NodoG(){
	}
	int getId(){ return nodoId; }
	void setId(int id) {nodoId = id;}
  friend ostream& operator<<(ostream&, const NodoG&);
  bool operator==(const NodoG& g){
    if (this->getId()==g.getId()) return true;
    return false;
  }
 private:
	int nodoId;
};

ostream& operator<<(ostream& os, const NodoG& n){
  os<<n.nodoId;
  return os;
}

template<class E, class P>
	class Graph_mat : public Graph<E, P, NodoG > {
 public:
    typedef E Etichetta;
    typedef P Peso;
    typedef NodoG Nodo;
    typedef Arco_<Peso, Nodo> Arco;
    typedef Graph<Etichetta, Peso, Nodo> Graph_;
    typedef typename Graph_::ListaNodi ListaNodi;
		typedef typename Graph_::ListaNodiPos ListaNodiPos;

    Graph_mat();
    Graph_mat(int);
    ~Graph_mat();

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
	Graph_mat<E, P>::Graph_mat(){
	dimensione = DEFAULTSIZE;
	nodi = 0;
	archi = 0;
	matrice = new InfoNodo<E,P>[dimensione];
	for (int i=0; i<dimensione; i++)
		matrice[i].archi = new InfoArco<P>[dimensione];
}

template<class E, class P>
	Graph_mat<E, P>::Graph_mat(int _dimensione){
	dimensione = _dimensione;
	nodi = 0;
	archi = 0;
	matrice = new InfoNodo<E,P>[dimensione];
	for (int i=0; i<dimensione; i++)
		matrice[i].archi = new InfoArco<P>[dimensione];
}

template<class E, class P>
	Graph_mat<E, P>::~Graph_mat() {
	delete [] matrice;
}

template<class E, class P>
	bool Graph_mat<E, P>::vuoto() const {
	return (nodi == 0);
}

template<class E, class P>
	void Graph_mat<E, P>::insNodo(Nodo& N) {
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
	void Graph_mat<E, P>::insArco(Nodo n1, Nodo n2, P peso) {
	matrice[n1.getId()].archi[n2.getId()].peso = peso;
	matrice[n1.getId()].archi[n2.getId()].vuoto = false;
	archi++;
}


template<class E, class P>
	void Graph_mat<E, P>::cancNodo(Nodo n) {
	// ATTENZIONE: controllare prima che non ci siano archi uscenti o entranti in n
	bool canc = true;
	int i;
	for (i=0; i < dimensione && canc; i++)
		if (!matrice[n.getId()].archi[i].vuoto)
			canc = false;
	for (i=0; i < dimensione && canc; i++)
		if (!matrice[i].vuoto && !matrice[i].archi[n.getId()].vuoto)
			canc = false;

	if (canc){
		delete matrice[n.getId()].archi;
		matrice[n.getId()].vuoto = true;
    nodi--;
	}
}

template<class E, class P>
	void Graph_mat<E, P>::cancArco(Nodo n1, Nodo n2){
	matrice[n1.getId()].archi[n2.getId()].vuoto = true;
	archi--;
}

template<class E, class P>
	typename Graph_mat<E, P>::ListaNodi Graph_mat<E, P>::Adiacenti(Nodo n) const{
	ListaNodi list;

	for (int i = 0; i < dimensione; i++) {
		if (!matrice[n.getId()].archi[i].vuoto) {
			list.insert(new NodoG(i), list.begin());
		}
	}
	return list;
}

template<class E, class P>
	typename Graph_mat<E, P>::ListaNodi Graph_mat<E, P>::list_nodi() const {
	ListaNodi list;
	for (int i = 0; i < dimensione; i++)
		if (!matrice[i].vuoto)
			list.insert(new NodoG(i), list.begin());
	return list;
}

template<class E, class P>
	E Graph_mat<E, P>::leggiEtichetta(Nodo n) const {
	return matrice[n.getId()].etichetta;
}

template<class E, class P>
	void Graph_mat<E, P>::scriviEtichetta(Nodo n, E etichetta) {
	matrice[n.getId()].etichetta = etichetta;
}

template<class E, class P>
	P Graph_mat<E, P>::leggiPeso(Nodo n1, Nodo n2) const {
	return matrice[n1.getId()].archi[n2.getId()].peso;
}

template<class E, class P>
	void Graph_mat<E, P>::scriviPeso(Nodo n1, Nodo n2, P peso) {
	matrice[n1.getId()].archi[n2.getId()].peso = peso;
}

template<class E, class P>
bool Graph_mat<E, P>::esisteNodo(Nodo n){
  if(matrice[n.getId()].vuoto) return false;
  return true;
}

template<class E, class P>
bool Graph_mat<E, P>::esisteArco(Nodo nodo1, Nodo nodo2){
  if(matrice[nodo1.getId()].archi[nodo2.getId()].vuoto) return false;
  return true;
}

#endif
