#ifndef __TREE__
#define __TREE__
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
typedef long long ll;

template <typename T, int b>
class Node{
public:
    /* Public data and connected nodes */
    pair<Node<T, b>*,ll> parent;
    Node<T, b> **children;
    T **data;
    ll size;
    /* Constructors and Destructors */
    // Constructor with parent pointer
    Node(Node<T, b> *,ll);
    // Default Destructor
    ~Node();
};

#define parent(n) n->parent
#define child(n, i) n->children[i]
#define data(n,i) n->data[i]
#define size(n) n->size

template <typename T, int b>
class Tree{
private:
    Node<T, b> *root;

    // Binary Search for internal use
    static ll binarySearch(T **, ll, T);
    // Recursive Printer for internal use
    static void printNode(Node<T, b>*, string s); 

public:
    // Default Constructor
    Tree();
    // Default Destructor
    ~Tree();

    /* Tree Operations */
    // Inserts the given element
    bool insert(const T&);
    // Find the given element
    pair<Node<T,b>*,ll> find(T);
    // Find min element in the tree
    pair<Node<T,b>*,ll> min();
    // Find max element in the tree
    pair<Node<T,b>*,ll> max();
    // Find successor of the given node
    pair<Node<T,b>*,ll> succ(Node<T,b>*,ll);
    // Find predecessor of the given node
    pair<Node<T,b>*,ll> pred(Node<T,b>*,ll);
    // // Remove the given element
    // bool remove(T);
    // Traversal based on given type
    void traverse(function<void(T*)> f, Node<T, b> *r=NULL);
    // Print the tree in a pretty format
    friend ostream& operator<<(std::ostream &cout, Tree<T, b> &t){
        cout<<"┬\n";
        t.printNode(t.root,"");
        return cout;
    }
};

#endif