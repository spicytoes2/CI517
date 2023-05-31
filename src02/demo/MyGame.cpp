#include "MyGame.h"

/*const int WIDTH = 600;
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

    void show(GraphicsEngine* gfx, int cols, int rows) {
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

        gfx->setDrawColor(SDL_COLOR_BLACK);

        if (walls[0]) {
            gfx->drawLine(Point2(startX, startY), Point2(startX + size, startY));
        }
        if (walls[1]) {
            // Only draw the right wall if it is not the last cell
            if (i != cols - 1 || j != rows - 1) {
                gfx->drawLine(Point2(startX + size, startY), Point2(startX + size, startY + size));
            }
        }
        if (walls[2]) {
            gfx->drawLine(Point2(startX + size, startY + size), Point2(startX, startY + size));
        }
        if (walls[3]) {
            gfx->drawLine(Point2(startX, startY + size), Point2(startX, startY));
        }

        if (visited) {
            int rectX = startX + 1;
            int rectY = startY + 1;
            int rectW = size - 2;
            int rectH = size - 2;

            gfx->setDrawColor(SDL_COLOR_PINK);
            gfx->fillRect(rectX, rectY, rectW, rectH);
        }
    }
};

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30) {
    /*TTF_Font* font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
    gfx->useFont(font);
    gfx->setVerticalSync(true);

    for (int i = 0; i < numKeys; i++) {
        std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
        k->isAlive = true;
        k->pos = Point2(getRandom(0, 750), getRandom(0, 550));
        gameKeys.push_back(k);
    }

    //gfx->setFullscreen(true);

    // Initialize the maze with a size of 10x10
    maze = mySystem->generateMaze(10, 10);

    // Set the player's initial position
    playerPos = Point2(0, 0);
}

MyGame::~MyGame() {
}

void MyGame::handleKeyEvents() {
    int speed = 1;

    if (eventSystem->isPressed(Key::W)) {
        Point2 newPos = Point2(playerPos.x, playerPos.y - speed);
        if (!isCollidingWithWall(newPos)) {
            playerPos = newPos;
        }
    }

    if (eventSystem->isPressed(Key::S)) {
        Point2 newPos = Point2(playerPos.x, playerPos.y + speed);
        if (!isCollidingWithWall(newPos)) {
            playerPos = newPos;
        }
    }

    if (eventSystem->isPressed(Key::A)) {
        Point2 newPos = Point2(playerPos.x - speed, playerPos.y);
        if (!isCollidingWithWall(newPos)) {
            playerPos = newPos;
        }
    }

    if (eventSystem->isPressed(Key::D)) {
        Point2 newPos = Point2(playerPos.x + speed, playerPos.y);
        if (!isCollidingWithWall(newPos)) {
            playerPos = newPos;
        }
    }
}

void MyGame::update() {
    // Update the game logic
}

void MyGame::render() {
    // Clear the screen
    gfx->clearScreen();

    // Render the maze
    int mazeWidth = maze[0].size();
    int mazeHeight = maze.size();

    // Calculate the size of each cell
    int cellWidth = (WIDTH - 2 * SPACING) / mazeWidth;
    int cellHeight = (HEIGHT - 2 * SPACING) / mazeHeight;

    // Render the maze cells
    for (int row = 0; row < mazeHeight; ++row) {
        for (int col = 0; col < mazeWidth; ++col) {
            if (maze[row][col] == 1) {
                // Calculate the position of the current cell
                int x = col * cellWidth + SPACING;
                int y = row * cellHeight + SPACING;

                // Draw the walls of the cell
                gfx->setDrawColor(SDL_COLOR_RED);
                if (maze[row][col] & 1) {
                    // Top wall
                    gfx->drawLine(Point2(x, y), Point2(x + cellWidth, y));
                }
                if (maze[row][col] & 2) {
                    // Right wall
                    gfx->drawLine(Point2(x + cellWidth, y), Point2(x + cellWidth, y + cellHeight));
                }
                if (maze[row][col] & 4) {
                    // Bottom wall
                    gfx->drawLine(Point2(x + cellWidth, y + cellHeight), Point2(x, y + cellHeight));
                }
                if (maze[row][col] & 8) {
                    // Left wall
                    gfx->drawLine(Point2(x, y + cellHeight), Point2(x, y));
                }

                // Fill the cell if it is visited
                if (maze[row][col] & 16) {
                    SDL_Rect rect = { x + 1, y + 1, cellWidth - 2, cellHeight - 2 };
                    gfx->setDrawColor(SDL_COLOR_AQUA);
                    SDL_RenderFillRect(gfx->renderer, &rect);
                }
            }
        }
    }

    
    SDL_RenderPresent(gfx->renderer);
}

void MyGame::renderUI() {
    // Render the UI elements
}

bool MyGame::isCollidingWithWall(const Point2& position) {
    int row = position.y / 40;
    int col = position.x / 40;

    // Check if the player's position is within the maze bounds
    if (row >= 0 && row < maze.size() && col >= 0 && col < maze[0].size()) {
        // Check if the player is colliding with a wall
        if (maze[row][col] == 1) {
            return true;
        }
    }

    return false;
}*/