#ifndef __ENTRY__
#define __ENTRY__
#include <Complex.hpp>
typedef long long H;
typedef long long V;

// A class to denote an entry of the map
class Entry{
public:
    H h; // Hashed key
    V v; // Value

    /* Constructors and Destructors */
    // Constructor with given hash and value
    Entry(H,V);
    // Copy Constructor
    Entry(const Entry&);
    // Default destructor
    ~Entry();

    /* Comparison operators */
    bool operator<(const Entry&);
    bool operator<=(const Entry&);
    bool operator==(const Entry&);
    bool operator!=(const Entry&);
    bool operator>=(const Entry&);
    bool operator>(const Entry&);

    // Pretty printer
    friend std::ostream& operator<<(std::ostream &cout, Entry &e){
        cout<<"{ "<<e.h<<" : "<<e.v<<" }";
        return cout;
    }
};

#define hash(e) e->h
#define value(e) e->v

#endif