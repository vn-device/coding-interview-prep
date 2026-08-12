#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

//---------- Implementation #2 (Range Construction & Strict C++14/17 Standard) ----------
/*
    Optimal Strategy: Amortized O(N) Time | O(N) Auxiliary Space

    Improvements over Implementation #1:

    1. Range Constructor Delegate:
       Replaces manual loop insertion and reserve() calls with the std::unordered_set 
       range constructor (nums.begin(), nums.end()). This delegates bucket allocation 
       and deduplication directly to the container constructor.

    2. C++14/17 Compatibility:
       Employs find(key) == end() lookups to guarantee 100% compilation safety across 
       legacy and modern judging platforms (avoiding C++20 .contains() dependencies).

    3. Natural Zero Initialization:
       Initializes highestStreak to 0 rather than -1. On empty inputs (N = 0), the set 
       is empty, skipping outer loops and returning 0 naturally without early guard clauses.
*/
int longestConsecutive(const std::vector<int>& nums)
{
    const std::unordered_set<int> numsTracker(nums.begin(), nums.end());
    int highestStreak = 0;

    for (const int &num : numsTracker)
    {
        if (numsTracker.find(num - 1) == numsTracker.end())
        {
            int currentNum = num;
            int currentStreak = 1;

            while (numsTracker.find(++currentNum) != numsTracker.end())
            {
                currentStreak++;
            }

            highestStreak = std::max(highestStreak, currentStreak);
        }
    }

    return highestStreak;
}

//---------- Implementation #1 (Manual Set Insertion & Bucket Reservation) ----------
/*
    Optimal Strategy: Amortized O(N) Time | O(N) Auxiliary Space

    1. Sequence-Starter Identification Invariant:
       Querying whether (num - 1) exists in the hash set isolates sequence starters in 
       O(1) average time. Inner while-loops execute strictly for starter elements, 
       guaranteeing that every element in the sequence is visited at most twice (O(N) total).

    2. Explicit Allocation Strategy:
       Calls reserve(nums.size()) up front to prevent dynamic rehashing allocations 
       during explicit loop-based element insertion.

    3. Deduplication via Set Iteration:
       Iterates over the std::unordered_set directly to eliminate redundant checks on 
       duplicate inputs before evaluation.

    4. Refactoring Target:
       Replaces manual loop-based element insertion with standard library range-based 
       iterators (nums.begin(), nums.end()) to simplify set initialization.
*/
// int longestConsecutive(const std::vector<int>& nums)
// {
//     if (nums.empty())
//     {
//         return 0;
//     }

//     std::unordered_set<int> numsTracker;
//     numsTracker.reserve(nums.size());

//     for (const int& num : nums)
//     {
//         numsTracker.insert(num);
//     }

//     int highestStreak = -1;

//     for (const int& num : numsTracker)
//     {
//         if (numsTracker.find(num - 1) == numsTracker.end())
//         {
//             int currentNum = num;
//             int currentStreak = 1;
//             while (numsTracker.find(++currentNum) != numsTracker.end())
//             {
//                 currentStreak++;
//             }

//             highestStreak = std::max(currentStreak, highestStreak);
//         }
//     }

//     return highestStreak;
// }

int main()
{
    // Test Case #1
    std::vector<int> nums1 = {100,4,200,1,3,2};
    std::cout << "Expected Test #1 Output = 4 | Actual Output = " << longestConsecutive(nums1) << std::endl;

    // Test Case #2
    std::vector<int> nums2 = {0,3,7,2,5,8,4,6,0,1};
    std::cout << "Expected Test #2 Output = 9 | Actual Output = " << longestConsecutive(nums2) << std::endl;

    // Test Case #3
    std::vector<int> nums3 = {1,0,1,2};
    std::cout << "Expected Test #3 Output = 3 | Actual Output = " << longestConsecutive(nums3) << std::endl;
    
    return 0;
}