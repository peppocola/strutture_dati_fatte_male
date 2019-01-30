#ifndef _QUEUEVT_H
#define _QUEUEVT_H
#include <iostream>
#define DEFAULTSIZE 10;

using namespace std;

template < class tipoelem >
class Coda {

public:

  Coda(int n){
    maxlung = n;
    creaCoda();
  }

  Coda(Coda<tipoelem> &q){

    testa=q.testa;
    lung=q.lung;
    maxlung==q.maxlung;
    elementi=new tipoelem[q.maxlung];

    for (int i=testa; i<lung; i++)
      elementi[i]=q.elementi[i];

  }

  Coda(){
    maxlung = DEFAULTSIZE;
    creaCoda();
  }

  ~Coda(){delete[] elementi;}

  void creaCoda(){
    elementi = new tipoelem[maxlung];
    testa = 0;
    lung = 0;
  }

  bool codaVuota(){
    return (lung == 0);
  }

  tipoelem leggiCoda(){
    if (!codaVuota())
      return (elementi[testa]);
  }

  void fuoriCoda(){
    if (!codaVuota()){
      testa = (testa + 1) % maxlung;
      lung--;
    }
  }

  void inCoda(tipoelem a){
    if (lung != maxlung){
      elementi[(testa+lung) % maxlung] = a;
      lung++;
    }
  }

  Coda<tipoelem>& operator=(const Coda<tipoelem>& q){

    testa=q.testa;
    lung=q.lung;

    if(maxlung!=q.maxlung){
      delete[]elementi;
      elementi=new tipoelem[q.maxlung];
      maxlung=q.maxlung;
    }

    for (int i=testa; i<lung; i++)
      elementi[i]=q.elementi[i];

  }

  template<class tp>
  friend ostream& operator<<(ostream&, const Coda<tp>&);

 private:
  tipoelem *elementi;
  int testa, lung, maxlung;
};

template<class tp>
ostream& operator<<(ostream& os, const Coda<tp>& q){

  os<<"[";

  int i=q.testa;
  while(i<q.lung-1){

    os<<q.elementi[i]<<", ";

    i++;
  }

  os<<q.elementi[i];
  os<<"]";

  return os;
}

#endif //QUEUEVT
