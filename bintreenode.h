#ifndef BINTREE_LIST_H
#define BINTREE_LIST_H
#include "bintree.h"

template <class>
class bintree_list;

template <class T>
class bintreenode{
  friend class bintree_list<T>;
  bintreenode();
  bintreenode(T);
  bintreenode(T val, bintreenode<T>* fa);
  bintreenode(const bintreenode<T> &btn);
  ~bintreenode();
  T getValue() const{return value;}
  bintreenode<T>* getFather() const{return father;}
  bintreenode<T>* getLChild() const{return Lchild;}
  bintreenode<T>* getRChild() const{return Rchild;}
  void removenode(bintreenode<T>*);
  bintreenode<T>& operator=(const bintreenode<T>* &node);
private:
  T value;
  bintreenode<T>* father;
  bintreenode<T>* Lchild;
  bintreenode<T>* Rchild;

  bintreenode<T>* copynode(bintreenode<T>*,bintreenode<T>*);

};

template <class T>
bintreenode<T>::bintreenode(){
  father=nullptr;
  Lchild=nullptr;
  Rchild=nullptr;
}

template <class T>
bintreenode<T>::bintreenode(T val){
  father=nullptr;
  Lchild=nullptr;
  Rchild=nullptr;
  value=val;
}

template <class T>
bintreenode<T>::bintreenode(T val, bintreenode<T>* fa){
  father=fa;
  Lchild=nullptr;
  Rchild=nullptr;
  value=val;
}

template <class T>
bintreenode<T>::bintreenode(const bintreenode<T> &btn){

  this=copynode(btn, btn->father);

}

template <class T>
bintreenode<T>& bintreenode<T>::operator=(const bintreenode<T>* &node){

  if (this!=node){
    this=removenode(this->Lchild, this);
    this=removenode(this->Rchild, this);
    bintreenode<T>*tmp=this;
    this=copynode(node, node->father);
    delete tmp;
    return this;
  }
}

template <class T>
bintreenode<T>* bintreenode<T>::copynode(bintreenode<T>* tocopy, bintreenode<T>* fa){

  if (tocopy==nullptr)
    return nullptr;

  bintreenode<T> *newnode=new bintreenode<T>;
  newnode->father=fa;
  newnode->value=tocopy->value;
  newnode->Lchild=copynode(tocopy->Lchild, tocopy);
  newnode->Rchild=copynode(tocopy->Rchild, tocopy);
  return newnode;

}

template <class T>
void bintreenode<T>::removenode(bintreenode<T>* toremove){

  if (toremove!=nullptr){
    removenode(toremove->Lchild);
    removenode(toremove->Rchild);
    delete toremove;
  }

}

#endif
