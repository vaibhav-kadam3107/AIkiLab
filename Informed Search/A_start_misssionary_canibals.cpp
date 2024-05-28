#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

class State {
public:
    int missionariesLeft;
    int cannibalsLeft;
    int boat;
    int missionariesRight;
    int cannibalsRight;
    mutable State* parentState;  // Make parentState mutable

    State(int missionariesLeft, int cannibalsLeft, int boat,
          int missionariesRight, int cannibalsRight) : 
          missionariesLeft(missionariesLeft),
          cannibalsLeft(cannibalsLeft),
          boat(boat),
          missionariesRight(missionariesRight),
          cannibalsRight(cannibalsRight),
          parentState(nullptr) {}

    bool isGoal() const {
        return missionariesLeft == 0 && cannibalsLeft == 0;
    }

    bool isValid() const {
        return missionariesLeft >= 0 && cannibalsLeft >= 0 &&
               missionariesRight >= 0 && cannibalsRight >= 0 &&
               (missionariesLeft == 0 || missionariesLeft >= cannibalsLeft) &&
               (missionariesRight == 0 || missionariesRight >= cannibalsRight);
    }

    std::vector<State*> generateSuccessors() const {
        std::vector<State*> successors;
        if (boat == 0) {
            // Boat is on the left side
            for (int i = 0; i <= 2; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (i + j >= 1 && i + j <= 2) {
                        State* newState = new State(missionariesLeft - i, cannibalsLeft - j, 1,
                                missionariesRight + i, cannibalsRight + j);
                        if (newState->isValid()) {
                            newState->parentState = const_cast<State*>(this);
                            successors.push_back(newState);
                        }
                    }
                }
            }
        } else {
            // Boat is on the right side
            for (int i = 0; i <= 2; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (i + j >= 1 && i + j <= 2) {
                        State* newState = new State(missionariesLeft + i, cannibalsLeft + j, 0,
                                missionariesRight - i, cannibalsRight - j);
                        if (newState->isValid()) {
                            newState->parentState = const_cast<State*>(this);
                            successors.push_back(newState);
                        }
                    }
                }
            }
        }
        return successors;
    }

    int getHeuristic() const {
        // Using a simple heuristic: Number of missionaries and cannibals left on the left side
        return missionariesLeft + cannibalsLeft;
    }
};

class CompareStates {
public:
    bool operator()(State* a, State* b) {
        return a->getHeuristic() > b->getHeuristic();
    }
};

State* solve(State* initialState) {
    std::priority_queue<State*, std::vector<State*>, CompareStates> openSet;
    std::unordered_set<State*> closedSet;
    openSet.push(initialState);

    while (!openSet.empty()) {
        State* currentState = openSet.top();
        openSet.pop();

        if (currentState->isGoal()) {
            return currentState;
        }

        closedSet.insert(currentState);

        for (State* successor : currentState->generateSuccessors()) {
            if (closedSet.find(successor) == closedSet.end()) {
                openSet.push(successor);
            }
        }
    }

    return nullptr;
}

void printSolution(State* solution) {
    if (solution == nullptr) {
        std::cout << "No solution found." << std::endl;
        return;
    }

    std::vector<State*> path;
    State* currentState = solution;
    while (currentState != nullptr) {
        path.push_back(currentState);
        currentState = currentState->parentState;
    }

    for (int i = path.size() - 1; i >= 0; i--) {
        currentState = path[i];
        std::cout << "Left: " << currentState->missionariesLeft << " missionaries, " << currentState->cannibalsLeft
                  << " cannibals | Right: " << currentState->missionariesRight << " missionaries, " << currentState->cannibalsRight
                  << " cannibals | Boat: " << (currentState->boat == 0 ? "Left" : "Right") << std::endl;
    }
}

int main() {
    State* initialState = new State(3, 3, 0, 0, 0);
    std::cout << "Initial State:" << std::endl;
    printSolution(initialState);
    State* solution = solve(initialState);
    std::cout << "\nSolution:" << std::endl;
    printSolution(solution);

    // Cleanup: Delete allocated states
    delete initialState;
    delete solution;

    return 0;
}


/*

Problem Description:
The Missionaries and Cannibals problem is a classic puzzle in which three missionaries and three cannibals must cross a river using a boat that can carry at most two people. The challenge is to ensure that cannibals never outnumber missionaries on either side of the river, as this would result in the missionaries being eaten.

AI Search Used:
The code employs Greedy Best-First Search (GBFS). GBFS uses a heuristic to prioritize exploring nodes that appear to be closer to the goal state.

Algorithm:
The algorithm is as follows:

Initialize the state with three missionaries, three cannibals, and the boat on the left side.
Use a priority queue (min-heap) to explore states based on their heuristic value, which is the sum of the number of missionaries and cannibals left on the starting side.
Generate successors by moving the boat with 1 or 2 people (either missionaries or cannibals or a combination of both) to the other side.
Check for goal state: All missionaries and cannibals are on the right side.
Track explored states to avoid cycles and redundant work.

This code implements a solution for the classic "Missionaries and Cannibals" problem using a search algorithm. The problem involves moving three missionaries and three cannibals from the left bank of a river to the right bank using a boat that can carry at most two people, without ever leaving more cannibals than missionaries on either bank. 

The `State` class represents the state of the problem, including the number of missionaries and cannibals on each bank, and the boat's position. The `isGoal` method checks if the goal state (all missionaries and cannibals are on the right bank) is reached. The `isValid` method ensures that the state is valid (no negative numbers and no more cannibals than missionaries on either bank, unless there are no missionaries on that side).

The `generateSuccessors` method creates all possible next states by moving 1 or 2 people from the current boat side to the other side and checking their validity. Each valid new state is added to the list of successors.

The `CompareStates` class is used to compare states based on a heuristic function in the `getHeuristic` method, which simply sums the number of missionaries and cannibals left on the left bank. This heuristic helps prioritize states with fewer people left on the initial bank.

The `solve` function implements the search algorithm using a priority queue (min-heap) to explore the most promising states first. The `closedSet` keeps track of visited states to avoid redundant processing. If a goal state is found, it is returned.

The `printSolution` function prints the sequence of states from the initial state to the goal state, showing the number of missionaries and cannibals on each bank and the boat's position.

In `main`, an initial state with all missionaries and cannibals on the left bank is created and printed. The `solve` function is called to find the solution, which is then printed.

Memory cleanup is done at the end by deleting the allocated states. This implementation effectively demonstrates solving the Missionaries and Cannibals problem using a state space search with a heuristic to guide the search.

*/

