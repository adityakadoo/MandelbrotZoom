#include <Tree.hpp>
#include <queue>
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

Tree::Tree(ll f) : root(NULL), root_data(NULL)
{
    for (ll i = 0; i < f * f; i++)
    {
        Entry *e = new Entry(i, -1);
        insert(e);
    }
}

long long Tree::hash(ll x, ll y, ll resol)
{
    ll res = 0;
    ll f = resol / FACTOR;
    while (f > 0)
    {
        res *= FACTOR * FACTOR;
        res += (y % FACTOR + FACTOR * (x % FACTOR));
        x /= FACTOR;
        y /= FACTOR;
        f /= FACTOR;
    }
    return res;
}

pair<ll, ll> Tree::unhash(ll h, ll f)
{
    pair<ll, ll> res = make_pair(0, 0);
    for (ll i = 0; i < f; i++)
    {
        ll temp = h % (FACTOR * FACTOR);
        res.first *= FACTOR;
        res.first += temp % FACTOR;
        res.second *= FACTOR;
        res.second += temp / FACTOR;
        h /= FACTOR * FACTOR;
    }
    return res;
}

ll Tree::binarySearch(Entry **arr, ll len, Entry *elem)
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

bool Tree::put(ll v, ll f, ll x, ll y, ll resol, ld value)
{
    Entry *elem = new Entry(v + pow(FACTOR * FACTOR, f) * hash(x, y, resol), value);
    return insert(elem);
}

bool Tree::insert(Entry *elem)
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
        i = binarySearch(&data(r, 0), nodesize(r), elem);
        if (i == nodesize(r) - 1 && nodesize(r) + 1 < B)
        {
            data(r, nodesize(r)) = elem;
            nodesize(r)++;
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
    nodesize(r)++;
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
        i = binarySearch(&data(r, 0), nodesize(r), elem);
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

Entry *Tree::get(ll v, ll f, ll x, ll y, ll resol)
{
    Entry *temp = new Entry(v + pow(FACTOR * FACTOR, f) * hash(x, y, resol), -1);
    pair<Node *, ll> r = find(temp);
    if (r.first)
    {
        return data(r.first, r.second);
    }
    else if (r.second == 0)
    {
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
    while (child(r, nodesize(r)))
    {
        r = child(r, nodesize(r));
    }
    return data(r, nodesize(r) - 1);
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
    if (!child(r.first, r.second + 1) && r.second + 1 < nodesize(r.first))
    {
        return data(r.first, r.second + 1);
    }
    else if (!child(r.first, r.second + 1))
    {
        pair<Node *, ll> p = parent(r.first);
        while (p.first && p.second >= nodesize(p.first))
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
            return data(p.first, nodesize(p.first) - 1);
        }
        else
        {
            return root_data;
        }
    }
    while (child(r.first, r.second))
    {
        ll temp = r.second;
        r.second = nodesize(child(r.first, r.second));
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
    for (ll i = 0; i < nodesize(r); i++)
    {
        if (child(r, i))
            traverse(f, child(r, i));
        f(data(r, i));
    }
    if (child(r, nodesize(r)))
        traverse(f, child(r, nodesize(r)));
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
    for (ll i = 0; i < nodesize(r); i++)
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
        if (i == 0 && !child(r, i) && nodesize(r) != 1)
            cout << "┬──" << *data(r, i) << "\n";
        else if (i != nodesize(r) - 1)
            cout << s << "├──" << *data(r, i) << "\n";
    }
    if (nodesize(r) == 1 && !child(r, 0))
    {
        if (child(r, nodesize(r)))
            cout << "┬──";
        else
            cout << "───";
    }
    else
    {
        cout << s;
        if (child(r, nodesize(r)))
            cout << "├──";
        else
            cout << "└──";
    }
    cout << *data(r, nodesize(r) - 1) << "\n";
    if (child(r, nodesize(r)))
    {
        cout << s << "└──";
        printNode(child(r, nodesize(r)), s + "   ");
    }
    return;
}

void Tree::zoom_in(ll zn, ll f, ll resol, ll in)
{
    if (!root)
    {
        return;
    }
    for (ll i = 0; i < B; i++)
    {
        if (i != in && child(root, i))
        {
            delete child(root, i);
            child(root, i) = NULL;
        }
        if (i + 1 != in && i + 1 != B && data(root, i))
        {
            delete data(root, i);
            data(root, i) = NULL;
        }
    }
    if (in != 0 && root_data)
    {
        delete root_data;
        root_data = data(root, in - 1);
        data(root, in - 1) = NULL;
    }
    Node *temp = child(root, in);
    child(root, in) = NULL;
    delete root;
    root = temp;
    ll a = pow(FACTOR * FACTOR, f);
    ll b = pow(FACTOR * FACTOR, f - 1) * resol * resol;
    ll lim = a * pow((resol / FACTOR), 2);
    for (ll i = 0; i < lim; i += a)
    {
        for (ll j = 1; j < 4; j++)
        {
            Entry *e = new Entry(root_data->h + i + j * b, -1);
            insert(e);
        }
    }
}

void Tree::zoom_out(ll zn, ll f, ll resol, ll on)
{
    Node *old_root = root;
    root = NULL;
    Entry *old_root_data = root_data;
    root_data = NULL;

    queue<Node *> q;
    q.push(old_root);
    while (!q.empty())
    {
        Node *s = q.front();
        for (ll i = 0; i < B; i++)
        {
            if (child(child(s, i), 0))
            {
                q.push(child(s, i));
            }
            else
            {
                delete child(s, i);
                child(s, i) = NULL;
            }
        }
        q.pop();
    }

    ll a = pow(FACTOR * FACTOR, f);
    ll b = pow(FACTOR * FACTOR, f) * resol * resol;
    root = new Node(NULL, -1);
    if (on == 0)
    {
        insert(old_root_data);
        child(root, 0) = old_root;
        root_data = old_root_data;
    }
    else
    {
        root_data = new Entry(zn, -1);
    }
    for (ll i = 0; i < B; i++)
    {
        if (i + 1 != on && i + 1 != B)
        {
            Entry *temp = new Entry(zn + (i + 1) * a, -1);
            insert(temp);
        }
        else if (i + 1 == on)
        {
            insert(old_root_data);
            child(root, i + 1) = old_root;
        }
    }
    for (ll i = zn + FACTOR * FACTOR * a; i < b; i += a)
    {
        if (old_root_data->h > i || old_root_data->h + a <= i)
        {
            Entry *temp = new Entry(i, -1);
            insert(temp);
        }
    }
}