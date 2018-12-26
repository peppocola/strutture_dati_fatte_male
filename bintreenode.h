#ifndef BINTREENODE_H
#define BINTREENODE_H
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
  bintreenode<T>& operator=(const bintreenode<T>* &node);
  void clear();
  void removeleft(bintreenode<T>* toremove);
  void removeright(bintreenode<T>* toremove);

private:
  T value;
  bintreenode<T>* father;
  bintreenode<T>* Lchild;
  bintreenode<T>* Rchild;
  void removenode(bintreenode<T>*);
  bintreenode<T>* copynode(const bintreenode<T>*tocopy, const bintreenode<T>*fa);

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

  this=copynode(btn, nullptr);

}

template <class T>
bintreenode<T>& bintreenode<T>::operator=(const bintreenode<T>* &node){

  if (this!=node){
    clear();
    this=copynode(node, nullptr);
  }
  return *this;
}

template <class T>
void bintreenode<T>::clear(){
  removeleft(this);
  removeright(this);
  delete this;
  this=nullptr;
}

template <class T>
bintreenode<T>* bintreenode<T>::copynode(const bintreenode<T>* tocopy, const bintreenode<T>* fa){

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

template <class T>
void bintreenode<T>::removeleft(bintreenode<T>* toremove){

  if (toremove!=nullptr){
    removenode(toremove->Lchild);
    toremove->Lchild=nullptr;
  }
}

template <class T>
void bintreenode<T>::removeright(bintreenode<T>* toremove){

  if (toremove!=nullptr){
    removenode(toremove->Rchild);
    toremove->Rchild=nullptr;
  }
}

#endif
