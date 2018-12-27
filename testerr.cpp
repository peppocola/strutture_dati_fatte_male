#include "bintree_list.h"
#include <iostream>
using namespace std;

int main (void){

  bintree_list<int> listy;
  listy.print();
  listy.ins_root(1);
  listy.ins_sx(listy.root(), 2);
  listy.print();
  cout<<listy.getnonodes()<<endl;
  listy.removeleft(listy.root());
  listy.print();
  return 0;
}
