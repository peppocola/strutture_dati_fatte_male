#ifndef GRAPH_H
#define GRAPH_H

#include "linked_list.h"

template<class P, class N>
	class Arco_ {
 public:
	N nodo1;
	N nodo2;
	P peso;
};


template<class E, class P, class N>
	class Graph {
 public:
	typedef E Etichetta;
	typedef P Peso;
	typedef N Nodo;

	typedef Arco_<Peso, Nodo> Arco;
	typedef Linked_list<Nodo*> ListaNodi;
	typedef typename Linked_list<Nodo*>::position ListaNodiPos;
	typedef Linked_list<Arco> ListaArchi;

	virtual bool vuoto() const = 0;
	virtual void insNodo(Nodo&) = 0;
	virtual void insArco(Nodo, Nodo, Peso) = 0;
	virtual void cancNodo(Nodo) = 0;
	virtual void cancArco(Nodo, Nodo) = 0;
	virtual bool esisteNodo(Nodo) = 0;
	virtual bool esisteArco(Nodo, Nodo) = 0;
	virtual ListaNodi Adiacenti(Nodo) const = 0;
	virtual ListaNodi list_nodi() const = 0;
	virtual Etichetta leggiEtichetta(Nodo) const = 0;
	virtual void scriviEtichetta(Nodo, Etichetta) = 0;
	virtual Peso leggiPeso(Nodo, Nodo) const = 0;
	virtual void scriviPeso(Nodo, Nodo, Peso) = 0;

	virtual int numNodi() = 0;
	virtual int numArchi() = 0;

	virtual ~Graph(){};
	template <class A, class B, class C>
	friend ostream& operator<<(ostream&, const Graph<A,B,C>&);

};

template <class A, class B, class C>
ostream& operator<<(ostream& os, const Graph<A,B,C>& g){

	typedef C Nodo;
	typedef Linked_list<Nodo*> ListaNodi;
	ListaNodi l=g.list_nodi();
	typename ListaNodi::position p=l.begin();

	os<<"NODI :[";
	if(!l.empty()){
		while(!l.end(l.next(p))){
			os<<*l.read(p)<<", ";
			p=l.next(p);
		}
		os<<*l.read(p);
	}
	os<<"]"<<endl;
	p=l.begin();

	if(!l.empty()){
	os<<"ARCHI :"<<endl;;
		while(!l.end(p)){
			os<<*l.read(p)<<"->";
			ListaNodi a=g.Adiacenti(*l.read(p));
			typename ListaNodi::position f=a.begin();

			os<<"[";
			if(!a.empty()){
				while(!a.end(a.next(f))){
					os<<*a.read(f);
					os<<"(";
					os<<g.leggiPeso(*l.read(p), *a.read(f))<<"), ";
					f=a.next(f);
				}
				os<<*a.read(f);
				os<<"(";
				os<<g.leggiPeso(*l.read(p), *a.read(f))<<")";
			}
			os<<"]"<<endl;
			p=l.next(p);
		}
	}

	return os;
}


#endif
