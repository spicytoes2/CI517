#include "MyEngineSystem.h"

std::vector<std::vector<int>> MyEngineSystem::generateMaze(int width, int height) {
    std::vector<std::vector<int>> maze(height, std::vector<int>(width, 1));
    maze[0][0] = 0;
    dfsMazeGeneration(maze, 0, 0);
    return maze;
}

void MyEngineSystem::dfsMazeGeneration(std::vector<std::vector<int>>& maze, int row, int col) {
    int dr[] = { -1, 0, 1, 0 };
    int dc[] = { 0, 1, 0, -1 };
    std::vector<int> directions = { 0, 1, 2, 3 };
    std::random_shuffle(directions.begin(), directions.end());

    for (int i = 0; i < 4; i++) {
        int nextRow = row + dr[directions[i]];
        int nextCol = col + dc[directions[i]];

        if (nextRow >= 0 && nextRow < maze.size() && nextCol >= 0 && nextCol < maze[0].size()) {
            if (maze[nextRow][nextCol] == 1) {
                maze[row][col] &= ~(1 << directions[i]);
                maze[nextRow][nextCol] &= ~(1 << ((directions[i] + 2) % 4));
                maze[nextRow][nextCol] = 0;
                dfsMazeGeneration(maze, nextRow, nextCol);
            }
        }
    }
}