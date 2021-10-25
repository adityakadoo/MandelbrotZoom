#include "Tree.hpp"

template<typename T, int b>
Node<T,b>::Node(Node<T,b>* p,ll loc){
    parent = make_pair(p,loc);
    children = new Node<T,b>*[b];
    for(ll i=0;i<b;i++){
        children[i] = NULL;
    }
    data = new T*[b-1];
    for(ll i=0;i<b-1;i++){
        data[i] = NULL;
    }
    size=0;
}

template<typename T, int b>
Node<T,b>::~Node(){
    for(int i=0;i<b;i++)
        if(children[i])
            delete children[i];
    delete[] children;
    for(int i=0;i<b-1;i++)
        if(data[i])
            delete data[i];
    delete[] data;
}


template<typename T, int b>
Tree<T,b>::Tree(): root(NULL){}

template<typename T, int b>
ll Tree<T, b>::binarySearch(T** arr,ll len, T elem){
    ll l = 0, r = len-1, res = -1, mid;
    while(l<=r){
        mid = l+(r-l)/2;
        if(*arr[mid]<=elem){
            res = mid;
            l = mid+1;
        }
        else{
            r = mid-1;
        }
    }
    return res;
}

template<typename T, int b>
bool Tree<T,b>::insert(const T &elem){
    Node<T,b>* p = NULL;
    Node<T,b>* r = root;
    ll i = -2;
    while(r){
        p = r;
        i = binarySearch(&data(r,0),size(r),elem);
        if(i==size(r)-1 && size(r)+1<b){
            data(r,size(r)) = new T(elem);
            size(r)++;
            return true;
        }
        else if(i==-1)
            r = child(r,0);
        else if(*data(r,i) == elem)
            return false;
        else
            r = child(r,i+1);
    }
    r = new Node<T,b>(p,i+1);
    data(r,0) = new T(elem);
    size(r)++;
    if(!p)
        root = r;
    else
        child(p,i+1) = r;
    return true;
}

template<typename T, int b>
pair<Node<T,b>*,ll> Tree<T,b>::find(T elem){
    Node<T,b>* r = root;
    ll i;
    while(r){
        i = binarySearch(&data(r,0),size(r),elem);
        if(i==-1)
            r = child(r,0);
        else if(*data(r,i) == elem)
            return make_pair(r,i);
        else
            r = child(r,i+1);
    }
    return make_pair((Node<T,b>*)NULL,-1);
}

template<typename T, int b>
pair<Node<T,b>*,ll> Tree<T,b>::min(){
    if(!root)
        return make_pair((Node<T,b>*)NULL,-1);
    Node<T,b>* r = root;
    while(child(r,0))
        r = child(r,0);
    return make_pair(r,0);
}

template<typename T, int b>
pair<Node<T,b>*,ll> Tree<T,b>::max(){
    if(!root)
        return make_pair((Node<T,b>*)NULL,-1);
    Node<T,b>* r = root;
    while(child(r,size(r)))
        r = child(r,size(r));
    return make_pair(r,size(r)-1);
}

template<typename T, int b>
pair<Node<T,b>*,ll> Tree<T,b>::succ(Node<T,b>* r,ll i){
    if(!child(r,i+1) && i+1<size(r))
        return make_pair(r,i+1);
    else if(!child(r,i+1)){
        pair<Node<T,b>*,ll> p = parent(r);
        while(p.first && p.second>=size(p.first))
            p = parent(p.first);
        if(p.first)
            return make_pair(p.first,p.second);
        else
            return make_pair((Node<T,b>*)NULL,-1);
    }
    while(child(r,i+1)){
        r = child(r,i+1);
        i = -1;
    }
    return make_pair(r,i+1);
}

template<typename T, int b>
pair<Node<T,b>*,ll> Tree<T,b>::pred(Node<T,b>* r,ll i){
    if(!child(r,i) && i!=0)
        return make_pair(r,i-1);
    else if(!child(r,i)){
        pair<Node<T,b>*,ll> p = parent(r);
        while(p.first && p.second<=0)
            p = parent(p.first);
        if(p.first)
            return make_pair(p.first,size(p.first)-1);
        else
            return make_pair((Node<T,b>*)NULL,-1);
    }
    while(child(r,i)){
        ll temp = i;
        i = size(child(r,i));
        r = child(r,temp);
    }
    return make_pair(r,i-1);
}

// template<typename T, int b>
// bool Tree<T,b>::remove(T elem){
//         Node<T,b>* r = find(elem);
//     if(r){
//             if(!parent(r) && !left(r) && !right(r))
//             root = NULL;
//         else if(!parent(r) && !left(r) && right(r)){
//                 parent(right(r)) = NULL;
//             root = right(r);
//         }
//         else if(!parent(r) && left(r) && !right(r)){
//                 parent(left(r)) = NULL;
//             root = left(r);
//         }
//         else if(!parent(r) && left(r) && right(r)){
//                 parent(right(r)) = left(r);
//             parent(left(r)) = NULL;
//             right(left(r)) = right(r);
//         }
//         else if(left(parent(r))==r && !left(r) && !right(r))
//             left(parent(r)) = NULL;
//         else if(left(parent(r))==r && !left(r) && right(r)){
//                 left(parent(r)) = right(r);
//             parent(right(r)) = parent(r);
//         }
//         else if(left(parent(r))==r && left(r) && !right(r)){
//                 left(parent(r)) = left(r);
//             parent(left(r)) = parent(r);
//         }
//         else if(right(parent(r))==r && !left(r) && !right(r))
//             right(parent(r)) = NULL;
//         else if(right(parent(r))==r && !left(r) && right(r)){
//                 right(parent(r)) = right(r);
//             parent(right(r)) = parent(r);
//         }
//         else if(right(parent(r))==r && left(r) && !right(r)){
//                 right(parent(r)) = left(r);
//             parent(left(r)) = parent(r);
//         }
//         else{
//                 Node<T,b>* p = pred(r);
//             T temp = *data(p);
//             remove(temp);
//             *data(r) = temp;
//             return true;
//         }
//         delete r;
//         return true;
//     }
//     return false;
// }

template<typename T, int b>
void Tree<T,b>::traverse(function<void(T*)> f,Node<T,b>* r){
    if(!r){
        r = root;
    }
    for(ll i=0;i<size(r);i++){
        if(child(r,i))
            traverse(f,child(r,i));
        f(&(*data(r,i)));
    }
    if(child(r,size(r)))
        traverse(f,child(r,size(r)));
    return;
}

template<typename T, int b>
Tree<T,b>::~Tree(){
    if(root)
        delete root;
}

template<typename T, int b>
void Tree<T,b>::printNode(Node<T,b>* r, string s){
    for(ll i=0;i<size(r);i++){
        if(child(r,i)){
            cout<<s<<"├──┐\n";
            printNode(child(r,i),s+"│  ");
        }
        if(i!=size(r)-1)
            cout<<s<<"├──"<<*data(r,i)<<"\n";
    }
    cout<<s<<"└──"<<*data(r,size(r)-1)<<"\n";
    if(child(r,size(r)))
        printNode(child(r,size(r)),s+"   ");
    return;
}