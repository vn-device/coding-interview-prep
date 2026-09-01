#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//-------------- Brute Force Method - Time Complexity O(N) --------------
vector<int> asteroidCollision(const vector<int>& asteroids)
{
    // Worst edge case scenario
    if (asteroids.size() < 2)
    {
        return asteroids;
    }

    // Let asteroidStack use stacking concept to monitor which asteroids will persist
    // Note: asteroidStack may (not) be the same length of vector<int>& asteroids
    vector<int> stack;
    stack.reserve(asteroids.size());

    for (int incoming : asteroids)
    {
        bool incomingDestroyed = false;

        // Only consider whenever abs(stack.back) > 0 and incoming < 0
        while (!stack.empty() && stack.back() > 0 && incoming < 0)
        {
            // Destroy stack back and continue looping
            if (stack.back() < abs(incoming))
            {
                stack.pop_back();
            }
            // Destroy stack back and incoming
            else if (stack.back() == abs(incoming))
            {
                stack.pop_back();
                incomingDestroyed = true;
                break;
            }
            // Stack back is bigger, so destroy only incoming
            else
            {
                incomingDestroyed = true;
                break;
            }
        }

        if (!incomingDestroyed)
        {
            stack.push_back(incoming);
        } 
    }

    return stack;
}

int main()
{
    // Test Case #1 - Expected Output = [5,10]
    vector<int> aster1 = {5,10,-5};
    vector<int> out1 = asteroidCollision(aster1);
    cout << "Expected Test Case #1 Output = [5,10]\n";
    cout << "  Actual Test Case #1 Output = [";
    for (size_t i = 0; i < out1.size(); i++)
    {
        if (i < out1.size() - 1)
            cout << out1[i] << ",";
        else
            cout << out1[i];
    }
    cout << "]\n\n";

    // Test Case #2 - Expected Output = []
    vector<int> aster2 = {8,-8};
    vector<int> out2 = asteroidCollision(aster2);
    cout << "Expected Test Case #2 Output = []\n";
    cout << "  Actual Test Case #2 Output = [";
    for (size_t i = 0; i < out2.size(); i++)
    {
        if (i < out2.size() - 1)
            cout << out2[i] << ",";
        else
            cout << out2[i];
    }
    cout << "]\n\n";

    // Test Case #3 - Expected Output = [10]
    vector<int> aster3 = {10,2,-5};
    vector<int> out3 = asteroidCollision(aster3);
    cout << "Expected Test Case #3 Output = [10]\n";
    cout << "  Actual Test Case #3 Output = [";
    for (size_t i = 0; i < out3.size(); i++)
    {
        if (i < out3.size() - 1)
            cout << out3[i] << ",";
        else
            cout << out3[i];
    }
    cout << "]\n\n";

    // Test Case #4 - Expected Output = [-6,2,4]
    vector<int> aster4 = {3,5,-6,2,-1,4};
    vector<int> out4 = asteroidCollision(aster4);
    cout << "Expected Test Case #4 Output = [-6,2,4]\n";
    cout << "  Actual Test Case #4 Output = [";
    for (size_t i = 0; i < out4.size(); i++)
    {
        if (i < out4.size() - 1)
            cout << out4[i] << ",";
        else
            cout << out4[i];
    }
    cout << "]\n\n";

    // Test Case #5 - Expected Output = [-2,-1,1,2]
    vector<int> aster5 = {-2,-1,1,2};
    vector<int> out5 = asteroidCollision(aster5);
    cout << "Expected Test Case #5 Output = [-2,-1,1,2]\n";
    cout << "  Actual Test Case #5 Output = [";
    for (size_t i = 0; i < out5.size(); i++)
    {
        if (i < out5.size() - 1)
            cout << out5[i] << ",";
        else
            cout << out5[i];
    }
    cout << "]\n\n";
    
    return 0;
}