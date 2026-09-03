#include <vector>

//==============================================================================
// LeetCode #622: Design Circular Queue
// Strategy: Fixed-Capacity Ring Buffer with Modular Pointer Wrap-Around
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(1) strictly deterministic across all member functions
      (enQueue, deQueue, Front, Rear, isEmpty, isFull).
      - Buffer lookups, writes, and cursor increments execute via constant-time 
        modular arithmetic operations without any dynamic memory shifting.
    - Auxiliary Space: O(K) auxiliary heap memory.
      - m_Buffer pre-allocates exactly K integer elements once upon instantiation.
      - Zero dynamic reallocations, memory movements, or deallocations during execution.

    Hardware & State Invariants:
    1. Flat Contiguous Storage & Cache Alignment:
       - Elements are stored sequentially in a single contiguous std::vector buffer, 
         maximizing spatial locality and L1 data cache line utilization.
    2. Modular Wrap-Around Invariant:
       - Advances m_Head and m_Tail using (index + 1) % m_Capacity to cycle within [0, K - 1].
    3. Positive Modulo Protection:
       - Calculates the tail element index as (m_Tail - 1 + m_Capacity) % m_Capacity, 
         preventing negative modulo evaluation when m_Tail == 0.
    4. State Disambiguation:
       - Maintains m_CurrentSize to distinguish empty (size == 0) from full (size == capacity) 
         states without requiring an unwritten sentinel slot.
*/
class MyCircularQueue
{
private:
    std::vector<int> m_Buffer;
    int m_Capacity;
    int m_CurrentSize;
    int m_Head;
    int m_Tail;

public:
    MyCircularQueue(int k)
        : m_Buffer(k), m_Capacity(k), m_CurrentSize(0), m_Head(0), m_Tail(0)
    {
    }

    bool enQueue(int value)
    {
        if (isFull())
        {
            return false;
        }

        m_Buffer[m_Tail] = value;
        m_Tail = (m_Tail + 1) % m_Capacity;
        m_CurrentSize++;

        return true;
    }

    bool deQueue()
    {
        if (isEmpty())
        {
            return false;
        }

        m_Head = (m_Head + 1) % m_Capacity;
        m_CurrentSize--;

        return true;
    }

    int Front() const
    {
        if (isEmpty())
        {
            return -1;
        }

        return m_Buffer[m_Head];
    }

    int Rear() const
    {
        if (isEmpty())
        {
            return -1;
        }

        int lastIdx = (m_Tail - 1 + m_Capacity) % m_Capacity;
        return m_Buffer[lastIdx];
    }

    bool isEmpty() const
    {
        return m_CurrentSize == 0;
    }

    bool isFull() const
    {
        return m_CurrentSize == m_Capacity;
    }
};