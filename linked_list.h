#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include "linear_list.h"
#include <iostream>

template<class T>
class Linked_list;

template<class T>
class Linked_ord_list;

template<class T>
class List_node{
	friend class Linked_list<T>;
	friend class Linked_ord_list<T>;
private:
	T value;
	List_node<T> * _pPrev;
	List_node<T> * _pNext;

};

template<class T>
class Linked_list : public Linear_list<T, List_node<T>*>{
public:
	typedef typename Linear_list<T, List_node<T>*>::value_type value_type;
	typedef typename Linear_list<T, List_node<T>*>::position position;

	Linked_list(); //costruttore generico;
	Linked_list(int); //costruttore con lunghezza in input;
	Linked_list(const Linked_list<T>&); //costruttore di copia;
	~Linked_list(); //distruttore;

	virtual void create(); //crealista;
	virtual void clear();  //cancellalista;
	virtual int size() const; //lunghezzalista;
	virtual bool empty() const; //listavuota;
	virtual bool end(position p) const; //finelista;
	virtual position begin() const; //primaposizione;
	virtual position last() const; //ultimaposizione;
	virtual value_type read(position) const; //leggilista;
	virtual position next(position) const; //posizionesuccessiva;
	virtual position previous(position) const; //posizioneprecedente;
	virtual void erase(position) const; //cancellaelemlista;
	void write(const value_type&, position); //scrivilista (scrivi un valore in una posizione);
	void insert(const value_type&, position); //inseriscilista (non sovrascrive, inserisce in una posizione con shift);
	virtual position search(const value_type&)const;
	virtual void pushback(const value_type&);
	virtual bool contains(const value_type&)const;
	//sovraccarico di operatori;
	Linked_list<T>& operator=(const Linked_list<T>&);
	bool operator==(const Linked_list<T>&) const;

private:
	List_node<T>* _pHead;
	int length;

};

template <class T>
Linked_list<T>::Linked_list(){
	_pHead=new List_node<T>;
	_pHead->_pPrev=_pHead;
	_pHead->_pNext=_pHead;
	length=0;
}

template <class T>
Linked_list<T>::Linked_list(int l){

	_pHead=new List_node<T>;

	if(l==0){

		_pHead->_pPrev=_pHead;
		_pHead->_pNext=_pHead;

	}else{
		int i;
		position p;

		p=_pHead;

		for(i=0; i<l; i++){

			p->_pNext=new List_node<T>;
			p->_pNext->_pPrev=p;
			p=p->_pNext;

		}

		_pHead->_pPrev=p;
		p->p_Next=_pHead;

	}

	length=l;

}

template <class T>
Linked_list<T>::Linked_list(const Linked_list<T>& L){

	_pHead=new List_node<T>;

	length=L.length;

	if(L.empty()){

		_pHead->_pPrev=_pHead;
		_pHead->_pNext=_pHead;

	}else{

		position p;

		p=L.last();

		for (int i=0; i<L.length; i++){

				insert(read(p), begin());
				p=L.previous(p);

		}

	}

}

template <class T>
Linked_list< T >::~Linked_list(){
	while(!empty()){
		erase(begin());
	}
	delete _pHead;
}

template< class T >
void Linked_list< T >::create(){
	if (empty())
			length = 0; //il resto lo fa il costruttore
}

template <class T>
void Linked_list<T>::clear(){

	while(!end(begin())){

		erase(begin());

	}
	delete _pHead;
	length=0;

}

template <class T>
int Linked_list<T>::size() const {return length;}

template <class T>
bool Linked_list<T>::empty() const {

	return (_pHead->_pNext==_pHead);

}

template <class T>
bool Linked_list<T>::end(position p) const {return (p==_pHead);}

template <class T>
typename Linked_list< T >::position Linked_list<T>::begin() const {return (_pHead->_pNext);}

template <class T>
typename Linked_list< T >::position Linked_list<T>::last() const {return (_pHead->_pPrev);}

template <class T>
typename Linked_list< T >::value_type Linked_list<T>::read(position p) const {

	if (!end(p)){

		return (p->value);

	}

}

template <class T>
typename Linked_list< T >::position Linked_list<T>::next(position p) const{return p->_pNext;}


template< class T >
typename Linked_list< T >::position Linked_list< T >::previous(position p) const {
	if (p != _pHead)
		return(p->_pPrev);
}

template< class T >
void Linked_list< T >::write(const value_type &a, position p) {
	if (!end(p))
    p->value = a;
}

template< class T >
void Linked_list< T >::insert(const value_type &a, position p){
	position t = new List_node<T>;
	t->value = a;
	t->_pNext = p;
	t->_pPrev = p->_pPrev;

	p->_pPrev->_pNext = t;
	p->_pPrev = t;

	length++;
}
template< class T >
void Linked_list< T >::pushback(const value_type& a){

	length++;
	if (this->empty()){
		insert(a, begin());
		return;
	}else{
		position t = new List_node<T>;
		t->value = a;
		t->_pNext = _pHead;
		t->_pPrev = last();
		last()->_pNext=t;
		_pHead->_pPrev=t;
	}
}


template< class T >
void Linked_list< T >::erase(position p)const{
	if (!empty() && !end(p)){
		p->_pPrev->_pNext = p->_pNext;
		p->_pNext->_pPrev = p->_pPrev;
		delete p;
	}
}


template<class T>
Linked_list<T>& Linked_list<T>::operator=(const Linked_list<T>& L){
	if (this != &L){

		_pHead = new List_node<T>;
		_pHead->_pNext = _pHead;
		_pHead->_pPrev = _pHead;


		if (!L.empty()){
            position p = L.last();
			for (int i=0; i < L.size(); i++){
				insert(L.read(p), begin());
				p = L.previous(p);
			}
		}
	}
	return *this;
}


template<class T>
bool Linked_list<T>::operator==(const Linked_list<T> &L) const{
	if (L.size() != length)
		return false;
	position p, pL;
	p = begin();
	pL = L.begin();
	while (!end(p)){
		if (p->value != pL->value)
			return false;
		p = p->_pNext;
		pL = pL->_pNext;
	}
	return true;
}

template <class T>
typename Linked_list<T>::position Linked_list<T>::search(const value_type& v)const{

	position p;
	p=begin();
	while (p!=_pHead){
		if (p->value==v)
			return p;
		p=next(p);
	}
	throw "not found"	;
	return nullptr;

}

template <class T>
bool Linked_list<T>::contains(const value_type& v)const{

	position p;
	p=begin();
	while (p!=_pHead){
		if (p->value==v)
			return true;
		p=next(p);
	}
	return false;

}
#endif // _LINKED_LIST_H
