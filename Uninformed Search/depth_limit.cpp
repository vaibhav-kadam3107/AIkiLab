#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Node
{
public:
    string value;
    vector<Node *> children;

    Node(string val) : value(val) {}
};

bool depthLimitedSearch(Node *node, const string &goal, int depth, int limit, vector<string> &path)
{
    path.push_back(node->value);

    if (node->value == goal)
    {
        return true;
    }
    if (depth >= limit)
    {
        path.pop_back();
        return false;
    }

    for (Node *child : node->children)
    {
        if (depthLimitedSearch(child, goal, depth + 1, limit, path))
        {
            return true;
        }
    }

    path.pop_back();
    return false;
}

bool dls(Node *start, const string &goal, int limit, vector<string> &path)
{
    return depthLimitedSearch(start, goal, 0, limit, path);
}

int main()
{
    // Creating the expanded graph
    Node *A = new Node("A");
    Node *B = new Node("B");
    Node *C = new Node("C");
    Node *D = new Node("D");
    Node *E = new Node("E");
    Node *F = new Node("F");
    Node *G = new Node("G");
    Node *H = new Node("H");
    Node *I = new Node("I");
    Node *J = new Node("J");
    Node *K = new Node("K");
    Node *L = new Node("L");

    A->children.push_back(B);
    A->children.push_back(C);
    A->children.push_back(D);
    B->children.push_back(E);
    B->children.push_back(F);
    D->children.push_back(G);
    D->children.push_back(H);
    E->children.push_back(I);
    E->children.push_back(J);
    G->children.push_back(K);
    G->children.push_back(L);

    string start = "A";
    string goal = "L";
    int limit = 3;
    vector<string> path;

    cout << endl
         << "start state: " << start << " and goal state: " << goal << endl;

    if (dls(A, goal, limit, path))
    {
        cout << "Path found: ";
        for (const string &node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found within depth limit." << endl;
    }
    return 0;
}

/*Overview
The code implements a Depth-Limited Search (DLS) algorithm to find a path from a start node to a goal node in a graph. The graph is represented using nodes, each containing a value and a list of child nodes. The search is limited to a specified depth to prevent infinite recursion in case of cycles.

Node Class
Purpose: Represents a node in the graph.
Attributes:
value: A string storing the value or label of the node.
children: A vector of pointers to child nodes.
Constructor: Initializes the node with a given value.

Depth-Limited Search Function (depthLimitedSearch)
Parameters:
node: The current node being explored.
goal: The target node value we are searching for.
depth: The current depth in the search.
limit: The maximum depth allowed for the search.
path: A reference to a vector storing the path from the start node to the goal node.
Functionality:
Adds the current node's value to the path.
Checks if the current node's value matches the goal. If it does, the search is successful and returns true.
If the current depth exceeds or matches the limit, backtracks by removing the current node from the path and returns false.
Recursively explores each child node. If a child node leads to the goal, the search is successful and returns true.
If no child nodes lead to the goal within the depth limit, backtracks by removing the current node from the path and returns false.

Wrapper Function for DLS (dls)
Purpose: Initializes the depth for the search and calls the depthLimitedSearch function.
Parameters:
start: The starting node for the search.
goal: The target node value.
limit: The maximum depth for the search.
path: A vector to store the path from the start node to the goal node.

Main Function
Graph Creation:
Creates nodes labeled "A" to "L".
Defines the relationships (edges) between nodes to form a graph.
Parameters:
start: The value of the start node ("A").
goal: The value of the goal node ("L").
limit: The depth limit for the search (3 in this case).
Execution:
Calls the dls function to perform the search.
If a path is found within the depth limit, it prints the path.
If no path is found within the depth limit, it indicates that no path was found.

Key Points
Depth-Limited Search (DLS): A variant of depth-first search (DFS) with a depth limit to prevent infinite loops in cyclic graphs.
Backtracking: Removes nodes from the path when no further progress can be made or when the depth limit is reached.
Path Storage: Uses a vector to store and print the path from the start node to the goal node if found.
This code effectively demonstrates the use of DLS to find paths in a graph while managing the depth to avoid infinite recursion and unnecessary explorations.*/