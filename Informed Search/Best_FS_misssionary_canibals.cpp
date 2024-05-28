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
    State* parentState;

    State(int missionariesLeft, int cannibalsLeft, int boat,
          int missionariesRight, int cannibalsRight) : 
          missionariesLeft(missionariesLeft),
          cannibalsLeft(cannibalsLeft),
          boat(boat),
          missionariesRight(missionariesRight),
          cannibalsRight(cannibalsRight),
          parentState(nullptr) {}

    bool isGoal() {
        return missionariesLeft == 0 && cannibalsLeft == 0;
    }

    bool isValid() {
        return missionariesLeft >= 0 && cannibalsLeft >= 0 &&
               missionariesRight >= 0 && cannibalsRight >= 0 &&
               (missionariesLeft == 0 || missionariesLeft >= cannibalsLeft) &&
               (missionariesRight == 0 || missionariesRight >= cannibalsRight);
    }

    std::vector<State*> generateSuccessors() {
        std::vector<State*> successors;
        if (boat == 0) {
            // Boat is on the left side
            for (int i = 0; i <= 2; i++) {
                for (int j = 0; j <= 2; j++) {
                    if (i + j >= 1 && i + j <= 2) {
                        State* newState = new State(missionariesLeft - i, cannibalsLeft - j, 1,
                                missionariesRight + i, cannibalsRight + j);
                        if (newState->isValid()) {
                            newState->parentState = this;
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
                            newState->parentState = this;
                            successors.push_back(newState);
                        }
                    }
                }
            }
        }
        return successors;
    }

    int getHeuristic() {
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

This code solves the "Missionaries and Cannibals" problem, which requires moving all missionaries and cannibals from the left bank to the right bank of a river using a boat that can carry up to two people, while ensuring that cannibals never outnumber missionaries on either bank.

The `State` class models the state of the problem. Each state includes the number of missionaries and cannibals on the left and right banks, the boat's position (0 for left bank, 1 for right bank), and a pointer to the parent state.

The `isGoal` method checks if all missionaries and cannibals have been successfully moved to the right bank, while `isValid` ensures no invalid states occur (such as negative numbers of people or more cannibals than missionaries on any bank, unless there are no missionaries on that side).

The `generateSuccessors` method produces all possible next states by moving 1 or 2 people from the current boat position to the opposite bank and validates each new state. The boat's position toggles between 0 and 1 to reflect its movement.

The heuristic function, `getHeuristic`, calculates the sum of missionaries and cannibals left on the left bank, guiding the search towards states with fewer people remaining on the initial bank.

The `CompareStates` class is a functor that compares two states based on their heuristic values, used by the priority queue in the `solve` function.

The `solve` function uses a priority queue (min-heap) to explore states, prioritizing those with lower heuristic values. It tracks visited states using an unordered set to avoid reprocessing. The function returns the goal state if found, or `nullptr` if no solution exists.

The `printSolution` function traces the path from the initial state to the goal state by following parent pointers, and prints the sequence of states.

In the `main` function, an initial state with all missionaries and cannibals on the left bank is created and printed. The `solve` function is called to find a solution, which is then printed. Memory cleanup is performed at the end by deleting the initial and solution states.

This code effectively demonstrates solving the Missionaries and Cannibals problem using a heuristic-based search algorithm.


Detailed Breakdown:
State Class:

Represents the state of the puzzle with attributes for the number of missionaries and cannibals on both sides and the boat's position.
isGoal: Checks if the current state is the goal state.
isValid: Checks if the current state is valid (i.e., no more cannibals than missionaries on either side).
generateSuccessors: Generates all possible valid states that can be reached from the current state by moving the boat.
getHeuristic: Returns the heuristic value (number of people left on the left side).
CompareStates Class:

Used to order states in the priority queue based on their heuristic value.
solve Function:

Uses a priority queue to manage the states to explore, prioritizing states with a lower heuristic value.
Explores each state by generating its successors and checking if any of them is the goal state.
printSolution Function:

Prints the solution path from the initial state to the goal state by tracing back from the goal state using the parentState pointers.
main Function:

Initializes the initial state and starts the solving process.
Prints the initial state and the solution path if found.
This code uses Greedy Best-First Search to solve the Missionaries and Cannibals problem by exploring states based on a heuristic that prioritizes states with fewer people left on the starting side. The solution is printed as a sequence of states from the initial state to the goal state.



*/
