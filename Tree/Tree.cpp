// #include <bits/stdc++.h>
// using namespace std;
#include "Tree.hpp"

template<typename T>
Node<T>::Node(){
    children = new Node<T>*[b];
}

template<typename T>
Node<T>::Node(T d): data(d){
    children = new Node<T>*[b];
}

template<typename T>
Node<T>::~Node(){
    delete[] children;
}

#define parent(n) n->parents.front()
#define left(n) n->children.front()
#define right(n) n->children.back()
#define data(n) n->data
enum traversal_type {PRE, POST, IN, EULER};

template<typename T>
class BST
{
private:
    Node<T>* root;
public:
    BST(): root(NULL){}
    bool insert(T elem,bool copies=false){
        Node<T>* p = NULL;
        Node<T>* r = root;
        while(r){
            p = r;
            if(elem>data(r))
                r = right(r);
            else if(elem<data(r) || copies)
                r = left(r);
            else
                return false;
        }
        r = new Node<T>(elem);
        parent(r) = p;
        left(r) = NULL;
        right(r) = NULL;
        if(!p)
            root = r;
        else if(elem>data(p))
            right(p) = r;
        else if(elem<data(p) || copies)
            left(p) = r;
        return true;
    }
    Node<T>* find(T elem){
        Node<T>* r = root;
        while (r && data(r)!=elem){
            if(elem>data(r))
                r = right(r);
            else if(elem<data(r))
                r = left(r);
        }
        return r;
    }
    Node<T>* min(){
        Node<T>* r = root;
        while (left(r)){
            r = left(r);
        }
        return r;
    }
    Node<T>* max(){
        Node<T>* r = root;
        while (right(r)){
            r = right(r);
        }
        return r;
    }
    Node<T>* succ(Node<T> *r){
        Node<T>* p = parent(r);
        if(right(r)){
            r = right(r);
            while(left(r))
                r = left(r);
            return r;
        }
        if(p && data(r)>data(p))
            return NULL;
        return p;
    }
    Node<T>* pred(Node<T> *r){
        Node<T>* p = parent(r);
        if(left(r)){
            r = left(r);
            while(right(r))
                r = right(r);
            return r;
        }
        if(p && data(r)<=data(p))
            return NULL;
        return p;
    }
    bool remove(T elem){
        Node<T>* r = find(elem);
        if(r){
            if(!parent(r) && !left(r) && !right(r))
                root = NULL;
            else if(!parent(r) && !left(r) && right(r)){
                parent(right(r)) = NULL;
                root = right(r);
            }
            else if(!parent(r) && left(r) && !right(r)){
                parent(left(r)) = NULL;
                root = left(r);
            }
            else if(!parent(r) && left(r) && right(r)){
                parent(right(r)) = left(r);
                parent(left(r)) = NULL;
                right(left(r)) = right(r);
            }
            else if(left(parent(r))==r && !left(r) && !right(r))
                left(parent(r)) = NULL;
            else if(left(parent(r))==r && !left(r) && right(r)){
                left(parent(r)) = right(r);
                parent(right(r)) = parent(r);
            }
            else if(left(parent(r))==r && left(r) && !right(r)){
                left(parent(r)) = left(r);
                parent(left(r)) = parent(r);
            }
            else if(right(parent(r))==r && !left(r) && !right(r))
                right(parent(r)) = NULL;
            else if(right(parent(r))==r && !left(r) && right(r)){
                right(parent(r)) = right(r);
                parent(right(r)) = parent(r);
            }
            else if(right(parent(r))==r && left(r) && !right(r)){
                right(parent(r)) = left(r);
                parent(left(r)) = parent(r);
            }
            else{
                Node<T>* p = pred(r);
                T temp = data(p);
                remove(temp);
                data(r) = temp;
                return true;
            }
            delete r;
            return true;
        }
        return false;
    }
    void traverse(traversal_type tt,function<void(Node<T>*)> f,Node<T>* r=NULL){
        if(!r)
            r = root;
        if(!left(r) && !right(r)){
            f(r);
            return;
        }
        if(tt==PRE || tt==EULER)
            f(r);
        if(left(r))
            traverse(tt,f,left(r));
        if(tt==IN || tt==EULER)
            f(r);
        if(right(r))
            traverse(tt,f,right(r));
        if(tt==POST || tt==EULER)
            f(r);
    }
    friend ostream& operator<<(std::ostream &cout, BST<T> &t) {
        if(!t.root){
            cout<<"<Empty BST>\n";
            return cout;
        }
        stack<pair<Node<T>*,string>> s;
        pair<Node<T>*,string> r = make_pair(t.root,"");
        while(true){
            while(r.first){
                s.push(r);
                if(!parent(r.first))
                    r = make_pair(left(r.first),r.second);
                else if(left(parent(r.first))==r.first)
                    r = make_pair(left(r.first),r.second+"   ");
                else if(right(parent(r.first))==r.first)
                    r = make_pair(left(r.first),r.second+"│  ");
            }
            if(s.empty())
                break;
            r = s.top();
            if(!parent(r.first))
                cout<<r.second<<data(r.first)<<"\n";
            else if(parent(r.first) && left(parent(r.first))==r.first)
                cout<<r.second<<"┌──"<<data(r.first)<<"\n";
            else if(parent(r.first) && right(parent(r.first))==r.first)
                cout<<r.second<<"└──"<<data(r.first)<<"\n";
            s.pop();
            if(!parent(r.first))
                r = make_pair(right(r.first),r.second);
            else if(right(parent(r.first))==r.first)
                r = make_pair(right(r.first),r.second+"   ");
            else if(left(parent(r.first))==r.first)
                r = make_pair(right(r.first),r.second+"│  ");
        }
        return cout;
    }
    ~BST(){
        while(root)
            remove(data(min()));
    }
};