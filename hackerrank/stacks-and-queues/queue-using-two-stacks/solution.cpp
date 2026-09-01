#include <iostream>
#include <stack>

//==============================================================================
// HackerRank: Queue using Two Stacks
// Strategy: Lazy Amortized Inversion Partitioning
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - Option 1: O(1) direct push onto stackIn.
      - Option 2: O(1) amortized, O(N) worst-case (only when stackOut is empty).
      - Option 3: O(1) amortized, O(N) worst-case (only when stackOut is empty).
      - Total for M operations: O(M) cumulative runtime (O(1) amortized per operation).
    - Auxiliary Space: O(N) auxiliary stack memory where N is the element count.
      - stackIn and stackOut collectively hold exactly N elements.

    Algorithmic Invariants & State Design:
    1. Lazy Transfer Invariant:
       - Elements reside in stackIn in chronological LIFO order.
       - stackIn elements are transferred to stackOut if and only if stackOut is empty.
       - stackOut elements permanently retain reversed chronological FIFO order.
    2. Zero Redundant Shuffling:
       - Every element enters stackIn once, transfers to stackOut once, and is popped once.
*/
typedef unsigned long ULONG;

int main()
{
    int queries = 0;
    std::cin >> queries;

    std::stack<ULONG> stackIn;
    std::stack<ULONG> stackOut;

    while (queries--)
    {
        int option = 0;
        std::cin >> queries;

        if (option == 1)
        {
            ULONG val;
            std::cin >> val;
            stackIn.push(val);
        }
        else if (option == 2)
        {
            if (stackOut.empty())
            {
                while (!stackIn.empty())
                {
                    stackOut.push(stackIn.top());
                    stackIn.pop();
                }
            }

            if (!stackOut.empty())
            {
                stackOut.pop();
            }
        }
        else // if (option == 3) guaranteed by HackerRank
        {
            if (stackOut.empty())
            {
                while (!stackIn.empty())
                {
                    stackOut.push(stackIn.top());
                    stackIn.pop();
                }
            }

            std::cout << stackOut.top() << std::endl;
        }
    }

    return 0;
}

//==============================================================================
// HackerRank: Queue using Two Stacks
// Implementation: Eager Bidirectional Ping-Pong Data Transfer (TLE)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(Q * N) where Q is the query count and N is the queue length.
      - Enqueue (Type 1): O(1) push to s1.
      - Dequeue / Peek (Types 2 & 3): O(N) full array migration from s1 to s2 
        followed by immediate O(N) migration back from s2 to s1.
    - Auxiliary Space: O(N) auxiliary stack memory across s1 and s2.

    Defects & Bottlenecks:
    1. Eager State Reconstruction:
       - Immediately returning elements to s1 after a single dequeue or peek operation
         discards the FIFO ordering already established in s2, causing redundant O(N) moves.
    2. I/O Stream Bottlenecks:
       - std::endl forces manual buffer flushes on every query 3 inspection.
*/
// typedef unsigned long ULONG;

// void MoveData(std::stack<ULONG>& incoming, std::stack<ULONG>& receiving)
// {
//     while (!incoming.empty())
//     {
//         receiving.push(incoming.top());
//         incoming.pop();
//     }
// }

// int main()
// {
//     int queries = 0;
//     std::cin >> queries;
    
//     std::stack<ULONG> s1;
//     std::stack<ULONG> s2;
    
//     while (queries--)
//     {
//         int option = 0;
//         std::cin >> option;
        
//         if (option == 1)
//         {
//             int val = 0;
//             std::cin >> val;
            
//             s1.push(val);
//         }
//         else if (option == 2)
//         {
//             // Move all s1 elements to s2
//             MoveData(s1, s2);
            
//             // Remove s2.top()
//             s2.pop();
            
//             // Move remaining s2 elements back to s1
//             MoveData(s2, s1);
//         }
//         else // if (option == 3)
//         {
//             // Move all s1 elements to s2
//             MoveData(s1, s2);
            
//             std::cout << s2.top() << std::endl;
            
//             // Move all s2 elements back to s1
//             MoveData(s2, s1);
//         }
//     }
           
//     return 0;
// }
