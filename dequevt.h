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
    coda= 0;
    lung = 0;
  }

  bool codaVuota(){
    return (lung == 0);
  }

  tipoelem top(){
    if (!codaVuota()){
      return (elementi[testa]);
    }
  }

  tipoelem bot(){
    if (!codaVuota()){
      return (elementi[coda]);
    }
  }

  void pop_front(){
    if (!codaVuota()){
      testa = (testa + 1) % maxlung;
      lung--;
    }
  }

  void pop_back(){
    if (!codaVuota()){
      coda = (coda - 1) % maxlung;
      lung--;
    }
  }


  void push_back(tipoelem a){
    if (lung != maxlung){
      elementi[(testa+lung) % maxlung] = a;
      lung++;
      coda=(testa+lung) % maxlung;
    }
  }

  void push_front(tipoelem a){
    if (lung != maxlung){
      elementi[(testa-1) % maxlung] = a;
      lung++;
      testa=(testa-1)%maxlung;
    }
  }

 private:
  tipoelem *elementi;
  int testa, coda, lung, maxlung;
};

#endif //CODAVT_
