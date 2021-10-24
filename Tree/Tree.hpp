#ifndef __TREE__
#define __TREE__
#include <bits/stdc++.h>
using namespace std;

#define a 2
#define b 4

template<typename T>
class Node
{
public:
    /* Public data and connected nodes */
    Node<T>* parent;
    Node<T>** children;
    T data;
    /* Constructors and Destructors */
    // Default constructor
    Node();
    // Constructor with given data
    Node(T);
    // Default Destructor
    ~Node();
};

#define parent(n) n->parents.front()
#define left(n) n->children.front()
#define right(n) n->children.back()
#define data(n) n->data
enum traversal_type {PRE, POST, IN, EULER};

template<typename K,typename V>
class Tree
{
private:
    Node<T>* root;
public:
    // Default Constructor
    Tree(): root(NULL){}

    /* Tree Operations */
    // Inserts the given element into the tree
    bool insert(T, bool);
    // Find the given key
    Node<T>* find(T);
    //
    Node<T>* min();
    Node<T>* max();
    Node<T>* succ(Node<T>*);
    Node<T>* pred(Node<T>*);
    bool remove(T);
    void traverse(traversal_type,function<void(Node<T>*)>,Node<T>*);
    friend ostream& operator<<(std::ostream&, Tree<T>&);
};

#endif