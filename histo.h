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

  friend ostream& operator<<(ostream& os, const histo& h);
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
  if(hist.contains(v)){
    if (hist[v]>=2){
      hist.insert(v, hist[v]-1);
    }else{
      hist.erase(v);
    }
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

ostream& operator<<(ostream& os, const histo& h){

  Linked_list<int> keys=h.hist.keys();
  Linked_list<int>::position p=keys.begin();

  while (!keys.end(p)){

    int key=keys.read(p);

    os<<key<<" ";

    string value(h.hist[key], '*');

    os<<value<<endl;

    p=keys.next(p);
  }
  return os;
}

#endif
