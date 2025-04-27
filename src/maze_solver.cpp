#include "maze_solver.h"
#include <stack>
using namespace std;

bool MazeSolver::dfs(Maze& maze, int r, int c, vector<vector<bool>>& visited) {
    if (!maze.inBounds(r, c) || maze.isWall(r, c) || visited[r][c]) {
        return false;
    }

    if (r == maze.finish.row && c == maze.finish.col) {
        return true;
    }

    visited[r][c] = true;

    const int dr[] = {-1, 0, 1, 0};
    const int dc[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        int newR = r + dr[i];
        int newC = c + dc[i];

        if (dfs(maze, newR, newC, visited)) {
            Cell currentCell = {r, c};
            maze.path.push_back(currentCell);
            return true;
        }
    }

    return false;
}

bool MazeSolver::solveDFS(Maze& maze) {
    // Clear any existing path
    maze.path.clear();
    
    // Create visited matrix
    vector<vector<bool>> visited(maze.grid.size(), 
                               vector<bool>(maze.grid[0].size(), false));
    
    // Start DFS from the start position
    bool found = dfs(maze, maze.start.row, maze.start.col, visited);
    
    // If path found, add the start position to the path
    if (found) {
        maze.path.push_back(maze.start);
    }
    
    return found;
}
