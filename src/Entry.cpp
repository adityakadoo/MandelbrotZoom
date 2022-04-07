#include <Entry.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;

Entry::Entry(ll h1, ld v1) : h(h1), v(v1) {}

Entry::Entry(const Entry &e) : h(e.h), v(e.v) {}

Entry::~Entry() {}

bool Entry::operator<(const Entry &e)
{
    ll a=h,b=e.h;
    while(a>0 || b>0){
        if(a%(FACTOR*FACTOR)>b%(FACTOR*FACTOR)){
            return false;
        }
        else if(a%(FACTOR*FACTOR)>b%(FACTOR*FACTOR)){
            return true;
        }
        a /= FACTOR*FACTOR;
        b /= FACTOR*FACTOR;
    }
    return false;
}

bool Entry::operator<=(const Entry &e)
{
    ll a=h,b=e.h;
    while(a>0 || b>0){
        if(a%(FACTOR*FACTOR)>b%(FACTOR*FACTOR)){
            return false;
        }
        else if(a%(FACTOR*FACTOR)>b%(FACTOR*FACTOR)){
            return true;
        }
        a /= FACTOR*FACTOR;
        b /= FACTOR*FACTOR;
    }
    return true;
}

bool Entry::operator==(const Entry &e)
{
    ll a=h,b=e.h;
    while(a>0 || b>0){
        if(a%(FACTOR*FACTOR)!=b%(FACTOR*FACTOR)){
            return false;
        }
        a /= FACTOR*FACTOR;
        b /= FACTOR*FACTOR;
    }
    return true;
}

bool Entry::operator!=(const Entry &e)
{
    ll a=h,b=e.h;
    while(a>0 || b>0){
        if(a%(FACTOR*FACTOR)!=b%(FACTOR*FACTOR)){
            return true;
        }
        a /= FACTOR*FACTOR;
        b /= FACTOR*FACTOR;
    }
    return false;
}

bool Entry::operator>=(const Entry &e)
{
    ll a=h,b=e.h;
    while(a>0 || b>0){
        if(a%(FACTOR*FACTOR)>b%(FACTOR*FACTOR)){
            return true;
        }
        else if(a%(FACTOR*FACTOR)>b%(FACTOR*FACTOR)){
            return false;
        }
        a /= FACTOR*FACTOR;
        b /= FACTOR*FACTOR;
    }
    return true;
}

bool Entry::operator>(const Entry &e)
{
    ll a=h,b=e.h;
    while(a>0 || b>0){
        if(a%(FACTOR*FACTOR)>b%(FACTOR*FACTOR)){
            return true;
        }
        else if(a%(FACTOR*FACTOR)>b%(FACTOR*FACTOR)){
            return false;
        }
        a /= FACTOR*FACTOR;
        b /= FACTOR*FACTOR;
    }
    return false;
}
