#ifndef _BINTREE_H_
#define _BINTREE_H_
#include <iostream>
#include <queue>

using namespace std;

template <class T, class N>
class bintree {
  static const int NIL = -1;

  public:
    // tipi
    typedef T value_type;
    typedef N Nodo;

    // operatori
    virtual void create() = 0;
    virtual bool empty() const =  0;

    virtual Nodo root() const = 0;
    virtual Nodo parent(Nodo) const =  0;
    virtual Nodo sx(Nodo) const = 0;
    virtual Nodo dx(Nodo) const = 0;
    virtual bool sx_empty(Nodo) const = 0;
    virtual bool dx_empty(Nodo) const = 0;

    //virtual void costr(bintree<T,N>);
    virtual void erase(Nodo) = 0;

    virtual T read(Nodo) const = 0;
    virtual void write(Nodo , value_type ) = 0;

    virtual void ins_root(value_type) = 0;
    virtual void ins_sx(Nodo, value_type) = 0;
    virtual void ins_dx(Nodo, value_type) = 0;

    virtual void previsit(Nodo);
    virtual void invisita(Nodo);
    virtual void postvisit(Nodo);
    virtual void BFS(Nodo);
    virtual int depth(Nodo);
    virtual int width(Nodo);

    int kSubtree(const Nodo, const int)const;
    int sumSubtree(const Nodo)const;
    int maxSumSubtree(const Nodo n)const;

    template<class G, class S>
    friend ostream& operator<<(ostream& out, const bintree<G, S>& t);


private:
    virtual int _width(Nodo, int);
    virtual int _depth(Nodo, int);
    virtual void printSubTree(ostream&, const Nodo) const;
    virtual void print(ostream&) const;


  };

template <class T, class N>
void bintree<T,N>::print(ostream& os)const{
	if (!empty())
		printSubTree(os, root());
	else
		os << "[]" << endl;
	os << endl;
}

template <class T, class N>
void bintree<T,N>::printSubTree(ostream& os, const Nodo n) const{
  if (sx_empty(n) && dx_empty(n)){
    os << "[" << read(n) << "]";
    return;
  }
  os << "[" << read(n) << ",";
	if (!sx_empty(n))
		printSubTree(os, sx(n));
	else os << "[sxNIL]";
	os << ",";
	if (!dx_empty(n))
		printSubTree(os, dx(n));
	else os << "[dxNIL]";
	os << "]";
}

template<class G, class S>
ostream& operator<<(ostream& out, const bintree<G, S>& t) {
    t.print(out);
    return out;
}

template<class T, class N>
void bintree<T,N>::previsit(Nodo n){
  //esamina nodo
  if(!sx_empty(n)) previsit(sx(n));
  if(!dx_empty(n)) previsit(dx(n));
}

template<class T, class N>
void bintree<T,N>::invisita(Nodo n){
  if(!sx_empty(n)) invisita(sx(n));
  //esamina nodo
  if(!dx_empty(n)) invisita(dx(n));
}

template<class T, class N>
void bintree<T,N>::postvisit(Nodo n){
  if(!sx_empty(n)) postvisit(sx(n));
  if(!dx_empty(n)) postvisit(dx(n));
  //esamina nodo
}

template<class T, class N>
void bintree<T,N>::BFS(Nodo n){
  queue<Nodo> q;
  q.push(n);
  while (!q.empty()){
    //esamina q.front
    if(!sx_empty(q.front())) q.push(sx(q.front()));
    if(!dx_empty(q.front())) q.push(dx(q.front()));
    q.pop();
  }
}

template<class T, class N>
int bintree<T,N>::depth(Nodo n){
  return _depth(n, 0);

}

template<class T, class N>
int bintree<T,N>::_depth(Nodo n, int i){

  int dp=i;

  if (!sx_empty(n)){
    int tmp=_depth(sx(n),dp);
    if (tmp>dp){
      dp=tmp;
    }
  }

  if (!dx_empty(n)){
    int tmp=_depth(dx(n),dp);
    if (tmp>dp){
      dp=tmp;
    }
  }

  return dp+1;
}

template<class T, class N>
int bintree<T,N>::width(Nodo n){
  if(!empty()){
    return _width(n, 0);
  }
  return 0;
}

template<class T, class N>
int bintree<T,N>::_width(Nodo n, int w){

  queue<Nodo>q;
  q.push(n);

  while (!q.empty()){
    int i=q.size();

    if (i>w){
      w=i;
    }

    int j=0;
    while(j<i){
      Nodo front=q.front();
      if (!sx_empty(front)) q.push(sx(front));
      if (!dx_empty(front)) q.push(dx(front));
      q.pop();
      j++;
    }
  }
  return w;
}

//dato un albero binario di n nodi contare i sottoalberi che hanno somma dei nodi pari ad un intero k
template<class T, class N>
int bintree<T,N>::kSubtree(const Nodo n, const int k)const{

  int result=0;
  queue<Nodo> q;
  q.push(n);
  while (!q.empty()){
    Nodo front=q.front();
    if (sumSubtree(front)==k) result++;
    if(!sx_empty(front)) q.push(sx(front));
    if(!dx_empty(front)) q.push(dx(front));
    q.pop();
  }
  return result;
}

template<class T, class N>
int bintree<T,N>::sumSubtree(const Nodo n)const{

  int result=read(n);
  if(!sx_empty(n)){
    result+=sumSubtree(sx(n));
  }
  if(!dx_empty(n)){
    result+=sumSubtree(dx(n));
  }

  return result;
}

template<class T, class N>
int bintree<T,N>::maxSumSubtree(const Nodo n)const{

  int result=sumSubtree(n);
  queue<Nodo> q;

  if(!sx_empty(n)) q.push(sx(n));
  if(!dx_empty(n)) q.push(dx(n));

  while (!q.empty()){
    Nodo front=q.front();
    int tmp=sumSubtree(front);
    if (tmp>result) result=tmp;
    if(!sx_empty(front)) q.push(sx(front));
    if(!dx_empty(front)) q.push(dx(front));
    q.pop();
  }
  return result;
}

#endif /* _BINTREE_H_ */
