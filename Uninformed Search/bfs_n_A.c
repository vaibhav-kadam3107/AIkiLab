#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ROWS 20
#define MAX_COLS 20
#define OBSTACLE -1
#define START -2
#define END -3

int ROWS, COLS;

int maze[MAX_ROWS][MAX_COLS];

typedef struct
{
    int row, col;
} Point;

typedef struct
{
    Point point;
    int f; // Evaluation function value
    int g; // Cost from start to current node
} Node;

typedef struct
{
    Node *arr;
    int capacity;
    int size;
} PriorityQueue;

PriorityQueue *createPriorityQueue(int capacity)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->arr = (Node *)malloc(capacity * sizeof(Node));
    return pq;
}

void enqueue(PriorityQueue *pq, Node node)
{
    if (pq->size >= pq->capacity)
    {
        printf("PriorityQueue is full!\n");
        return;
    }
    pq->arr[pq->size++] = node;
}

Node dequeue(PriorityQueue *pq)
{
    if (pq->size <= 0)
    {
        printf("PriorityQueue is empty!\n");
        return (Node){{-1, -1}, -1};
    }
    int minIdx = 0;
    for (int i = 1; i < pq->size; ++i)
    {
        if (pq->arr[i].f < pq->arr[minIdx].f)
        {
            minIdx = i;
        }
    }
    Node minNode = pq->arr[minIdx];
    for (int i = minIdx; i < pq->size - 1; ++i)
    {
        pq->arr[i] = pq->arr[i + 1];
    }
    pq->size--;
    return minNode;
}

bool isValid(Point p)
{
    return p.row >= 0 && p.row < ROWS && p.col >= 0 && p.col < COLS;
}

bool isDestination(Point p)
{
    return maze[p.row][p.col] == END;
}

bool isObstacle(Point p)
{
    return maze[p.row][p.col] == OBSTACLE;
}

void printLists(bool closedList[MAX_ROWS][MAX_COLS], PriorityQueue *openList)
{
    printf("Open List: ");
    for (int i = 0; i < openList->size; ++i)
    {
        printf("(%d, %d, f=%d) ", openList->arr[i].point.row, openList->arr[i].point.col, openList->arr[i].f);
    }
    printf("\n");

    printf("Closed List:\n");
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            if (closedList[i][j])
            {
                printf("X ");
            }
            else
            {
                printf(". ");
            }
        }
        printf("\n");
    }
}

int heuristic(Point p1, Point p2)
{
    return abs(p1.row - p2.row) + abs(p1.col - p2.col);
}

void bestFirstSearch(Point start, Point end)
{
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    PriorityQueue *openList = createPriorityQueue(ROWS * COLS);
    bool closedList[MAX_ROWS][MAX_COLS];
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            closedList[i][j] = false;
        }
    }

    Node startNode = {{start.row, start.col}, abs(start.row - end.row) + abs(start.col - end.col)};
    enqueue(openList, startNode);

    Point parent[MAX_ROWS][MAX_COLS];
    parent[start.row][start.col] = start;

    while (openList->size > 0)
    {
        Node currentNode = dequeue(openList);
        Point currentPoint = currentNode.point;
        closedList[currentPoint.row][currentPoint.col] = true;

        printLists(closedList, openList); // Print open and closed lists

        if (isDestination(currentPoint))
        {
            printf("Path Found!\n");
            Point path[MAX_ROWS * MAX_COLS];
            int pathSize = 0;
            while (!(currentPoint.row == start.row && currentPoint.col == start.col))
            {
                path[pathSize++] = currentPoint;
                currentPoint = parent[currentPoint.row][currentPoint.col];
            }
            path[pathSize++] = start;
            for (int i = pathSize - 1; i >= 0; --i)
            {
                printf("(%d, %d) ", path[i].row, path[i].col);
                if (i > 0)
                {
                    printf("-> ");
                }
            }
            printf("\n");
            return;
        }

        for (int i = 0; i < 4; ++i)
        {
            Point neighbor = {currentPoint.row + dx[i], currentPoint.col + dy[i]};
            if (isValid(neighbor) && !closedList[neighbor.row][neighbor.col] && !isObstacle(neighbor))
            {
                Node neighborNode = {{neighbor.row, neighbor.col}, abs(neighbor.row - end.row) + abs(neighbor.col - end.col)};
                enqueue(openList, neighborNode);
                parent[neighbor.row][neighbor.col] = currentPoint;
            }
        }
    }

    printf("Path not found!\n");
}

void aStarSearch(Point start, Point end)
{
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    char dir[4] = {'U', 'R', 'D', 'L'}; // Directions: Up, Right, Down, Left

    PriorityQueue *openList = createPriorityQueue(ROWS * COLS);
    bool closedList[MAX_ROWS][MAX_COLS];
    int gValues[MAX_ROWS][MAX_COLS]; // G-values for each point
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            closedList[i][j] = false;
            gValues[i][j] = INT_MAX;
        }
    }

    gValues[start.row][start.col] = 0;
    Node startNode = {{start.row, start.col}, heuristic(start, end)};
    enqueue(openList, startNode);

    Point parent[MAX_ROWS][MAX_COLS];
    char pathDirection[MAX_ROWS][MAX_COLS];

    while (openList->size > 0)
    {
        Node currentNode = dequeue(openList);
        Point currentPoint = currentNode.point;
        closedList[currentPoint.row][currentPoint.col] = true;

        printLists(closedList, openList); // Print open and closed lists

        if (isDestination(currentPoint))
        {
            printf("Path Found!\n");
            Point path[MAX_ROWS * MAX_COLS];
            int pathSize = 0;
            while (!(currentPoint.row == start.row && currentPoint.col == start.col))
            {
                path[pathSize++] = currentPoint;
                currentPoint = parent[currentPoint.row][currentPoint.col];
            }
            path[pathSize++] = start;
            for (int i = pathSize - 1; i >= 0; --i)
            {
                printf("(%d, %d) ", path[i].row, path[i].col);
                if (i > 0)
                {
                    Point prev = path[i - 1];
                    for (int dirIdx = 0; dirIdx < 4; ++dirIdx)
                    {
                        if (prev.row == path[i].row + dx[dirIdx] && prev.col == path[i].col + dy[dirIdx])
                        {
                            printf("-> %c ", dir[dirIdx]);
                            break;
                        }
                    }
                }
            }
            printf("\n");
            return;
        }

        for (int i = 0; i < 4; ++i)
        {
            Point neighbor = {currentPoint.row + dx[i], currentPoint.col + dy[i]};
            if (isValid(neighbor) && !closedList[neighbor.row][neighbor.col] && !isObstacle(neighbor))
            {
                int tentative_g = gValues[currentPoint.row][currentPoint.col] + 1;
                if (tentative_g < gValues[neighbor.row][neighbor.col])
                {
                    gValues[neighbor.row][neighbor.col] = tentative_g;
                    int h = heuristic(neighbor, end);
                    Node neighborNode = {{neighbor.row, neighbor.col}, tentative_g + h};
                    enqueue(openList, neighborNode);
                    parent[neighbor.row][neighbor.col] = currentPoint;
                }
            }
        }
    }

    printf("Path not found!\n");
}

void inputMaze()
{
    printf("Enter the number of rows (up to %d): ", MAX_ROWS);
    scanf("%d", &ROWS);
    printf("Enter the number of columns (up to %d): ", MAX_COLS);
    scanf("%d", &COLS);

    printf("Enter the maze, use numbers:\n");
    printf("\n");
    printf("  0 represents empty cells.\n");
    printf("  %d represents obstacles.\n", OBSTACLE);
    printf("  %d represents the start point.\n", START);
    printf("  %d represents the end point.\n", END);

    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            scanf("%d", &maze[i][j]);
        }
    }
}

int main()
{
    inputMaze();

    Point start, end;
    printf("Enter the starting point (row col): ");
    scanf("%d %d", &start.row, &start.col);
    printf("Enter the ending point (row col): ");
    scanf("%d %d", &end.row, &end.col);

    int choice;
    printf("Choose algorithm:\n");
    printf("1. Best-First Search\n");
    printf("2. A* Algorithm\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        bestFirstSearch(start, end);
        break;
    case 2:
        aStarSearch(start, end);
        break;
    default:
        printf("Invalid choice\n");
    }

    return 0;
}


/*

The problem tackled by this C code is finding the shortest path from a given starting point to a specified ending point within a maze. The maze consists of cells, some of which may be obstacles that cannot be traversed, while others are open paths. The objective is to navigate from the starting point to the ending point while avoiding obstacles and minimizing the total distance traveled.

The code implements two AI search algorithms: Best-First Search and A* Algorithm.

### Best-First Search:
- **AI Search Used:** Best-First Search
- **Algorithm:** Best-First Search is an informed search algorithm that explores a graph by expanding the most promising node according to a heuristic function, without considering the cost of reaching that node.
- **Explanation:** In this algorithm, the code explores the maze by prioritizing nodes based solely on their heuristic values, which estimate the distance from the current node to the goal. It expands nodes in order of their heuristic values without considering the actual cost incurred to reach them. The search continues until the goal is found or all reachable nodes are explored.

### A* Algorithm:
- **AI Search Used:** A* Algorithm
- **Algorithm:** A* Algorithm is an informed search algorithm that combines the benefits of both breadth-first search and Best-First Search. It evaluates nodes by combining the cost of reaching the node from the start node (`g` value) and the heuristic estimate of the distance to the goal (`h` value).
- **Explanation:** In this algorithm, the code maintains a priority queue of nodes, prioritizing them based on their combined evaluation function `f = g + h`, where `g` is the cost from the start node to the current node and `h` is the heuristic estimate of the distance to the goal. The algorithm expands nodes with lower `f` values first, considering both the actual cost and the heuristic estimate. This enables it to efficiently find the shortest path while exploring the search space intelligently.

### Overall:
- The code provides solutions to the pathfinding problem in a maze using two different AI search algorithms: Best-First Search and A* Algorithm. These algorithms allow for efficient exploration of the maze, considering either only heuristic estimates or combining them with actual costs to find the shortest path from the starting point to the ending point while avoiding obstacles. The user can choose between these algorithms based on their requirements for finding the optimal path in the maze.

*/
