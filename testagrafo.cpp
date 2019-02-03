#include "graph_mat.h"
#include <iostream>
#include <string>

using namespace std;

int main (void){

  Graph_mat<string, int> m;
  NodoG s;
  m.insNodo(s);
  NodoG g;
  m.insNodo(g);
  NodoG e;
  m.insNodo(e);

  m.insArco(e, g, 3);


  m.insArco(s, g, 2);

  if (m.esisteArco(e,s)) cout<<"TRUE"<<endl;

  m.scriviPeso(s,g,200);

  cout<<m<<endl;

  m.cancArco(s, g);

  cout<<m<<endl;

  m.cancArco(e, g);

  cout<<m<<endl;

  m.cancNodo(s);
  m.cancNodo(g);
  m.cancNodo(e);

  cout<<m<<endl;

  return 0;




}
