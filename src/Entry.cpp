#include <Entry.hpp>
using namespace std;
typedef long long ll;

Entry::Entry(H h1, V v1) : h(h1), v(v1) {}

Entry::Entry(const Entry &e) : h(e.h), v(e.v) {}

Entry::~Entry() {}

bool Entry::operator<(const Entry &e)
{
    return h < e.h;
}

bool Entry::operator<=(const Entry &e)
{
    return h <= e.h;
}

bool Entry::operator==(const Entry &e)
{
    return h == e.h;
}

bool Entry::operator!=(const Entry &e)
{
    return h != e.h;
}

bool Entry::operator>=(const Entry &e)
{
    return h >= e.h;
}

bool Entry::operator>(const Entry &e)
{
    return h > e.h;
}
