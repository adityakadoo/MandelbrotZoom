#ifndef __TREE__
#define __TREE__
#include <iostream>
#include <functional>
#include <Entry.hpp>
#define b 3
typedef Entry T;

class Node
{
public:
    /* Public data and connected nodes */
    std::pair<Node *, long long> parent;
    Node **children;
    T **data;
    long long size;
    /* Constructors and Destructors */
    // Constructor with parent pointer
    Node(Node *, long long);
    // Default Destructor
    ~Node();
};

#define parent(n) n->parent
#define child(n, i) n->children[i]
#define data(n, i) n->data[i]
#define size(n) n->size

class Tree
{
private:
    Node *root;

    // Binary Search for internal use
    static long long binarySearch(T **, long long, T);
    // Recursive Printer for internal use
    static void printNode(Node *, std::string s);

public:
    // Default Constructor
    Tree();
    // Default Destructor
    ~Tree();

    /* Tree Operations */
    // Inserts the given element
    bool insert(const T &);
    // Find the given element
    std::pair<Node *, long long> find(T);
    // Find min element in the tree
    std::pair<Node *, long long> min();
    // Find max element in the tree
    std::pair<Node *, long long> max();
    // Find successor of the given node
    std::pair<Node *, long long> succ(Node *, long long);
    // Find predecessor of the given node
    std::pair<Node *, long long> pred(Node *, long long);
    // // Remove the given element
    // bool remove(T);
    // Traversal based on given type
    void traverse(std::function<void(T *)> f, Node *r = NULL);
    // Print the tree in a pretty format
    friend std::ostream &operator<<(std::ostream &cout, Tree &t)
    {
        t.printNode(t.root, "");
        return cout;
    }
};

#endif