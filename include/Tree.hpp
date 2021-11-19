#ifndef __TREE__
#define __TREE__
#include <iostream>
#include <functional>
#include <Entry.hpp>
#define B 4

class Node
{
public:
    /* Public data and connected nodes */
    std::pair<Node *, long long> parent;
    Node **children;
    Entry **data;
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
    Entry *root_data;

    // Hashing function
    static long long hash(long long, long long, long long);
    // DEcoding function
    static std::pair<long long, long long> unhash(long long, long long);
    // Binary Search for internal use
    static long long binarySearch(Entry **, long long, Entry *);
    // Recursive Printer for internal use
    static void printNode(Node *, std::string s);

public:
    // Default Constructor
    Tree(long long);
    // Default Destructor
    ~Tree();

    /* Tree Operations */
    // Put an element with given x and y
    bool put(long long, long long, long long, long long, long long, long double);
    // Inserts the given element
    bool insert(Entry*);
    // Find the given element
    std::pair<Node *, long long> find(Entry *);
    // Get element with given x and y
    Entry* get(long long, long long, long long, long long, long long);
    // Find min element in the tree
    Entry *min();
    // Find max element in the tree
    Entry *max();
    // Find successor of the given node
    Entry *succ(Entry *);
    // Find predecessor of the given node
    Entry *pred(Entry *);
    // // Remove the given element
    // bool remove(T);
    // Traversal based on given type
    void traverse(std::function<void(Entry *)> f, Node *r = NULL);
    // Print the tree in a pretty format
    friend std::ostream &operator<<(std::ostream &cout, Tree &t)
    {
        cout << "┬──" << *t.root_data << "\n└──";
        t.printNode(t.root, "   ");
        return cout;
    }

    /* Extra Functions for Zooming */
    // Zooming in
    void zoom_in(long long, long long, long long, long long);
    // Zooming out
    void zoom_out(long long, long long, long long, long long);
};

#endif