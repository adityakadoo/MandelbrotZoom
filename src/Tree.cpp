#include <Tree.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;

Node::Node(Node *p, ll loc)
{
    parent = make_pair(p, loc);
    children = new Node *[B];
    for (ll i = 0; i < B; i++)
    {
        children[i] = NULL;
    }
    data = new Entry *[B - 1];
    for (ll i = 0; i < B - 1; i++)
    {
        data[i] = NULL;
    }
    size = 0;
}

Node::~Node()
{
    for (int i = 0; i < B; i++)
        if (children[i])
            delete children[i];
    delete[] children;
    for (int i = 0; i < B - 1; i++)
        if (data[i])
            delete data[i];
    delete[] data;
}

Tree::Tree(ll f) : root(NULL), root_data(NULL) {
    for(ll i=0;i<f*f;i++){
        Entry* e = new Entry(i,-1);
        insert(e);
    }
}

long long Tree::hash(ll v,ll f, ll x, ll y)
{
    if(x==0 && y==0){
        return v;
    }
    ll m = pow(FACTOR*FACTOR,f+1);
    ll res = hash(v+m,f-1,x/2,y/2);
    res -= m;
    res += m*(x % 2 + FACTOR * (y % 2));
    return res;
}

pair<ll, ll> Tree::unhash(ll h, ll f){
    pair<ll,ll> res = make_pair(0,0);
    for(ll i=0;i<f;i++){
        ll temp = h % (FACTOR*FACTOR);
        res.first *= FACTOR;
        res.first += temp % FACTOR;
        res.second *= FACTOR;
        res.second += temp / FACTOR;
        h /= FACTOR*FACTOR;
    }
    return res;
}

ll Tree::binarySearch(Entry **arr,  ll len, Entry *elem)
{
    ll l = 0, r = len - 1, res = -1, mid;
    while (l <= r)
    {
        mid = l + (r - l) / 2;
        if (*arr[mid] <= *elem)
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

bool Tree::put(ll v, ll f, ll x, ll y, ld value){
    Entry *elem = new Entry(hash(v, f, x, y), value);
    return insert(elem);
}

bool Tree::insert(Entry* elem)
{
    if (!root_data)
    {
        root_data = elem;
        return true;
    }
    Node *p = NULL;
    Node *r = root;
    ll i = -2;
    while (r)
    {
        p = r;
        i = binarySearch(&data(r, 0), size(r), elem);
        if (i == size(r) - 1 && size(r) + 1 < B)
        {
            data(r, size(r)) = elem;
            size(r)++;
            return true;
        }
        else if (i == -1)
        {
            r = child(r, 0);
        }
        else if (*data(r, i) == *elem)
        {
            return false;
        }
        else
        {
            r = child(r, i + 1);
        }
    }
    r = new Node(p, i + 1);
    data(r, 0) = elem;
    size(r)++;
    if (!p)
    {
        root = r;
    }
    else
    {
        child(p, i + 1) = r;
    }
    return true;
}

pair<Node *, ll> Tree::find(Entry *elem)
{
    if (*elem == *root_data)
    {
        return make_pair((Node *)NULL, 0);
    }
    Node *r = root;
    ll i;
    while (r)
    {
        i = binarySearch(&data(r, 0), size(r), elem);
        if (i == -1)
        {
            r = child(r, 0);
        }
        else if (*data(r, i) == *elem)
        {
            return make_pair(r, i);
        }
        else
        {
            r = child(r, i + 1);
        }
    }
    return make_pair((Node *)NULL, -1);
}

Entry* Tree::get(ll v, ll f, ll x, ll y){
    Entry* temp = new Entry(hash(v,f,x,y),-1);
    pair<Node *, ll> r = find(temp);
    if(r.first){
        return data(r.first,r.second);
    }
    else if(r.second==0){
        return root_data;
    }
    return NULL;
}

Entry *Tree::min()
{
    if (!root_data)
    {
        return NULL;
    }
    return root_data;
}

Entry *Tree::max()
{
    if (!root)
    {
        return root_data;
    }
    Node *r = root;
    while (child(r, size(r)))
    {
        r = child(r, size(r));
    }
    return data(r, size(r) - 1);
}

Entry *Tree::succ(Entry *elem)
{
    pair<Node *, ll> r = find(elem);
    if (!r.first)
    {
        if (r.second == 0)
        {
            if (!root)
            {
                return NULL;
            }
            r.first = root;
            while (child(r.first, 0))
            {
                r.first = child(r.first, 0);
            }
            return data(r.first, 0);
        }
        return NULL;
    }
    if (!child(r.first, r.second + 1) && r.second + 1 < size(r.first))
    {
        return data(r.first, r.second + 1);
    }
    else if (!child(r.first, r.second + 1))
    {
        pair<Node *, ll> p = parent(r.first);
        while (p.first && p.second >= size(p.first))
        {
            p = parent(p.first);
        }
        if (p.first)
        {
            return data(p.first, p.second);
        }
        else
        {
            return NULL;
        }
    }
    while (child(r.first, r.second + 1))
    {
        r.first = child(r.first, r.second + 1);
        r.second = -1;
    }
    return data(r.first, r.second + 1);
}

Entry *Tree::pred(Entry *elem)
{
    pair<Node *, ll> r = find(elem);
    if (!r.first)
    {
        return NULL;
    }
    if (!child(r.first, r.second) && r.second != 0)
    {
        return data(r.first, r.second - 1);
    }
    else if (!child(r.first, r.second))
    {
        pair<Node *, ll> p = parent(r.first);
        while (p.first && p.second <= 0)
        {
            p = parent(p.first);
        }
        if (p.first)
        {
            return data(p.first, size(p.first) - 1);
        }
        else
        {
            return root_data;
        }
    }
    while (child(r.first, r.second))
    {
        ll temp = r.second;
        r.second = size(child(r.first, r.second));
        r.first = child(r.first, temp);
    }
    return data(r.first, r.second - 1);
}

void Tree::traverse(function<void(Entry *)> f, Node *r)
{
    if (!r)
    {
        r = root;
        f(root_data);
    }
    for (ll i = 0; i < size(r); i++)
    {
        if (child(r, i))
            traverse(f, child(r, i));
        f(data(r, i));
    }
    if (child(r, size(r)))
        traverse(f, child(r, size(r)));
    return;
}

Tree::~Tree()
{
    if (root)
    {
        delete root;
    }
    if (root_data)
    {
        delete root_data;
    }
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

void Tree::zoom_in(ll in){
    for(ll i=0;i<=B;i++){
        if(i!=in){
            delete child(root,i);
            child(root,i)=NULL;
        }
        if(i+1!=in && i!=B){
            delete data(root,i);
            data(root,i)=NULL;
        }
    }
    if(in!=0){
        delete root_data;
        root_data = data(root,in-1);
        data(root,in-1) = NULL;
    }
    Node* temp = child(root,in);
    child(root,in) = NULL;
    delete root;
    root = temp;
}

// void Tree::zoom_out(ll v, ll on){
//     Node* old_root = root;
//     Entry* old_root_data = root_data;
//     root = new Node(NULL,-1);
//     ll f = pow(FACTOR*FACTOR,level(old_root_data->h));
//     ll v = old_root_data->h % f;
//     root_data = new Entry(v,-1);
//     for(ll i=0;i<=b;i++){
//         if()
//     }
// }