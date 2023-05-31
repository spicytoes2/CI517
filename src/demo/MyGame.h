#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "../engine/GraphicsEngine.h"

struct GameKey {
    Point2 pos;
    bool isAlive;
};



class MyGame : public AbstractGame {
private:
    Rect box;
    Vector2i velocity;
    std::vector<std::shared_ptr<GameKey>> gameKeys;

    /* GAMEPLAY */
    int score, numKeys, lives;
    bool gameWon;

    std::vector<std::vector<int>> maze; // Store the generated maze
    Point2 playerPos; // Store the player's position

    void handleKeyEvents();
    void update();
    void render();
    void renderUI();

    bool isCollidingWithWall(const Point2& position);

public:
    MyGame();
    ~MyGame();
};

#endif