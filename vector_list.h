#ifndef VECTOR_LIST_H
#define VECTOR_LIST_H

#include "linear_list.h"

#define DEFAULT_SIZE 10

template <class T>
class VectorList: public Linear_list<T, int>{
public:
  VectorList();
	VectorList(const VectorList &l);
  VectorList(int);
	~VectorList();

  VectorList &operator=(const VectorList &l);

  int begin() const;
  int last() const;
  bool end(int) const;
	T read(int) const;
	void write(int, T);
	int next(int) const;
	int prev(int) const;
  int search(T)const;
  void insert(int, T);
  void remove(int);
  void removeV(T);
	void clear();
	bool empty() const;
	size_t _size() const;
	void pushBack(T);
	void pushFront(T);
	void popBack();
	void popFront();

private:
  T* list; //
  size_t size; //how many elems can the list store
  int elems; //effective no of elems in the list
  void _resize (int);

};
template<typename T>
VectorList<T>::VectorList(){

  size=DEFAULT_SIZE;
  elems=0;
  list=new T[DEFAULT_SIZE];

}
template<typename T>
VectorList<T>::VectorList(const VectorList &l){

  size=l.size;
  elems=l.elems;
  this->list=new T[size];

  for (int i=0; i<elems; i++){
    this->list[i]=l.list[i];
  }

}
template<typename T>
VectorList<T>::VectorList(int sz){

  size=sz;
  elems=0;
  list=new T[size];

}
template<typename T>
VectorList<T>::~VectorList(){

  delete [] list;

}
template<typename T>
VectorList<T>& VectorList<T>::operator=(const VectorList &l){

  if (&l==this)
    return *this;
  this.size=l.size;
  this.elems=l.elems;
  delete [] this->list;

  this->list=new T [size];
  for (int i=0; i<elems; i++){
    this->list[i]=l.list[i];
  }
}
template<typename T>
int VectorList<T>::begin() const{return 0;}

template<typename T>
int VectorList<T>::last() const{return elems-1;}

template<typename T>
bool VectorList<T>::end(int p) const {return p==elems;}

template<typename T>
T VectorList<T>::read(int p) const {
  if (p<0 || p>=elems)
    throw "index out of bounds";
  return list[p];
}
template<typename T>
void VectorList<T>::write(int p, T v){
  if (p<0 || p>=elems)
    throw "index out of bounds";
  list[p]=v;
}
template<typename T>
int VectorList<T>::next(int p) const{return p+1;}

template<typename T>
int VectorList<T>::prev(int p) const{return p-1;}

template<typename T>
int VectorList<T>::search(T v)const{
  int i=begin();
  while(!end(i)){
    if (list[i]==v)
      return i;
    i=next(i);
  }
  return -1;
}
template<typename T>
void VectorList<T>::insert(int p, T v){
  if (p<0 || p>=elems)
    throw "index out of bounds";
  if (elems==size){
    _resize(2*size);
  }
  for (int i=elems; i>p; i--){
    list[i]=list[i-1];
  }

  list[p]=v;
  elems++;

}
template<typename T>
void VectorList<T>::remove(int p){
  if (p<0 || p>=elems)
    throw "index out of bounds";

  for (int i=p; i<elems-1; i++){
    list[i]=list[i+1];
  }
  elems--;
}

template<typename T>
void VectorList<T>::removeV(T v){
int p=search(v);
  if (p!=-1){
    for (int i=p; i<elems-1; i++){
      list[i]=list[i+1];
    }
    elems--;
  }

}
template<typename T>
void VectorList<T>::clear(){
  elems=0;
}

template<typename T>
bool VectorList<T>::empty() const{return elems==0;}

template<typename T>
size_t VectorList<T>::_size() const{return size;}

template<typename T>
void VectorList<T>::pushBack(T v){

  if (elems>=size){
    _resize(size*2);
  }
  list[elems]=v;
  elems++;

}
template<typename T>
void VectorList<T>::pushFront(T v){
  if (elems>=size){
    _resize(size*2);
  }
  for (int i=elems; i>0; i--)
    list[i]=list[i-1];
  list[0]=v;
  elems++;
}
template<typename T>
void VectorList<T>::popBack(){
  if (elems!=0)
    elems--;
}
template<typename T>
void VectorList<T>::popFront(){
  if (elems!=0){
    for (int i=0; i<elems-1; i++)
      list[i]=list[i+1];
    elems--;
  }
}
template<typename T>
void VectorList<T>::_resize(int newsize){
  T* tmp=new T[newsize];
  for (int i=0; i<elems; i++){
    tmp[i]=list[i];
  }
  T* tmp2=list;
  list=tmp;
  delete[] tmp2;
  size=newsize;
}
#endif
