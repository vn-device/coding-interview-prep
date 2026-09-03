#include <list>
#include <unordered_map>

//==============================================================================
// LeetCode #146: LRU Cache
// Strategy: Hash Map + Doubly-Linked List with O(1) Iterator Splicing
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - get(): O(1) average hash lookup + O(1) pointer splice.
      - put(): O(1) average hash lookup/insertion + O(1) list node splice/eviction.
    - Auxiliary Space: O(C) auxiliary memory where C is the maximum cache capacity.
      - m_Register stores at most C key-value pairs.
      - m_KeyDB stores at most C map entries containing node iterators.

    Algorithmic Invariants & State Transitions:
    1. MRU/LRU Spatial Ordering:
       - m_Register.front() permanently points to the Most Recently Used (MRU) node.
       - m_Register.back() permanently points to the Least Recently Used (LRU) node.
    2. Zero-Copy Node Reordering:
       - std::list::splice detaches and relinks internal list node pointers in O(1)
         without invalidating existing iterators stored in m_KeyDB.
    3. Bidirectional Key-Value Tracking:
       - List nodes store std::pair<int, int> {key, value} so evicting from the back
         provides the key required to erase the corresponding hash table entry in O(1).
*/
class LRUCache
{
private:
    int m_Capacity;
    std::list<std::pair<int, int>> m_Register;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m_KeyDB;

public:
    LRUCache(int capacity) : m_Capacity(capacity)
    {
    }

    int get(int key)
    {
        auto mapIter = m_KeyDB.find(key);
        if (mapIter == m_KeyDB.end())
        {
            return -1;
        }

        m_Register.splice(m_Register.begin(), m_Register, mapIter->second);
        return mapIter->second->second;
    }

    void put(int key, int value)
    {
        auto mapIter = m_KeyDB.find(key);
        if (mapIter != m_KeyDB.end())
        {
            mapIter->second->second = value;
            m_Register.splice(m_Register.begin(), m_Register, mapIter->second);
        }
        else
        {
            if (m_Register.size() == m_Capacity)
            {
                int lruKey = m_Register.back().first;
                m_KeyDB.erase(lruKey);
                m_Register.pop_back();
            }

            m_Register.emplace_front(key, value);
            m_KeyDB[key] = m_Register.begin();
        }
    }
};

//==============================================================================
// LeetCode #146: LRU Cache
// Implementation: In-Place Front Assignment Anti-Pattern (Broken State Logic)
//==============================================================================
/*
    Defect & Failure Mode Analysis:
    1. In-Place Head Mutation Anti-Pattern:
       - 'm_Register.front() = *listIter' does not relocate the accessed node to
         the head of the doubly-linked list.
       - Instead, it overwrites the key-value pair of the existing front node
         in-place, duplicating data and leaving the original accessed node at its
         stale position deeper in the list.
    2. Iterator & Map Desynchronization:
       - Mutating the front node's value leaves m_KeyDB's iterators pointing to
         corrupted data locations.
       - The original key mapping remains tied to the stale downstream node rather
         than the head, causing key-lookup collisions and phantom evictions.
    3. Stale Node Retention:
       - Because the accessed node is never detached or spliced out of its original
         position, subsequent cache capacity evictions ('m_Register.pop_back()')
         can evict actively touched keys while leaving duplicated dead state behind.

    Complexity Characteristics:
    - Time Complexity:
      - get(): O(1) average hash lookup, but produces invalid internal state.
      - put(): O(1) average hash lookup and list insertion, but fails recency tracking.
    - Auxiliary Space: O(C) auxiliary heap memory where C is capacity, corrupted
      by duplicate node values and misaligned map iterators.
*/
// class LRUCache
// {
// private:
//     int m_Capacity;
//     std::list<std::pair<int, int>> m_Register;
//     std::unordered_map<int, std::list<std::pair<int, int>>::iterator> m_KeyDB;

// public:
//     LRUCache(int capacity) : m_Capacity(capacity)
//     {
//     }

//     int get(int key)
//     {
//         auto mapIter = m_KeyDB.find(key);
//         if (mapIter == m_KeyDB.end())
//         {
//             return -1;
//         }

//         auto listIter = mapIter->second;
//         m_Register.front() = *listIter;
//         return (*listIter).second;
//     }

//     void put(int key, int value)
//     {
//         auto mapIter = m_KeyDB.find(key);
//         if (mapIter != m_KeyDB.end())
//         {
//             mapIter->second->second = value;
//             m_Register.front() = *(mapIter->second);
//         }
//         else
//         {
//             if (m_Register.size() == m_Capacity)
//             {
//                 int oldKey = m_Register.back().first;
//                 m_KeyDB.erase(oldKey);
//                 m_Register.pop_back();
//             }

//             m_Register.insert(m_Register.begin(), {key, value});
//             m_KeyDB[key] = m_Register.begin();
//         }
//     }
// };