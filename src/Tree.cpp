#include <Tree.hpp>
using namespace std;
typedef long long ll;

Node::Node(Node *p, ll loc)
{
    parent = make_pair(p, loc);
    children = new Node *[b];
    for (ll i = 0; i < b; i++)
    {
        children[i] = NULL;
    }
    data = new T *[b - 1];
    for (ll i = 0; i < b - 1; i++)
    {
        data[i] = NULL;
    }
    size = 0;
}

Node::~Node()
{
    for (int i = 0; i < b; i++)
        if (children[i])
            delete children[i];
    delete[] children;
    for (int i = 0; i < b - 1; i++)
        if (data[i])
            delete data[i];
    delete[] data;
}

Tree::Tree() : root(NULL) {}

ll Tree::binarySearch(T **arr, ll len, T elem)
{
    ll l = 0, r = len - 1, res = -1, mid;
    while (l <= r)
    {
        mid = l + (r - l) / 2;
        if (*arr[mid] <= elem)
        {
            res = mid;
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return res;
}

bool Tree::insert(const T &elem)
{
    Node *p = NULL;
    Node *r = root;
    ll i = -2;
    while (r)
    {
        p = r;
        i = binarySearch(&data(r, 0), size(r), elem);
        if (i == size(r) - 1 && size(r) + 1 < b)
        {
            data(r, size(r)) = new T(elem);
            size(r)++;
            return true;
        }
        else if (i == -1)
            r = child(r, 0);
        else if (*data(r, i) == elem)
            return false;
        else
            r = child(r, i + 1);
    }
    r = new Node(p, i + 1);
    data(r, 0) = new T(elem);
    size(r)++;
    if (!p)
        root = r;
    else
        child(p, i + 1) = r;
    return true;
}

pair<Node *, ll> Tree::find(T elem)
{
    Node *r = root;
    ll i;
    while (r)
    {
        i = binarySearch(&data(r, 0), size(r), elem);
        if (i == -1)
            r = child(r, 0);
        else if (*data(r, i) == elem)
            return make_pair(r, i);
        else
            r = child(r, i + 1);
    }
    return make_pair((Node *)NULL, -1);
}

pair<Node *, ll> Tree::min()
{
    if (!root)
        return make_pair((Node *)NULL, -1);
    Node *r = root;
    while (child(r, 0))
        r = child(r, 0);
    return make_pair(r, 0);
}

pair<Node *, ll> Tree::max()
{
    if (!root)
        return make_pair((Node *)NULL, -1);
    Node *r = root;
    while (child(r, size(r)))
        r = child(r, size(r));
    return make_pair(r, size(r) - 1);
}

pair<Node *, ll> Tree::succ(Node *r, ll i)
{
    if (!child(r, i + 1) && i + 1 < size(r))
        return make_pair(r, i + 1);
    else if (!child(r, i + 1))
    {
        pair<Node *, ll> p = parent(r);
        while (p.first && p.second >= size(p.first))
            p = parent(p.first);
        if (p.first)
            return make_pair(p.first, p.second);
        else
            return make_pair((Node *)NULL, -1);
    }
    while (child(r, i + 1))
    {
        r = child(r, i + 1);
        i = -1;
    }
    return make_pair(r, i + 1);
}

pair<Node *, ll> Tree::pred(Node *r, ll i)
{
    if (!child(r, i) && i != 0)
        return make_pair(r, i - 1);
    else if (!child(r, i))
    {
        pair<Node *, ll> p = parent(r);
        while (p.first && p.second <= 0)
            p = parent(p.first);
        if (p.first)
            return make_pair(p.first, size(p.first) - 1);
        else
            return make_pair((Node *)NULL, -1);
    }
    while (child(r, i))
    {
        ll temp = i;
        i = size(child(r, i));
        r = child(r, temp);
    }
    return make_pair(r, i - 1);
}

void Tree::traverse(function<void(T *)> f, Node *r)
{
    if (!r)
    {
        r = root;
    }
    for (ll i = 0; i < size(r); i++)
    {
        if (child(r, i))
            traverse(f, child(r, i));
        f(&(*data(r, i)));
    }
    if (child(r, size(r)))
        traverse(f, child(r, size(r)));
    return;
}

Tree::~Tree()
{
    if (root)
        delete root;
}

void Tree::printNode(Node *r, string s)
{
    for (ll i = 0; i < size(r); i++)
    {
        if (child(r, i))
        {
            if (i == 0)
            {
                cout << "┬──";
                printNode(child(r, i), s + "│  ");
            }
            else
            {
                cout << s << "├──";
                printNode(child(r, i), s + "│  ");
            }
        }
        if (i == 0 && !child(r, i) && size(r) != 1)
            cout << "┬──" << *data(r, i) << "\n";
        else if (i != size(r) - 1)
            cout << s << "├──" << *data(r, i) << "\n";
    }
    if (size(r) == 1 && !child(r, 0))
    {
        if (child(r, size(r)))
            cout << "┬──";
        else
            cout << "───";
    }
    else
    {
        cout << s;
        if (child(r, size(r)))
            cout << "├──";
        else
            cout << "└──";
    }
    cout << *data(r, size(r) - 1) << "\n";
    if (child(r, size(r)))
    {
        cout << s << "└──";
        printNode(child(r, size(r)), s + "   ");
    }
    return;
}