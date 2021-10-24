#include "Map.hpp"

template<typename K,typename V>
Map<K,V>::Map(function<V(K)> h): hashing_func(h){
    entries = new Entry<K,V>[MAX_ENTRIES];
}

template<typename K,typename V>
Map<K,V>::~Map(){
    delete[] entries;
}

template<typename K,typename V>
bool Map<K,V>::create(K& key){
    if(size==MAX_ENTRIES)
        return false;
    entries[size] = new Entry<K,V>;
    entries[size].key = key;
    entries[size].value = hashing_func(key);
    size++;
    return true;
}

template<typename K,typename V>
Entry<K,V>* Map<K,V>::get(K& key){
    // Simple Linear Search
    for(long long i=0;i<size;i++){
        if(entries[i].key==key)
            return entries[i];
    }
    return NULL;
}

template<typename K,typename V>
Entry<K,V>* Map<K,V>::getOrCreate(K& key){
    Entry<K,V>* res = get(key);
    if(res)
        return res;
    if(size==MAX_ENTRIES)
        return NULL;
    entries[size] = new Entry<K,V>;
    entries[size].key = key;
    entries[size].value = hashing_func(key);
    size++;
    return entries[size-1];
}