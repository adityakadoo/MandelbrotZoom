#ifndef __MANDELBROT_MAP__
#define __MANDELBROT_MAP__
#include <iostream>
#include <Entry.hpp>
#include <Tree.hpp>
typedef int K;

class Map{
private:
    Tree *t;
    std::function<H(K)> hashing_func;
public:
    /* Constructors and Destructors */
    // Default Constructor
    Map(std::function<H(K)>);
    // Default Destructor
    ~Map();

    /* Map operations */
    // If new key then inserts in the map
    // else return the entry for an old key
    std::pair<Entry*,bool> getOrCreate(K,V);

    // Pretty printer
    friend std::ostream& operator<<(std::ostream &cout, Map &m){
        cout<<*(m.t);
        return cout;
    }
};

#endif