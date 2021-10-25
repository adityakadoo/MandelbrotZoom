#ifndef __MANDELBROT_MAP__
#define __MANDELBROT_MAP__
#include <bits/stdc++.h>
#include "../Tree/Tree.hpp"
#include "../Tree/Tree.cpp"
using namespace std;

// A class to denote an entry of the map
template<typename H, typename V>
class Entry{
public:
    H h; // Hashed key
    V v; // Value

    /* Constructors and Destructors */
    // Constructor with given hash and value
    Entry(H,V);
    // Copy Constructor
    Entry(const Entry<H,V>&);
    // Default destructor
    ~Entry();

    /* Comparison operators */
    bool operator<(const Entry<H,V>&);
    bool operator<=(const Entry<H,V>&);
    bool operator==(const Entry<H,V>&);
    bool operator!=(const Entry<H,V>&);
    bool operator>=(const Entry<H,V>&);
    bool operator>(const Entry<H,V>&);

    // Pretty printer
    friend ostream& operator<<(std::ostream &cout, Entry<H,V> &e){
        cout<<"{ "<<e.h<<" : "<<e.v<<" }";
        return cout;
    }
};

#define hash(e) e->h
#define value(e) e->v

template<typename K,typename H,typename V>
class Map{
private:
    Tree<Entry<H,V>,4> *t;
    function<H(K)> hashing_func;
public:
    /* Constructors and Destructors */
    // Default Constructor
    Map(function<H(K)>);
    // Default Destructor
    ~Map();

    /* Map operations */
    // If new key then inserts in the map
    // else return the entry for an old key
    pair<Entry<H,V>*,bool> getOrCreate(K,V);

    // Pretty printer
    friend ostream& operator<<(std::ostream &cout, Map<K,H,V> &m){
        cout<<*(m.t);
        return cout;
    }
};

#endif