#include <vector>
#include <queue>
#include <functional>

//==============================================================================
// LeetCode #703: Kth Largest Element in a Stream
// Strategy: Bounded Min-Heap (Size K) with Conditional Sift-Down Pruning
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - Constructor: O(N log K) where N = nums.size()[cite: 13].
      - add(): 
        - O(1) best-case when incoming val <= scores.top() (skips heap mutation).
        - O(log K) worst-case when inserting or evicting elements.
      - find / top: O(1) direct root inspection[cite: 13].
    - Auxiliary Space: O(K) auxiliary heap memory[cite: 13].
      - scores maintains strictly at most K elements across the data stream[cite: 13].

    Algorithmic Optimizations & Invariants:
    1. Early Pruning Invariant:
       - When the heap is at full capacity (size == K), any value val <= scores.top()
         cannot enter the top-K set and is bypassed in O(1) without heap rebalancing.
    2. Min-Heap Root Property:
       - The root of the K-element min-heap (scores.top()) continuously represents the 
         minimum of the K largest elements, which is strictly the k-th largest element overall[cite: 13].
*/
class KthLargest
{
private:
    size_t queueSize;
    std::priority_queue<int, std::vector<int>, std::greater<int>> scores;

public:
    KthLargest(int k, const std::vector<int>& nums)
        : queueSize(static_cast<size_t>(k))
    {
        for (int num : nums)
        {
            add(num);
        }
    }

    int add(int val)
    {
        if (scores.size() < queueSize)
        {
            scores.push(val);
        }
        else if (val > scores.top())
        {
            scores.pop();
            scores.push(val);
        }

        return scores.top();
    }
};

//==============================================================================
// LeetCode #703: Kth Largest Element in a Stream
// Strategy: Bounded Min-Heap (Size K) Invariant
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - Constructor: O(N log K) where N = nums.size().
      - add(): O(log K) amortized time per insertion and rebalance.
      - find / top: O(1) direct root inspection.
    - Auxiliary Space: O(K) auxiliary heap memory.
      - minHeap retains strictly at most K elements at any point in the stream.

    Mathematical Invariants:
    1. Bounded K-Capacity Invariant:
       - minHeap contains exactly the K largest elements encountered in the stream so far.
    2. Min-Heap Root Identity:
       - For any collection of K elements in a min-heap, minHeap.top() = min(K largest elements),
         which is strictly the k-th largest element of the entire sequence.
*/
// class KthLargest
// {
// private:
//     size_t queueSize;
//     std::priority_queue<int, std::vector<int>, std::greater<int>> scores;

// public:
//     KthLargest(int k, const std::vector<int> &nums)
//         : queueSize(static_cast<size_t>(k))
//     {
//         for (size_t i = 0; i < nums.size(); i++)
//         {
//             scores.push(nums[i]);

//             if (scores.size() > queueSize)
//             {
//                 scores.pop();
//             }
//         }
//     }

//     int add(int val)
//     {
//         scores.push(val);

//         if (scores.size() > queueSize)
//         {
//             scores.pop();
//         }

//         return scores.top();
//     }
// };

//==============================================================================
// LeetCode #703: Kth Largest Element in a Stream
// Implementation: Repeated Vector Append & Full Max-Heap Rebuild (TLE)
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - Constructor: O(N) where N = nums.size() to copy nums into scores buffer.
      - add(): O(N + M + k * log(N + M)) per invocation, where M is the call count.
      - Total across M calls: O(M * (N + M)), resulting in Time Limit Exceeded.
    - Auxiliary Space: O(N + M) auxiliary heap memory.
      - scores vector grows linearly with each addition.
      - sortedScores allocates dynamic priority queue storage on every add() call.

    Defects & Bottlenecks:
    1. Redundant State Reconstruction:
       - Rebuilds an entire max-heap from scratch on every invocation of add().
    2. Unbounded Buffer Growth:
       - Keeps all historical numbers instead of discarding elements below the k-th rank.
*/
// class KthLargest
// {
// private:
//     int lowestRank;
//     std::vector<int> scores;

// public:
//     KthLargest(int k, std::vector<int>& nums)
//     : lowestRank(k), scores(nums)
//     {
        
//     }
    
//     int add(int val)
//     {
//         scores.push_back(val);
//         std::priority_queue<int> sortedScores(scores.begin(), scores.end());
        
//         for (int i = 0; i < lowestRank - 1; i++)
//         {
//             sortedScores.pop();
//         }

//         return sortedScores.top();
//     }
// };