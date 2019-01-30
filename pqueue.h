#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_
#include <iostream>

using namespace std;

template < class T > class PQueue {

public:
  typedef T _value_type;
  PQueue ();
  PQueue (int);
  PQueue (PQueue<T>&);
  ~PQueue ();

  void create ();
  void push (_value_type);
  _value_type top ();
  void pop ();
  bool empty();
  void printpq();

  PQueue<T>& operator=(const PQueue<T>& q);

  template <class K>
  friend ostream& operator<<(ostream &os, const PQueue<K>& q);

private:
  int MAXLENGTH;
  _value_type *heap;
  int last;

  void fixUp ();
  void fixDown (int, int);
};


template < class T >
PQueue < T >::PQueue ():MAXLENGTH (100) {
  heap = new _value_type[MAXLENGTH];
  create ();
}

template < class T >
PQueue < T >::PQueue (int maxN): MAXLENGTH (maxN) {
  heap = new _value_type[MAXLENGTH];
  create ();
}

template < class T >
PQueue < T >::PQueue (PQueue<T>& pq){

  MAXLENGTH=pq.MAXLENGTH;
  heap=new _value_type[MAXLENGTH];
  last=pq.last;

  for(int i=0; i<last; i++){
    heap[i]=pq.heap[i];
  }

}

template < class T >
PQueue < T >::~PQueue () {
  delete[]heap;
}

template < class T >
void PQueue < T >::create () {
  last = 0;
}

template < class T >
void PQueue < T >::push (_value_type e) {
  if(last < MAXLENGTH){
    heap[++last - 1] = e;
    fixUp ();
  }
}

template < class T > typename
PQueue < T >::_value_type PQueue < T >::top () {
  if(last != 0){
    return (heap[0]);
  }else throw "the queue is empty perdindirindina";
}

template < class T >
void PQueue < T >::pop () {

  if(last != 0){
    heap[0] = heap[last - 1];
    last--;
    fixDown (1,last);
  }
}

/* Per ripristinare i vincoli dello heap quando la priorità di un nodo è      *
 * cresciuta, ci spostiamo nello heap verso l'alto, scambiando, se necessario,*
 * il nodo in posizione k con il suo nodo padre (in posizione k/2),           *
 * continuando fintanto che heap[k]<heap[k/2] oppure fino a quando            *
 * raggiungiamo la cima dello heap.                                           */

template < class T > void PQueue < T >::fixUp () {
  int k = last;

  while (k > 1 && heap[k - 1] < heap[k / 2 - 1]) {   //heap[k - 1] is the last leaf  //heap[(k/2)-1] is the father
      _value_type tmp;
      tmp = heap[k - 1];
      heap[k - 1] = heap[k / 2 - 1];
      heap[k / 2 - 1] = tmp;
      k = k / 2;
    }

}

/* Per ripristinare i vincoli dello heap quando la priorità di un nodo si è   *
 * ridotta, ci spostiamo nello heap verso il basso, scambiando, se necessario,*
 * il nodo in posizione k con il minore dei suoi nodi figli e arrestandoci    *
 * quando il nodo al posto k non è più grande di almeno uno dei suoi figli    *
 * oppure quando raggiungiamo il fondo dello heap. Si noti che se N è pari e  *
 * k è N/2, allora il nodo in posizione k ha un solo figlio: questo caso      *
 * particolare deve essere trattato in modo appropriato.                      */

template < class T > void PQueue < T >::fixDown (int k, int N) {

  bool swap = 1;

  while (k <= N / 2 && swap) {
      int j = 2 * k;
      _value_type tmp;
      if (j < N && heap[j - 1] > heap[j])
				j++;
      if (swap = (heap[j - 1] < heap[k - 1])) {
				tmp = heap[k - 1];
				heap[k - 1] = heap[j - 1];
				heap[j - 1] = tmp;
				k = j;
			}
  }
}

template < class T >
bool PQueue<T>::empty(){
  return last==0;
}

template < class T > void PQueue < T >::printpq(){

  cout<<"|";
  for(int i=0; i<last; i++){
    cout<<heap[i]<<"|";
  }
  cout<<endl;
}

template < class T >
PQueue<T>& PQueue < T >::operator=(const PQueue<T>& q){

  if(this==&q){
    return *this;
  }
  if(MAXLENGTH!=q.MAXLENGTH){
    delete[]heap;
    MAXLENGTH=q.MAXLENGTH;
    heap=new _value_type[MAXLENGTH];
  }
  last=q.last;

  for(int i=0; i<last; i++){
    heap[i]=q.heap[i];
  }

  return *this;

}

template <class K>
ostream& operator<<(ostream& os, const PQueue<K>& q){

  os<<"|";
  for(int i=0; i<q.last; i++){
    os<<q.heap[i]<<"|";
  }
  os<<endl;

  return os;

}

#endif /* _PRIORITYQUEUE_H_ */
