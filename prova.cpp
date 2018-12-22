#include "tree.h"
#include <iostream>
using namespace std;

int main (void){

  Tree<int> prova;
  prova.insRoot(1);
  prova.insChild(prova.getRoot(),2);  //qui usa la funzione insert della lista perchè è ancora vuota
  prova.insChild(prova.getRoot(),4);  //qui usa pushback perchè c'è qualcosa dentro alla lista
  prova.insChild(prova.getRoot(),4); //qui utilizza pushback per la seconda volta ma sorge il problema doublefree or corruption
  //le funzioni incriminate sono: insChild, pushback

//
/*
  prova.printTree(prova.getRoot());



 prova.insChild(prova.getRoot(),6);
 prova.insChild(prova.getRoot(),7);
 prova.insChild(prova.getRoot(),8);
 prova.insChild(prova.getRoot(),9);
  prova.insChild(prova.getRoot()->firstChild(), 3);

  prova.printTree(prova.getRoot());
*/
  return 0;
}
