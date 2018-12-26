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
  void insertL(bintreenode<T>* position, T val);
  void insertR(bintreenode<T>* position, T val);
  void insertLsub(bintreenode<T>* position, bintreenode<T>* sub);
  void insertRsub(bintreenode<T>* position, bintreenode<T>* sub);

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
bintreenode<T>::~bintreenode(){
  removeleft(this);
  removeright(this);
  delete this;
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

template <class T>
void bintreenode<T>::insertL(bintreenode<T>* position, T val){
  if(position->Lchild==nullptr){
    bintreenode<T>* newnode=new bintreenode<T>;
    newnode->father=position;
    newnode->value=val;
    position->Lchild=newnode;
  }else throw "a LEFTNODE already exists";
}

template <class T>
void bintreenode<T>::insertR(bintreenode<T>* position, T val){
  if(position->Rchild==nullptr){
    bintreenode<T>* newnode=new bintreenode<T>;
    newnode->father=position;
    newnode->value=val;
    position->Rchild=newnode;
  }else throw "a RIGHTNODE already exists";
}

template <class T>
void insertLsub(bintreenode<T>* position, bintreenode<T>* sub){
  if(position->Lchild==nullptr ){
    if (sub->father==nullptr){
      position->Lchild=sub;
      sub->father=position;
    }else throw "the node can't have 2 fathers, is the node adopted?";
  }else throw "a LEFTNODE already exists";
}

template <class T>
void insertRsub(bintreenode<T>* position, bintreenode<T>* sub){
  if(position->Rchild==nullptr ){
    if (sub->father==nullptr){
      position->Rchild=sub;
      sub->father=position;
    }else throw "the node can't have 2 fathers, is the node adopted?";
  }else throw "a RIGHTNODE already exists";
}


#endif
