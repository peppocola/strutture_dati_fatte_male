#ifndef BINTREE_LIST_H
#define BINTREE_LIST_H
#include "bintreenode.h"
#include <iostream>

template <class T>
class bintree_list : public bintree<T, bintreenode<T>*>{
public:

  typedef typename bintree<T, bintreenode<T>*>::value_type value_type;
	typedef typename bintree<T, bintreenode<T>*>::Nodo Nodo;

  bintree_list();
  bintree_list(const bintree_list<T> &t);
  bintree_list& operator=(const bintree_list<T> &t);

  void create();
  bool empty() const;

  Nodo root() const;
  Nodo parent(Nodo) const;
  Nodo sx(Nodo) const;
  Nodo dx(Nodo) const;
  bool sx_empty(Nodo) const;
  bool dx_empty(Nodo) const;

  void erase(Nodo);

  value_type read(Nodo) const;
  void write(Nodo , value_type );

  void ins_root(value_type);
  void ins_sx(Nodo, value_type);
  void ins_dx(Nodo, value_type);
  void removeleft(bintreenode<T>* toremove);
  void removeright(bintreenode<T>* toremove);
  size_t getnonodes(){return nonodes;}

private:
  bintreenode<T>* _root;
  size_t nonodes;
  bintreenode<T>* copynode(const bintreenode<T>* tocopy, const bintreenode<T>* fa);
  void removenode(bintreenode<T>* toremove);
};

template <class T>
bintree_list<T>::bintree_list(){
  _root=nullptr;
  nonodes=0;
}

template <class T>
bintree_list<T>::bintree_list(const bintree_list<T> &t){

  nonodes=0;
  _root=bintree_list<T>::copynode(t._root, nullptr);

}

template <class T>
bintreenode<T>* bintree_list<T>::copynode(const bintreenode<T>* tocopy, const bintreenode<T>* fa){

  if (tocopy==nullptr)
    return nullptr;

  bintreenode<T> *newnode=new bintreenode<T>;
  newnode->father=fa;
  newnode->value=tocopy->value;
  newnode->Lchild=bintree_list<T>::copynode(tocopy->Lchild, tocopy);
  newnode->Rchild=bintree_list<T>::copynode(tocopy->Rchild, tocopy);
  nonodes++;
  return newnode;

}

template <class T>
bintree_list<T>& bintree_list<T>::operator=(const bintree_list<T> &t){

  if (this!=&t){

    _root->clear();
    delete _root;
    nonodes=0;
    _root=bintree_list<T>::copynode(t._root, nullptr);

  }

}

template <class T>
void bintree_list<T>::create(){
  if (!empty()){
    _root->clear();
  }
  _root=nullptr;
  _root->father=nullptr;
  nonodes=0;

}

template <class T>
bool bintree_list<T>::empty() const{
  return _root==nullptr;
}

template <class T>
typename bintree_list<T>::Nodo bintree_list<T>::root() const{
  return _root;
}

template <class T>
typename bintree_list<T>::Nodo bintree_list<T>::parent(Nodo n) const{
  return n->getFather();
}

template <class T>
typename bintree_list<T>::Nodo bintree_list<T>::sx(Nodo n) const{
  return n->getLChild();
}

template <class T>
typename bintree_list<T>::Nodo bintree_list<T>::dx(Nodo n) const{
  return n->getRChild();
}

template <class T>
bool bintree_list<T>::sx_empty(Nodo n) const{
  return n->getLChild()==nullptr;
}

template <class T>
bool bintree_list<T>::dx_empty(Nodo n) const{
  return n->getRChild()==nullptr;
}

template <class T>
void bintree_list<T>::erase(Nodo n){
  if (n->father==nullptr){
    removenode(n);
    _root=nullptr;

  }else if (n->father->getLChild()==n){
    removeleft(n->father);
  }else{
    removeright(n->father);
  }
}

template <class T>
typename bintree_list<T>::value_type bintree_list<T>::read(Nodo n) const{
  return n->value;
}

template <class T>
void bintree_list<T>::write(Nodo n, value_type v){
  n->value=v;
}

template <class T>
void bintree_list<T>::ins_root(value_type v){
  if (_root==nullptr){
    bintreenode<T>* tmp=new bintreenode<T>;
    tmp->value=v;
    _root=tmp;
    nonodes++;
  }else throw "tree already has a root";
}

template <class T>
void bintree_list<T>::ins_sx(Nodo position, value_type val){
  if(position->Lchild==nullptr){
    bintreenode<T>* newnode=new bintreenode<T>;
    newnode->father=position;
    newnode->value=val;
    position->Lchild=newnode;
    nonodes++;
  }else throw "a LEFTNODE already exists";
}

template <class T>
void bintree_list<T>::ins_dx(Nodo position, value_type val){
  if(position->Rchild==nullptr){
    bintreenode<T>* newnode=new bintreenode<T>;
    newnode->father=position;
    newnode->value=val;
    position->Rchild=newnode;
    nonodes++;
  }else throw "a RIGHTNODE already exists";

}

template <class T>
void bintree_list<T>::removenode(bintreenode<T>* toremove){

  if (toremove==nullptr) std::cout<<"isnull";
  if (toremove!=nullptr){
/*
    std::cout<<_root->value<<"root value"<<std::endl;
    std::cout<<_root->father<<"root father"<<std::endl;
    std::cout<<_root->Lchild<<"root LCHILD"<<std::endl;
    std::cout<<_root->Rchild<<"root RCHILD"<<std::endl;

    std::cout<<_root->Lchild<<"LCHILD"<<std::endl;
    std::cout<<_root->Lchild->value<<"value"<<std::endl;
    std::cout<<_root->Lchild->father->value<<"father value"<<std::endl;
    std::cout<<_root->Lchild->Lchild<<"   "<< _root->Lchild->Rchild<<" left e right"<<std::endl;
*/
    removenode(toremove->Lchild);
    removenode(toremove->Rchild);
    delete toremove;
    nonodes--;
  }
}

template <class T>
void bintree_list<T>::removeleft(bintreenode<T>* toremove){
  if (toremove!=nullptr){
    removenode(toremove->Lchild);
    toremove->Lchild=nullptr;
  }
}

template <class T>
void bintree_list<T>::removeright(bintreenode<T>* toremove){

  if (toremove!=nullptr){
    removenode(toremove->Rchild);
    toremove->Rchild=nullptr;
  }
}

#endif
