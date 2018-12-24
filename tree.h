#ifndef _TREE_H
#define _TREE_H
#define MAXNODES 100
#include <iostream>
#include "linked_list.h"
#include "treenode.h"

using namespace std;

template<class T>
class Tree{
public:
  typedef typename treenode<T>::listofchilds listofchilds;
  Tree();
  Tree(const Tree&);
  Tree &operator=(const Tree &t);
  ~Tree();
  treenode<T>* getRoot()const;
  bool empty () const;
  size_t size() const;
  void insRootNode(treenode<T>* node);
  void insRoot(T lab);
  void insSubTree(treenode<T>* node, Tree<T>& subtree);
  void removenode(treenode<T>* node);
  void clear();
  void insChild(treenode<T>*, T);
  void printTree(treenode<T>* t);
  int getNonodes() const {return nonodes;}
  int remainingNodes() const {return MAXNODES-nonodes;}

private:
  void printIt(treenode<T>* t);
  treenode<T>* copynode (treenode<T>* parent, treenode<T>* node);
  treenode<T>* root;
  size_t nonodes;
};
template<class T>
Tree<T>::Tree(){
    root=nullptr;
    nonodes=0;
}
template<class T>
Tree<T>::Tree(const Tree<T>& t){
  nonodes=0;
  root=copynode(nullptr, t.root);
}
template<class T>
Tree<T>& Tree<T>::operator=(const Tree<T> &t){

  if (this == &t) return *this;
  if(!empty()) clear();
  root=copynode(nullptr, t.root);

}

template<class T>
Tree<T>::~Tree(){
  removenode(root);
}

template<class T>
treenode<T>* Tree<T>::getRoot()const {return root;}

template<class T>
bool Tree<T>::empty () const {return root==nullptr;}

template<class T>
void Tree<T>::insRootNode(treenode<T>* node) {
  if (root==nullptr){
    root=node;
    nonodes++;
  }else{
    throw "a root is already stored";
  }
}

template<class T>
void Tree<T>::insRoot(T lab){
  if (root==nullptr){
    root= new treenode<T>;
    root->label=lab;
    root->father=nullptr;
    nonodes++;
  }else{
    throw "a root is already stored";
  }
}

template<class T>
void Tree<T>::insSubTree(treenode<T>* node, Tree<T>& subtree){

  if (node!=nullptr){
    if (nonodes+subtree.nonodes<=MAXNODES){

      node->childs.pushback(subtree.getRoot());
      nonodes+=subtree.nonodes;
      return;
    }else{
      throw "the subtree is too big";
    }
  }else{
    throw "the father is null, cannot insSubTree";
  }
}

template<class T>
size_t Tree<T>::size()const{return nonodes;}

template<class T>
void Tree<T>::removenode(treenode<T>* node){

  if (node!=nullptr){

    const listofchilds &childy=node->getChilds();
    List_node<treenode<T>*>*son=childy.begin();

      while(!childy.end(son)){

        removenode(childy.read(son));
        son=childy.next(son);

      }
      delete node;
      nonodes--;
  }

}
template<class T>
void Tree<T>::clear(){

  removenode(root);
  root=nullptr;


}

template<class T>
void Tree<T>::insChild(treenode<T>* node, T lab){

  if (nonodes==MAXNODES){
    throw "MAXNODES reached";
  }else{
    treenode<T>* baby=new treenode<T>;
    baby->father=node;
    baby->label=lab;
    node->childs.pushback(baby);
    nonodes++;
  }
}

template<class T>
void Tree<T>::printTree(treenode<T>* t){

  printIt(t);
  cout<<endl;

}


template<class T>
void Tree<T>::printIt(treenode<T>* t){

  if (t!=nullptr){

    cout<<"["<<t->label<<" ";

    const listofchilds &childy=t->getChilds();
    List_node<treenode<T>*>*son=childy.begin();

      while(!childy.end(son)){

        printIt(childy.read(son));
        son=childy.next(son);

      }
    cout<<"]";
  }

}


template<class T>
treenode<T>* Tree<T>::copynode (treenode<T>* parent, treenode<T>* node){

  if (node==nullptr){
    return nullptr;
  }
  treenode<T>* newnode=new treenode<T>;
  newnode->label=node->label;
  newnode->parent=parent;

  const listofchilds &childy=node->getChilds();
  List_node<treenode<T>*>*son=childy.begin();

  while(!childy.end(son)){

    treenode<T>* tmpnode=copynode(childy.read(son), newnode);
    newnode->childs.pushback(tmpnode);
    son=childy.next(son);

  }

  nonodes++;

  return newnode;
}


#endif
