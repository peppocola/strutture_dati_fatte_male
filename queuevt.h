#ifndef _QUEUEVT_H
#define _QUEUEVT_H

template < class tipoelem >
class Coda {

public:

  Coda(int n){
    maxlung = n;
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

 private:
  tipoelem *elementi;
  int testa, lung, maxlung;
};

#endif //QUEUEVT
