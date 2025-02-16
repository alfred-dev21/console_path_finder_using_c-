#include <iostream>
#include <vector>
#include <string>
#include <queue>


using namespace std;

/**
 * A Node class which represent a position in a maze
 * each node is aware of it's:
 *      1. Position in the maze
 *      2. Knows if it has been visted or is an obstacle
 *      3. Each node has a node number so that they are distictly
 * identifiable
 *      4. while doing path_finding algorithm each node must know it's parent
 */
class Node{
    public:
        int x, y;
        int parentNode, nodeN;
        bool isVisited, isObstacle;

        // Constructor which initializes all instance variables
        Node(int x, int y, int nodeN)
            : x(x), y(y), nodeN(nodeN), parentNode(-1), isObstacle(false),
            isVisited(false){}
};
