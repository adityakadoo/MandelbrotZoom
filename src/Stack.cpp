#include <Stack.hpp>
typedef long long ll;
typedef long double ld;
typedef unsigned long int usi;

Stack::Stack()
{
    curr_size = 0;
    capacity = BASE_CAPACITY;
    elements = new ll[capacity];
}

Stack::~Stack()
{
    delete[] elements;
}

void Stack::grow()
{
    capacity *= GROWTH_FACTOR;
    ll *temp = new ll[capacity];
    for (ll i = 0; i < curr_size; i++)
    {
        temp[i] = elements[i];
    }
    delete[] elements;
    elements = temp;
    return;
}

ll Stack::size()
{
    return curr_size;
}

bool Stack::empty()
{
    return curr_size == 0;
}

void Stack::push(ll elem)
{
    if (curr_size >= capacity)
    {
        grow();
    }
    elements[curr_size] = elem;
    curr_size++;
    return;
}

ll Stack::top()
{
    if (curr_size > 0)
    {
        return elements[curr_size - 1];
    }
    return -1;
}

void Stack::pop()
{
    if (curr_size > 0)
    {
        curr_size--;
    }
    return;
}