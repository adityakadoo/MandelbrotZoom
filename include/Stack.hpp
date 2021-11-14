#ifndef __STACK__
#define __STACK__

#define BASE_CAPACITY 1
#define GROWTH_FACTOR 2

class Stack
{
private:
    // Stores the element of the stack
    long long *elements;
    // Stores the current size
    long long curr_size;
    // Stores the current capacity
    long long capacity;

    /* Growth strategy */
    // Quadratic growth
    void grow();

public:
    /* Constructors and Destructors */
    // Default Constructor
    Stack();
    // Default Destructor
    ~Stack();

    /* Size access */
    // returns the current size
    long long size();
    // returns true if empty
    bool empty();

    /* Elements access */
    // Pushes element onto the stack
    void push(long long);
    // Returns topmost element on the stack
    long long top();
    // Pops the topmost element from the stack
    void pop();
};

#endif
