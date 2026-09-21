#include <vector>

//==============================================================================
// LeetCode #641: Design Circular Deque
// Strategy: Contiguous Fixed-Size Ring Buffer with Bidirectional Modular Indexing
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(1) for all operations.
      - 'insertFront', 'insertLast', 'deleteFront', 'deleteLast', 'getFront',
        'getRear', 'isEmpty', and 'isFull' execute strictly in constant time with
        zero branch-misprediction penalties or dynamic memory shifts.
    - Auxiliary Space: O(K) static heap buffer allocation where K is capacity.
      - Pre-allocates a fixed contiguous buffer via std::vector constructor sizing,
        guaranteeing zero runtime reallocations, page faults, or allocator lockups.

    Algorithmic & Hardware Invariants:
    1. Disambiguation via Explicit State Counter:
       - Maintains 'm_Size' to track active occupancy, entirely eliminating the
         classic ring buffer pointer-collision ambiguity where 'm_Head == m_Tail'
         signifies both completely empty and completely full states.
    2. Modulo-Safe Circular Offsets:
       - 'insertFront' evaluates '(m_Head - 1 + m_Capacity) % m_Capacity' to step
         counter-clockwise across the boundary; adding 'm_Capacity' explicitly
         prevents negative dividend truncation and out-of-bounds indexing in C++.
       - 'insertLast' evaluates target write slots via '(m_Head + m_Size) % m_Capacity'.
       - 'getRear' accesses the active tail via '(m_Head + m_Size - 1) % m_Capacity'.
    3. Cache-Line Locality & Memory Stability:
       - Binds all deque mutations to a single contiguous cache-friendly array,
         eliminating pointer chasing and heap-fragmentation overheads inherent
         to node-based doubly-linked lists.
*/

class MyCircularDeque
{
private:
    std::vector<int> m_Queue;
    int m_Capacity;
    int m_Head;
    int m_Size;

public:
    MyCircularDeque(int k)
        : m_Queue(k), m_Capacity(k), m_Head(0), m_Size(0)
    {
    }

    bool insertFront(int value)
    {
        if (!isFull())
        {
            m_Head = (m_Head - 1 + m_Capacity) % m_Capacity;
            m_Queue[m_Head] = value;
            ++m_Size;
            return true;
        }

        return false;
    }

    bool insertLast(int value)
    {
        if (!isFull())
        {
            int rearPos = (m_Head + m_Size) % m_Capacity;
            m_Queue[rearPos] = value;
            ++m_Size;
            return true;
        }

        return false;
    }

    bool deleteFront()
    {
        if (!isEmpty())
        {
            m_Head = (m_Head + 1) % m_Capacity;
            --m_Size;
            return true;
        }

        return false;
    }

    bool deleteLast()
    {
        if (!isEmpty())
        {
            --m_Size;
            return true;
        }

        return false;
    }

    int getFront() const
    {
        if (!isEmpty())
        {
            return m_Queue[m_Head];
        }

        return -1;
    }

    int getRear() const
    {
        if (!isEmpty())
        {
            int rearPos = (m_Head + m_Size - 1) % m_Capacity;
            return m_Queue[rearPos];
        }

        return -1;
    }

    bool isEmpty() const
    {
        return m_Size == 0;
    }

    bool isFull() const
    {
        return m_Size == m_Capacity;
    }
};