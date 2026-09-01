#include <stack>

//==============================================================================
// LeetCode #232: Implement Queue using Stacks
// Strategy: Dual-Stack Simulation with Lazy Inversion Partitioning
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - push(): O(1) direct ingestion into stackIn.
      - pop(): O(1) amortized, O(N) worst-case on empty stackOut transfers.
      - peek(): O(1) amortized, O(N) worst-case on empty stackOut transfers.
      - empty(): O(1) direct size evaluation across both stack headers.
      - Amortized Proof: Each element is pushed onto stackIn exactly once, 
        transferred to stackOut exactly once, and popped from stackOut exactly once, 
        yielding 3 * O(1) operations per element across its lifecycle.
    - Auxiliary Space: O(N) auxiliary memory where N is total active elements.
      - stackIn and stackOut store a combined total of N elements.

    Algorithmic Invariants & State Design:
    1. Chronological Partition Invariant:
       - stackIn holds incoming elements in chronological order (newest on top).
       - stackOut holds elements in inverted FIFO order (oldest on top).
    2. Lazy Transfer Invariant:
       - Elements are moved from stackIn to stackOut if and only if stackOut is empty.
       - Guarantees the top of stackOut is strictly the oldest un-dequeued element.
*/
class MyQueue
{
private:
    std::stack<int> stackIn;
    std::stack<int> stackOut;

    void transferIfEmpty()
    {
        if (stackOut.empty())
        {
            while (!stackIn.empty())
            {
                stackOut.push(stackIn.top());
                stackIn.pop();
            }
        }
    }

public:
    MyQueue() = default;

    void push(int x)
    {
        stackIn.push(x);
    }

    int pop()
    {
        const int frontVal = peek();
        stackOut.pop();
        return frontVal;
    }

    int peek()
    {
        transferIfEmpty();
        return stackOut.top();
    }

    bool empty() const
    {
        return stackIn.empty() && stackOut.empty();
    }
};