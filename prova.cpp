#include "tree.h"
#include <iostream>
using namespace std;

int main (void){

  Tree<int> prova;
  Tree<int> subprova;
  prova.insRoot(1);
  prova.insChild(prova.getRoot(),2);
  prova.insChild(prova.getRoot(),4);
  prova.insChild(prova.getRoot(),4);
  prova.insChild(prova.getRoot()->firstChild(), 3);

  subprova.insRoot(2);
  subprova.insChild(subprova.getRoot(),6);
  subprova.insChild(subprova.getRoot(),7);
  subprova.insChild(subprova.getRoot(),8);
  subprova.insChild(subprova.getRoot(),9);

  prova.printTree(prova.getRoot());
  subprova.printTree(subprova.getRoot());

  prova.insSubTree(prova.getRoot()->lastChild(), subprova);
  prova.printTree(prova.getRoot());
  return 0;
}
