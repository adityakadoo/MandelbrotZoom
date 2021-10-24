#ifndef __MANDELBROT_MAP__
#define __MANDELBROT_MAP__
#include <bits/stdc++.h>
using namespace std;

#define MAX_ENTRIES 2'00'000

// A class to denote an entry of the map
template<typename K, typename V>
class Entry{
public:
    K key; // Key
    V value; // Value
};

template<typename K,typename V>
class Map
{
private:
    Entry<K,V>* entries;
    long long size;
    function<V(K)> hashing_func;
public:
    /* Constructors and Destructors */
    // Default Constructor
    Map(function<V(K)>);
    // Default Destructor
    ~Map();

    /* Map operations */
    // Inserts new key in the map
    bool create(K);
    // Searches for given key in the map
    Entry<K,V>* get(K&);
    // Searches for the given key in the map
    // If not found then creates a new one
    Entry<K,V>* getOrCreate(K&);
};

#endif