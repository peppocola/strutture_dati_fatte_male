#ifndef TREENODE_H
#define TREENODE_H
#include "linked_list.h"

template<class T>
class Tree;

template<class T>
class treenode{

public:
  friend class Tree<T>;
  typedef Linked_list<treenode<T>*> listofchilds;
  treenode(){
    father=nullptr;
    label=-1;
  }
  treenode(T lab){
    label=lab;
    father=this;
  }
  treenode<T>* getFather() const;
  T getLabel() const;
  listofchilds& getChilds();
  treenode<T>* firstChild() const;
  treenode<T>* lastChild() const;
  treenode<T>* nextBro() const;
  treenode<T>* prevBro() const;
  bool hasChilds () const;
  bool isRoot () const;

private:
  T label;
  treenode<T>* father;
  Linked_list<treenode<T>*> childs;
};

template<class T>
treenode<T>* treenode<T>::getFather() const{return father;}

template<class T>
T treenode<T>::getLabel() const{return label;}

template<class T>
typename treenode<T>::listofchilds& treenode<T>::getChilds() {return childs;}

template<class T>
treenode<T>* treenode<T>::firstChild() const {return childs.read(childs.begin());}

template<class T>
treenode<T>* treenode<T>::lastChild() const {return childs.read(childs.last());}

template<class T>
treenode<T>* treenode<T>::nextBro() const {

  listofchilds childy =getChilds(father);
  return childy.read(childy.next(childy.search(this)));

}

template<class T>
treenode<T>* treenode<T>::prevBro() const {

  listofchilds childy =getChilds(father(this));
  return childy.read(childy.previous(childy.search(this)));

}

template<class T>
bool treenode<T>::hasChilds () const {return !(childs->empty());}

template<class T>
bool treenode<T>::isRoot () const {return father==nullptr;}

#endif
