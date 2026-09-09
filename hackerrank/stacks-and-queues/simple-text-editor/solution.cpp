#include <iostream>
#include <string>
#include <vector>

struct Operation
{
    int type;           // 1 for Append, 2 for Delete
    std::string text;   // Type 1: string appended; Type 2: string deleted
};

static std::string S;
static std::vector<Operation> UndoStack;

void Append(const std::string& W)
{
    S += W;
    UndoStack.push_back({1, W});
}

void Delete(size_t k)
{
    if (k <= S.size())
    {
        // Cache the exact substring being deleted
        std::string removed = S.substr(S.size() - k);
        S.erase(S.size() - k);
        UndoStack.push_back({2, std::move(removed)});
    }
}

void Print(size_t k)
{
    if (k <= S.size())
    {
        std::cout << S[k - 1] << '\n';
    }
}

void Undo()
{
    if (UndoStack.empty())
    {
        return;
    }

    Operation lastOp = std::move(UndoStack.back());
    UndoStack.pop_back();

    if (lastOp.type == 1)
    {
        // Revert append by shrinking
        S.erase(S.size() - lastOp.text.size());
    }
    else if (lastOp.type == 2)
    {
        // Revert delete by restoring the exact deleted segment
        S += lastOp.text;
    }
}

int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int Q = 0;
    if (!(std::cin >> Q))
    {
        return 0;
    }

    UndoStack.reserve(Q);

    int type = 0;
    while (Q-- && std::cin >> type)
    {
        if (type == 1)
        {
            std::string W;
            std::cin >> W;
            Append(W);
        }
        else if (type == 2)
        {
            size_t k = 0;
            std::cin >> k;
            Delete(k);
        }
        else if (type == 3)
        {
            size_t k = 0;
            std::cin >> k;
            Print(k);
        }
        else if (type == 4)
        {
            Undo();
        }
    }

    return 0;
}

//==============================================================================
// HackerRank: Simple Text Editor
// Strategy: Command Log Delta Stack with Character Buffer Reversion
//==============================================================================
/*
    Complexity Analysis:
    - Time Complexity:
      - Append (Type 1): O(K) where K = W.length().
      - Delete (Type 2): O(K) where K is the count of popped characters.
      - Print (Type 3): O(1) direct random access into contiguous string buffer.
      - Undo (Type 4): O(K) where K is the number of characters re-added or removed.
      - Total Time: O(Total Characters Mutated) across all operations.
    - Auxiliary Space: O(Q * L + M) auxiliary memory.
      - 'PrevMutations' stores command strings for up to Q operations.
      - 'CharsDeleted' acts as a LIFO character pool caching deleted segments.

    Algorithmic & Structural Invariants:
    1. Reversible Mutation Invariant:
       - Only operations of type 1 (Append) and 2 (Delete) mutate the state and push 
         to 'PrevMutations'. Read queries (Type 3) and rollbacks (Type 4) produce no 
         undo log entries.
    2. Character Restoration Symmetry:
       - Characters popped from 'S' in Delete are pushed to 'CharsDeleted' in LIFO order.
       - Undoing a Delete pops from 'CharsDeleted' and appends back onto 'S', preserving 
         exact character ordering without caching full historical string snapshots.

    Architectural Observations & Edge Cases:
    - Command Substring Allocations:
      - Storing raw command strings ("1 abcd") triggers dynamic allocations per mutation.
      - A structured struct { int type; int count; } combined with string storage avoids 
        repetitive 'substr' and 'std::stoi' invocations during Undo().
    - Integer Promotion Hazard:
      - Comparing 'S.length() - k >= 0' evaluates unsigned arithmetic; direct size 
        comparison 'S.length() >= static_cast<size_t>(k)' prevents underflow bugs.
*/

// static std::string S;
// static std::vector<std::string> PrevMutations;
// static std::string CharsDeleted;

// void Append(const std::string &W)
// {
//     S += W;
// }

// void Delete(int k)
// {
//     // if (S.length() - k >= 0)
//     if (static_cast<size_t>(k) <= S.length())
//     {
//         while (k--)
//         {
//             CharsDeleted.push_back(S.back());
//             S.pop_back();
//         }
//     }
// }

// void Print(int k)
// {
//     if (S.size() >= k)
//     {
//         // std::cout << S[k - 1] << std::endl;
//         std::cout << S[k - 1] << "\n";
//     }
// }

// void Undo()
// {
//     if (!PrevMutations.empty())
//     {
//         std::string prevCmd = PrevMutations.back();
//         PrevMutations.pop_back();

//         size_t spacePos = prevCmd.find_first_of(' ');

//         if (prevCmd[0] == '1')
//         {
//             int deletions = static_cast<int>(prevCmd.substr(spacePos + 1).length());

//             while (deletions--)
//             {
//                 S.pop_back();
//             }
//         }
//         else // if prevCmd[0] == '2'
//         {
//             int additions = static_cast<int>(std::stoi(prevCmd.substr(spacePos + 1)));

//             while (additions--)
//             {
//                 S.push_back(CharsDeleted.back());
//                 CharsDeleted.pop_back();
//             }
//         }
//     }
// }

// int main()
// {
//     std::cin.tie(nullptr);
//     std::ios_base::sync_with_stdio(false);
    
//     int Q = 0;
//     std::cin >> Q;
//     std::cin.ignore(); // Discard new line termination from std::cin

//     PrevMutations.reserve(Q);
//     std::string command;

//     while (Q-- && std::getline(std::cin, command))
//     {
//         size_t spacePos = command.find_first_of(' ');

//         if (command[0] == '1')
//         {
//             Append(command.substr(spacePos + 1));
//             PrevMutations.push_back(command);
//         }
//         else if (command[0] == '2')
//         {
//             Delete(std::stoi(command.substr(spacePos + 1)));
//             PrevMutations.push_back(command);
//         }
//         else if (command[0] == '3')
//         {
//             Print(std::stoi(command.substr(spacePos + 1)));
//         }
//         else // if command[0] == '4'
//         {
//             Undo();
//         }
//     }

//     return 0;
// }
