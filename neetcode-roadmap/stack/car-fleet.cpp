#include <vector>
#include <algorithm>
#include <utility>

//==============================================================================
// LeetCode #853 / NeetCode: Car Fleet
// Strategy: Descending Position Sort + Scalar Monotonic Fleet Tracking
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity: O(N log N) where N = position.size().
      - Pairing and sorting cars by position descending takes O(N log N).
      - Single linear sweep computing arrival times takes O(N).
    - Auxiliary Space: O(N) for the contiguous (position, speed) pair buffer.
      - Replaces the explicit O(N) monotonic stack with two register scalars
        (fleets, slowestTime), eliminating secondary heap allocations.

    Algorithmic & Hardware Invariants:
    1. Front-to-Back Causal Ordering:
       - Sorting positions descending ensures each leading fleet's arrival time
         is resolved before evaluating trailing cars behind it.
    2. Stack-to-Scalar Compression:
       - Because fleets only merge into slower leading fleets, the monotonic
         stack only ever queries its top element and pushes strictly larger times.
         Tracking 'slowestTime' in a register achieves identical behavior in O(1)
         extra space.
    3. Exact IEEE-754 Division:
       - Casting distance to double prevents integer truncation on fractional
         arrival times.
*/
int carFleet(int target, const std::vector<int>& position, const std::vector<int>& speed)
{
    const int n = static_cast<int>(position.size());
    std::vector<std::pair<int, int>> cars;
    cars.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        cars.emplace_back(position[i], speed[i]);
    }

    // Sort by position descending (closest to target first)
    std::sort(cars.begin(), cars.end(), [](const auto& a, const auto& b)
    {
        return a.first > b.first;
    });

    int fleets = 0;
    double slowestTime = 0.0;

    for (const auto& car : cars)
    {
        const double arrivalTime = static_cast<double>(target - car.first) / car.second;

        // If this car takes strictly longer than the fleet ahead, it cannot catch up
        if (arrivalTime > slowestTime)
        {
            ++fleets;
            slowestTime = arrivalTime;
        }
    }

    return fleets;
}