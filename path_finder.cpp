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


vector<vector<Node>> matrix;
const int rows = 15;
const int cols = 15;
int startx, starty, goalx, goaly;



/**
 * setUp function
 * used to fill the maze with Node elements ith and jth positions
 * @param maze is a string matrix from input
 */

void setUp(char maze[rows][cols]){
    int nodeNumber = 0; // node numbers start from zero

    for (int row = 0; i < rows; ++row){
        for (int col = 0; col < cols; ++col){
            Node node(row, col, nodeNumber);

            if (maze[row][col] == 'S'){ // checking the starting position
                startx = i;
                starty = j;
            }else if (maze[row][col] == 'G'){ // checks the goal
                goalx = i;
                goaly = j;
            }else if (maze[row][col] == 'X'){
                node.isObstacle = true;
            }

            node.x = i; node.y = j;
            matrix[i][j] = node;
            nodeNumber++;
        }
    }
}


/**
 * Path Finder algorithm I am using is BFS
 */
vector<Node> bfs(){
    vector<Node> path;
    queue<Node> toVisit;

    Node currNode = matrix[startx][starty];
    Node goal = matrix[goalx][goaly];

    int directions[4][2] = {
        {1,0}, {0,1}, {-1,0}, {0,-1}
    };
    toVisit.push(currNode);

    // while loop to find path
    while (!toVisit.empty() && currNode.nodeN != goal.nodeN){
        currNode = toVisit.front(); //dequeue
        matrix[currNode.x][currNode.y].isVisited = true; // marked as visited
        path.push_back(currNode);
        toVisit.pop();

        for (const auto& dir: directions){
            int x = currNode.x + dir[0];
            int y = currNode.y + dir[1];

            Node nextNode = matrix[x][y];
            if (nextNode.isObstacle == false && nextNode.isVisited == false){
                nextNode.parentNode = currNode.nodeN;
                toVisit.push(nextNode);
            }
        }
    }

    // This is backtracking
    currNode = path[path.size() - 1];
    for (int i = path.size() - 2; i > -1; --1){
        Node nextNode = path[i];

        if (currNode.parentNode != nextNode.nodeN){
            path.erase(next(path.begin(), i));
        }else{
            currNode = nextNode;
        }
    }
    return path;
}


/**
 * printMaze function to print the solution to the console
 * @param maze is the grid with strings
 * @param path is the path found from bfs
 */

 void printMaze(char maze[rows][cols], vector<Node> path){
    for (int i = 1; i < path.size() - 1; i++){
        Node node = path[i];
        maze[node.x][node.y] = '*';
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << maze[i][j];
        }
        cout << endl;
    }
}


int main(){
    matrix.resize(rows, vector<Node>(cols, Node(0, 0, 0)));
    char maze[rows][cols];

    string input;
    int a, b; // size of the matrix. for now we keeping it at 15 by 15
    cin >> a >> b;
    cin.ignore();

    for (int i = 0; i < a; i++){
        getline(cin, input);

        for (int j = 0; j < b; j++){
            maze[i][j] = input[j];
        }
    }

    setUp(maze);
    vector<Node> path = bfs();

    if (path.empty()){
        cout << "No Path Found" << endl;
    }else{
        printMaze(maze, path);
    }

    return 0;
}


