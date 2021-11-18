#ifndef __ENTRY__
#define __ENTRY__
#include <Complex.hpp>

#define FACTOR 2
#define level(h) ceil(log2(h + 1) / 2) - 1

// A class to denote an entry of the map
class Entry
{
public:
    long long h;   // Hashed key
    long double v; // Value

    /* Constructors and Destructors */
    // Constructor with given hash and value
    Entry(long long, long double);
    // Copy Constructor
    Entry(const Entry &);
    // Default destructor
    ~Entry();

    /* Comparison operators */
    bool operator<(const Entry &);
    bool operator<=(const Entry &);
    bool operator==(const Entry &);
    bool operator!=(const Entry &);
    bool operator>=(const Entry &);
    bool operator>(const Entry &);

    // Pretty printer
    friend std::ostream &operator<<(std::ostream &cout, Entry &e)
    {
        cout << "{ " << e.h << " : " << e.v << " }";
        return cout;
    }
};

// #define hashed(e) e->h
// #define value(e) e->v

#endif