#ifndef HISTO_H
#define HISTO_H

#include <iostream>
#include <string>
#include "hash.h"

#define DEFAULTSIZE 10

using namespace std;

class histo{
public:
  histo();

  void add(int v);
  void remove(int v);
  int mode();
  double mean();
  void print();
private:
  hash_table<int, int> hist;

};

histo::histo():hist(DEFAULTSIZE){}

void histo::add(int v){

  if (!hist.contains(v)){
    hist.insert(v,1);
  }else{
    hist.insert(v, hist[v]+1);
  }
}

void histo::remove(int v){
  if(hist.contains(v) && hist[v]!=0){
    hist.insert(v, hist[v]-1);
  }
}

int histo::mode(){

  int max=0;
  int bestkey;
  Linked_list<int> keys=hist.keys();
  Linked_list<int>::position p=keys.begin();
  while (!keys.end(p)){
    int key = keys.read(p);

    if (hist[key]>max){
      max=hist[key];
      bestkey=key;
    }
    p=keys.next(p);

  }

  return bestkey;
}

double histo::mean(){

  Linked_list<int> keys=hist.keys();
  Linked_list<int>::position p=keys.begin();

  double result=0;
  while (!keys.end(p)){

    result+=keys.read(p);

    p=keys.next(p);

  }

  return result/keys.size();

}

void histo::print(){

    Linked_list<int> keys=hist.keys();
    Linked_list<int>::position p=keys.begin();

    while (!keys.end(p)){

      int key=keys.read(p);

      cout<<key<<" ";

      string value(hist[key], '*');

      cout<<value<<endl;

      p=keys.next(p);
    }
}

#endif
