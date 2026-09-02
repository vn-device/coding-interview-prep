#include <queue>
#include <utility>

//==============================================================================
// LeetCode #225: Implement Stack using Queues
// Strategy: Dual-Queue Auxiliary Transfer with O(1) std::swap
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - push(): O(N) where N = q1.size() for migrating elements through auxiliary q2.
      - pop(): O(1) direct q1.front() extraction.
      - top(): O(1) direct q1.front() inspection.
      - empty(): O(1) size inspection.
    - Auxiliary Space: O(N) auxiliary memory across both std::queue containers.

    Algorithmic Invariants & State Transitions:
    1. Auxiliary Inversion Invariant:
       - Enqueueing the incoming element into empty q2 prior to draining q1 guarantees 
         the newest element precedes all previously inserted elements in q2.
    2. Zero-Copy Swap Overhead:
       - std::swap(q1, q2) exchanges internal container pointer state in O(1) time 
         without copying elements.
*/
class MyStack
{
private:
    std::queue<int> q1;
    std::queue<int> q2;

public:
    MyStack() = default;

    void push(int x)
    {
        // Ingest new element into auxiliary queue
        q2.push(x);

        // Transfer all existing elements behind the new element
        while (!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }

        // q2 now contains elements in strict LIFO order; swap with q1
        std::swap(q1, q2);
    }

    int pop()
    {
        int topVal = q1.front();
        q1.pop();
        return topVal;
    }

    int top() const
    {
        return q1.front();
    }

    bool empty() const
    {
        return q1.empty();
    }
};

//==============================================================================
// LeetCode #225: Implement Stack using Queues
// Strategy: Single-Queue Ingestion Rotation (Costly Push, O(1) Pop/Top)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - push(): O(N) where N is the current size of queueData.
        - Rotates all N - 1 prior elements behind the newly appended element.
      - pop(): O(1) direct removal from queueData.front().
      - top(): O(1) direct inspection of queueData.front().
      - empty(): O(1) direct size verification.
    - Auxiliary Space: O(N) auxiliary queue memory.

    Algorithmic Invariants & State Design:
    1. Permanent LIFO Invariant:
       - Guarantees queueData.front() is permanently the most recently inserted element.
    2. Zero Pop-Latency Guarantee:
       - Front inspections and pop operations avoid traversal or mutation cycles, 
         optimizing workloads dominated by reads/pops over writes.
*/
class MyStack
{
private:
    std::queue<int> queueData;

public:
    MyStack() = default;

    void push(int x)
    {
        queueData.push(x);
        const size_t rotations = queueData.size() - 1;

        // Invert order at ingestion time: rotate all older elements behind the new head
        for (size_t i = 0; i < rotations; ++i)
        {
            queueData.push(queueData.front());
            queueData.pop();
        }
    }

    int pop()
    {
        const int stackTop = queueData.front();
        queueData.pop();
        return stackTop;
    }

    int top() const
    {
        return queueData.front();
    }

    bool empty() const
    {
        return queueData.empty();
    }
};

//==============================================================================
// LeetCode #225: Implement Stack using Queues
// Strategy: Single-Queue Rotation on Demand (Costly Pop/Top)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - push(): O(1) direct FIFO enqueue into queueIn.
      - pop(): O(N) where N = queueIn.size() to rotate N - 1 elements.
      - top(): O(N) to rotate N - 1 elements, inspect front, and re-enqueue.
      - empty(): O(1) direct container check.
    - Auxiliary Space: O(N) auxiliary queue memory storing N active elements.

    Algorithmic Invariants & Trade-offs:
    1. Lazy Rotation Invariant:
       - Preserves raw FIFO order on push, delaying reordering until an element 
         must be extracted or inspected.
    2. Single-Container Memory Layout:
       - Eliminates secondary queue allocations by reusing queueIn as a circular ring.
*/
class MyStack
{
private:
    std::queue<int> queueIn;
    // std::queue<int> queueOut;

    void RotateQueue()
    {
        for (size_t i = 0; i < queueIn.size() - 1; i++)
        {
            queueIn.push(queueIn.front());
            queueIn.pop();
        }
    }

public:
    MyStack() = default;

    void push(int x)
    {
        queueIn.push(x);
    }

    int pop()
    {
        RotateQueue();
        int stackTop = queueIn.front();
        queueIn.pop();

        return stackTop;
    }

    int top()
    {
        RotateQueue();
        int stackTop = queueIn.front();
        queueIn.push(stackTop);
        queueIn.pop();

        return stackTop;
    }

    bool empty() const
    {
        // return queueIn.empty() && queueOut.empty();
        return queueIn.empty();
    }
};