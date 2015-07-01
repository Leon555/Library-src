#include <iostream>
#include <vector>
#include <list>
#include <map>

using std::cout;
using std::map;
using std::vector;
using std::endl;
using std::list;

class LRUCache{
private:
    struct item_t{
        int key, val;
        item_t(int k, int v) : key(k), val(v) { }
    };
    typedef list<item_t> list_t;
    typedef map<int, list_t::iterator> map_t;
    map_t m_map;
    list_t m_list;
    int m_capacity;
public:
    LRUCache(int c) : m_capacity(c) { }
    
    int get(int key) {
        cout << "getting key: " << key << endl;
        map_t::iterator it = m_map.find(key);
        if(it == m_map.end())
            return -1;
        
        m_map[key] = promote(it->second);
        return m_map[key]->val;
    }
    
    void set(int key, int value) {
        map_t::iterator it = m_map.find(key);
        
        if(it != m_map.end()) {
#ifdef DEBUG
            cout << it->first << endl;
#endif
            m_map[key] = promote(it->second);
            m_map[key]->val = value;
        }
        else{
            if(m_map.size() < m_capacity)
                m_map[key] = m_list.insert(m_list.end(), item_t(key, value));
            else{
                m_map.erase(m_list.front().key);
                m_list.pop_front();
                m_map[key] = m_list.insert(m_list.end(), item_t(key, value));
            }
        }

#ifdef DEBUG     
        it = m_map.begin();
        while(it != m_map.end()) {
            cout << it->second->key << "->" << it->second->val << endl;
            it++;
        }
        cout << endl;
#endif
    }
    list_t::iterator promote(list_t::iterator it)
    {
        list_t::iterator inew = m_list.insert(m_list.end(), *it);
        m_list.erase(it);
        return inew;
    }
};

int main()
{
    LRUCache cache(4);
    cache.get(5);
    cache.set(1, 0);
    cache.set(2, 1);
    cache.set(3, 2);
    cache.set(4, 3);
    cache.set(5, 4);
    cache.set(6, 5);
    
}