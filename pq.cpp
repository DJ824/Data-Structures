template <typename E, typename C>
class pq
{
public:
    int size() const;
    bool empty() const;
    void insert(const E &e);
    const E &min() const;
    void removeMin();

private:
    std::list<E> L;
    C isLess;
};

template <typename E, typename C>
int pq<E, C>::size() const { return L.size(); }

template <typename E, typename C>
bool pq<E, C>::empty() const { return L.empty(); }

template <typename E, typename C>
void pq<E, C>::insert(const E &e)
{
    typename std::list<E> iterator p;
    p = L.begin();
    while (p != L.end() && isLess(e, *p))
    {
        ++p;
    }
    L.insert(p, e);
}

template <typename E, typename C>
const E &pq<E, C>::min() const
{
    return L.front();
}

template <typename E, typename C>
void pq<E, C>::removeMin()
{
    L.pop_front();
}
