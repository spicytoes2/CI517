#include "MyGame.h"

#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <chrono>
#include <thread>

const int WIDTH = 600;
const int HEIGHT = 600;
const int GRID_SIZE = 20;
const int SPACING = 20;

struct Cell {
    int i;
    int j;
    bool walls[4];
    bool visited;
    Cell* previous;

    Cell(int i, int j) : i(i), j(j), visited(false), previous(nullptr) {
        walls[0] = true; // Top wall
        walls[1] = true; // Right wall
        walls[2] = true; // Bottom wall
        walls[3] = true; // Left wall
    }

    void show(SDL_Renderer* renderer, int cols, int rows, bool showPath) {
        int x = i * GRID_SIZE + SPACING;
        int y = j * GRID_SIZE + SPACING;

        // Adjust the starting point and size for spacing
        int startX = x - GRID_SIZE / 2;
        int startY = y - GRID_SIZE / 2;
        int size = GRID_SIZE;

        // Check if the cell is on the edges and adjust the starting point and size
        if (i == 0) {
            startX -= SPACING;
            size += SPACING;
        }
        if (j == 0) {
            startY -= SPACING;
            size += SPACING;
        }
        if (i == cols - 1) {
            size += SPACING;
        }
        if (j == rows - 1) {
            size += SPACING;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        if (walls[0]) {
            SDL_RenderDrawLine(renderer, x, y, x + GRID_SIZE, y);
        }
        if (walls[1]) {
            // Only draw the right wall if it is not the last cell
            if (i != cols - 1 || j != rows - 1) {
                SDL_RenderDrawLine(renderer, x + GRID_SIZE, y, x + GRID_SIZE, y + GRID_SIZE);
            }
        }
        if (walls[2]) {
            SDL_RenderDrawLine(renderer, x + GRID_SIZE, y + GRID_SIZE, x, y + GRID_SIZE);
        }
        if (walls[3]) {
            SDL_RenderDrawLine(renderer, x, y + GRID_SIZE, x, y);
        }

        if (visited) {
            SDL_Rect rect = { x + 1, y + 1, GRID_SIZE - 2, GRID_SIZE - 2 };
            SDL_SetRenderDrawColor(renderer, 204, 171, 185, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

        if (showPath) {
            SDL_Rect rect = { x + 2, y + 2, GRID_SIZE - 2 , GRID_SIZE - 2 };
            //SDL_SetRenderDrawColor(renderer, 161, 26, 44, 255); red
            SDL_SetRenderDrawColor(renderer, 217, 145, 121, 255);
            SDL_RenderFillRect(renderer, &rect);
            //SDL_RenderDrawLine(renderer, x + GRID_SIZE / 2, y + GRID_SIZE / 2, x + GRID_SIZE / 2, y + GRID_SIZE / 2);
        }
    }
};

std::vector<Cell*> grid;
std::vector<Cell*> stack2;
std::vector<Cell*> path;
Cell* current;

int cols, rows;

int index(int i, int j) {
    if (i < 0 || j < 0 || i > cols - 1 || j > rows - 1) {
        return -1;
    }

    return i + j * cols;
}

Cell* getNeighbour(int i, int j);

void removeWalls(Cell* a, Cell* b, int cols, int rows) {
    int x = a->i - b->i;
    if (x == 1) {
        a->walls[3] = false;
        b->walls[1] = false;
    }
    else if (x == -1) {
        a->walls[1] = false;
        b->walls[3] = false;
    }
    int y = a->j - b->j;
    if (y == 1) {
        a->walls[0] = false;
        b->walls[2] = false;
    }
    else if (y == -1) {
        a->walls[2] = false;
        b->walls[0] = false;
    }

    // Special case for the bottom-right cell
    if (b->i == cols - 1 && b->j == rows - 1) {
        // Remove the right and bottom walls of the last cell
        b->walls[1] = false;
        b->walls[2] = false;
        // Remove the left wall of the first cell
        a->walls[3] = false;
    }
}

Cell* getNeighbour(int i, int j) {
    std::vector<Cell*> neighbours;

    int indexTop = index(i, j - 1);
    int indexRight = index(i + 1, j);
    int indexBottom = index(i, j + 1);
    int indexLeft = index(i - 1, j);

    if (indexTop != -1 && !grid[indexTop]->visited) {
        neighbours.push_back(grid[indexTop]);
    }
    if (indexRight != -1 && !grid[indexRight]->visited) {
        neighbours.push_back(grid[indexRight]);
    }
    if (indexBottom != -1 && !grid[indexBottom]->visited) {
        neighbours.push_back(grid[indexBottom]);
    }
    if (indexLeft != -1 && !grid[indexLeft]->visited) {
        neighbours.push_back(grid[indexLeft]);
    }

    if (!neighbours.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, neighbours.size() - 1);
        int r = dis(gen);

        Cell* neighbour = neighbours[r];
        neighbour->previous = grid[i + j * cols];  // Set the previous pointer

        return neighbour;
    }
    else {
        return nullptr;
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() < 0) {
        std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        return 1;
    }



    TTF_Font* font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return 1;
    }

    cols = (WIDTH - 2 * SPACING) / GRID_SIZE;
    rows = (HEIGHT - 2 * SPACING) / GRID_SIZE;

    // Initialize the grid
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < cols; i++) {
            Cell* cell = new Cell(i, j);
            grid.push_back(cell);
        }
    }

    current = grid[0]; // Start at the top-left corner

    while (true) {
        current->visited = true;
        Cell* next = getNeighbour(current->i, current->j);

        if (next) {
            next->visited = true;

            stack2.push_back(current);

            removeWalls(current, next, cols, rows);

            current = next;
        }
        else if (!stack2.empty()) {
            current = stack2.back();
            stack2.pop_back();
        }
        else {
            break;
        }
    }

    // Find the path from the end to the start using the previous pointers
    Cell* pathCell = grid[cols * rows - 1];
    while (pathCell != grid[0]) {
        path.push_back(pathCell);
        pathCell = pathCell->previous;
    }
    path.push_back(grid[0]);

    // Main loop
    bool quit = false;
    int renderIndex = 0;  // Variable to track the current cell being rendered
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 204, 171, 185, 255);
        SDL_RenderClear(renderer);

        // Render the cells
        for (Cell* cell : grid) {
            cell->show(renderer, cols, rows, false);
        }

        // Render the recorded path
        for (int i = 0; i <= renderIndex; i++) {
            path[i]->show(renderer, cols, rows, true);
        }

        // Increment the renderIndex to move to the next cell in the path
        if (renderIndex < path.size() - 1) {
            renderIndex++;
        }

        // Check the length of the fastest route
        if (path.size() < 250) {
            SDL_Rect textRect;
            textRect.x = 0;
            textRect.y = HEIGHT - 15;
            textRect.w = WIDTH / 2;
            textRect.h = 15;

            SDL_SetRenderDrawColor(renderer, 204, 171, 185, 255);
            SDL_RenderFillRect(renderer, &textRect);

            SDL_Surface* surface = TTF_RenderText_Solid(font, "Aaron_Terry-CI517-2022", { 255, 255, 255 });
            if (surface) {
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                if (texture) {
                    SDL_RenderCopy(renderer, texture, NULL, &textRect);
                    SDL_DestroyTexture(texture);
                }
                SDL_FreeSurface(surface);
            }
        }

        SDL_RenderPresent(renderer);

    }

    // Cleanup
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

















/*int main(int argc, char* args[]) {

	try {
        MyGame game;
		game.runMainLoop();
	} catch (EngineException & e) {
		std::cout << e.what() << std::endl;
		getchar();
	}

	return 0;
}*/



