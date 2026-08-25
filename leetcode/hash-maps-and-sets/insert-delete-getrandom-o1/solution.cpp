#include <stdlib.h>
#include <unordered_map>
#include <vector>

//---------- Implementation #2 (Vector + Map Dual-Structure Swap-and-Pop) ----------
/*
    Optimal Strategy: O(1) Time | O(N) Auxiliary Space

    1. Dual-Structure State Synchronization:
       Pairs std::vector<int> (for contiguous storage and O(1) random indexing) with 
       std::unordered_map<int, int> (mapping value -> vector index for O(1) lookup).

    2. O(1) Vector Swap-and-Pop Deletion Mechanism:
       Avoids O(N) element shifting during vector deletions by overwriting the target 
       element (values[valIndex]) with the array's last element (values.back()). 
       Updates the moved element's map index (setDB[lastVal] = valIndex) prior to 
       executing pop_back() and map erase operations.

    3. Edge Case Handling (Single-Element / End Deletions):
       When removing the final vector element (val == lastVal), updating setDB[lastVal] 
       performs a self-assignment before immediate erasure, preserving state consistency 
       without requiring conditional branching.
*/
class RandomizedSet
{
private:
    std::unordered_map<int, int> setDB;
    std::vector<int> values;

public:
    RandomizedSet() {}

    bool insert(int val)
    {
        if (setDB.find(val) == setDB.end())
        {
            values.push_back(val);
            setDB[val] = static_cast<int>(values.size() - 1);
            return true;
        }

        return false;
    }

    bool remove(int val)
    {
        if (setDB.find(val) != setDB.end())
        {
            int valIndex = setDB[val];
            int lastVal = values.back();
            
            values[valIndex] = lastVal;
            setDB[lastVal] = valIndex;

            values.pop_back();
            setDB.erase(val);
            
            return true;
        }

        return false;
    }

    int getRandom()
    {
        return values[rand() % values.size()];
    }
};

//---------- Implementation #1 (Single-Map Frequency Tracker - Flawed) ----------
/*
    Suboptimal Approach: Non-Functional for O(1) Operations

    1. Functional Limitation of std::unordered_map:
       Using std::unordered_map<int, int> as a frequency counter tracks existence, 
       but cannot provide O(1) uniform random element selection (getRandom). 
       Iterating over bucket chains or hash slots requires O(N) linear time traversal.

    2. Structural Imbalance:
       Lacks a contiguous underlying array (like std::vector) necessary to perform 
       direct indexed array accesses (values[rand() % size]) in strict O(1) time.

    3. Architectural Takeaway:
       Hash tables provide O(1) key-value lookup and deletion, but require pairing 
       with contiguous linear memory to achieve true O(1) random access.
*/
// class RandomizedSet
// {
// private:
//     std::unordered_map<int, int> setDB;

// public:
//     RandomizedSet() {}

//     bool insert(int val)
//     {
//         setDB[val]++;
//         return (setDB[val] == 1) ? true : false;
//     }

//     bool remove(int val)
//     {

//     }

//     int getRandom()
//     {
        
//     }
// };