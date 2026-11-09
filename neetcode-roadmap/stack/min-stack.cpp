#include <vector>
#include <algorithm>

//==============================================================================
// LeetCode #155 / NeetCode: Min Stack
// Strategy: Dual Vector Synchronized Prefix Minimum LIFO Buffers
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(1) strictly for push, pop, top, and getMin.
      - push(): O(1) amortized dynamic vector insertion.
      - pop(): O(1) tail removal.
      - top(): O(1) tail read.
      - getMin(): O(1) tail read.
    - Auxiliary Space: O(N) where N is the number of elements active in the stack.
      - Two parallel contiguous integer buffers.

    Algorithmic & Hardware Invariants:
    1. Prefix-Minimum Monotonic Invariant:
       - m_Prefix[i] strictly stores min(m_Main[0...i]).
       - Every push/pop operation maintains synchronized 1:1 sizing between buffers.
    2. Zero Branching on Hot Minimum Evaluation:
       - std::min() maps cleanly to conditional move (CMOV) instructions on x86-64.
*/

class MinStack
{
private:
    std::vector<int> m_Main;
    std::vector<int> m_Prefix;

public:
    MinStack() = default;

    void push(int val)
    {
        m_Main.push_back(val);

        if (m_Prefix.empty())
        {
            m_Prefix.push_back(val);
        }
        else
        {
            m_Prefix.push_back(std::min(m_Prefix.back(), val));
        }
    }

    void pop()
    {
        m_Main.pop_back();
        m_Prefix.pop_back();
    }

    int top() const
    {
        return m_Main.back();
    }

    int getMin() const
    {
        return m_Prefix.back();
    }
};