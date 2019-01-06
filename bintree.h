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

    virtual void print() const;

private:
    virtual int _width(Nodo, int);
    virtual int _depth(Nodo, int);
    virtual void printSubTree(const Nodo) const;


  };

template <class T, class N>
void bintree<T,N>::print() const{
	if (!empty())
		printSubTree(root());
	else
		cout << "[]" << endl;
	cout << endl;
}

template <class T, class N>
void bintree<T,N>::printSubTree(const Nodo n) const{
  if (sx_empty(n) && dx_empty(n)){
    cout << "[" << read(n) << "]";
    return;
  }
  cout << "[" << read(n) << ",";
	if (!sx_empty(n))
		printSubTree(sx(n));
	else cout << "[sxNIL]";
	cout << ",";
	if (!dx_empty(n))
		printSubTree(dx(n));
	else cout << "[dxNIL]";
	cout << "]";
}

template<class T, class N>
ostream& operator<<(ostream& out, const bintree<T, N>& t) {
    t.print();
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

#endif /* _BINTREE_H_ */
