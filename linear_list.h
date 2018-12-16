#ifndef _LINEAR_LIST_H
#define _LINEAR_LIST_H

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

template <class T, class P>
class Linear_list{
  public:
    typedef T value_type;
    typedef P position;

    virtual void create()=0; //crealista;
    virtual void clear()=0;  //cancellalista;
    virtual int size() const =0; //lunghezzalista;
    virtual bool empty() const =0; //listavuota;
    virtual bool end(position p) const =0; //finelista;
    virtual position begin() const =0; //primaposizione;
    virtual position last() const =0; //ultimaposizione;
    virtual value_type read(position) const = 0; //leggilista;
    virtual position next(position) const =0; //posizionesuccessiva;
    virtual position previous(position) const =0; //posizioneprecedente;
    virtual void erase(position) const=0; //canellaelemlista;

};

template< class T, class P >
ostream& operator<< (ostream& os, const Linear_list<T,P> &l){
	typename Linear_list<T,P>::position p;
	p = l.begin();
	os << "[";
	while (!l.end(p)){
		if (p != l.begin())
			os << ", " << l.read(p);
		else
			os << l.read(p);
		p = l.next(p);
	}
	os << "]" << endl;
	return os;
}

#endif //_LINLIST_H
