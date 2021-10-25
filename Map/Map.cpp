#include "Map.hpp"

template<typename H,typename V>
Entry<H,V>::Entry(H h1, V v1): h(h1), v(v1){}

template<typename H,typename V>
Entry<H,V>::Entry(const Entry& e): h(e.h), v(e.v){}

template<typename H,typename V>
Entry<H,V>::~Entry(){}

template<typename H,typename V>
bool Entry<H,V>::operator<(const Entry<H,V>& e){
    return h<e.h;
}

template<typename H,typename V>
bool Entry<H,V>::operator<=(const Entry<H,V>& e){
    return h<=e.h;
}

template<typename H,typename V>
bool Entry<H,V>::operator==(const Entry<H,V>& e){
    return h==e.h;
}

template<typename H,typename V>
bool Entry<H,V>::operator!=(const Entry<H,V>& e){
    return h!=e.h;
}

template<typename H,typename V>
bool Entry<H,V>::operator>=(const Entry<H,V>& e){
    return h>=e.h;
}

template<typename H,typename V>
bool Entry<H,V>::operator>(const Entry<H,V>& e){
    return h>e.h;
}


template<typename K,typename H,typename V>
Map<K,H,V>::Map(function<H(K)> h): hashing_func(h){
    t = new Tree<Entry<H,V>, 4>();
}

template<typename K,typename H,typename V>
Map<K,H,V>::~Map(){
    delete t;
}

template<typename K,typename H,typename V>
pair<Entry<H,V>*,bool> Map<K,H,V>::getOrCreate(K key, V value){
    Entry<H,V> temp(hashing_func(key),value);
    pair<Node<Entry<H,V>, 4>*, ll> res = t->find(temp);
    if(res.first)
        return make_pair(data(res.first,res.second),false);
    t->insert(temp);
    res = t->find(temp);
    return make_pair(data(res.first,res.second),true);
}
