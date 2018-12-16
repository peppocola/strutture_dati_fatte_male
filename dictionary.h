
/* A dictionary is a collection of pairs of the form (k,v), where k is a key and v is the value
 * associated with the key k (equivalently, v is the value whose key is k).
 */

/* The pair */

#ifndef _DICTIONARY_H
#define _DICTIONARY_H

template<class K, class E>
struct mypair {
  // data member
  K first; //key
  E second; //value

  // methods
  mypair(){}
  mypair(mypair<K,E>& the_pair){
    first = the_pair.first;
    second = the_pair.second;
  }
};


template <class K, class E>
class dictionary
{

public:
  virtual ~dictionary() {}

  virtual void create() = 0;
      // create an empty dictionary
  virtual bool empty() const = 0;
      // return true iff the dictionary is empty
  virtual int size() const = 0;
      // return the number of pairs in the dictionary
  virtual mypair< K, E>* find(const K& k) const = 0;
      // return the pair with key k
  virtual void insert( mypair< K, E>& p) = 0;
      // insert the pair p into the dictionary
  virtual void erase(const K& k) = 0;
      // delete the pair with key k
  virtual void modify(const K& k, const E& e) = 0;
      // modify the value of the pair with key k to e
};

#endif
