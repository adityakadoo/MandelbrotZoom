#include <Map.hpp>
using namespace std;
typedef long long ll;

Map::Map(function<H(K)> h): hashing_func(h){
    t = new Tree();
}

Map::~Map(){
    delete t;
}

pair<Entry*,bool> Map::getOrCreate(K key, V value){
    Entry temp(hashing_func(key),value);
    pair<Node*, ll> res = t->find(temp);
    if(res.first)
        return make_pair(data(res.first,res.second),false);
    t->insert(temp);
    res = t->find(temp);
    return make_pair(data(res.first,res.second),true);
}
