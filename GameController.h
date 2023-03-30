#pragma once
#include <SDL.h>
#include <ostream>
#include <iostream>
#include <ostream>
#include <math.h>
#include <vector>
#include <time.h>
#include "GameState.h"
#include "GameView.h"

class GameController {
public:
    GameController(GameState& gameState, GameView& gameView);
    void handleInput(SDL_Keycode keycode, bool down);
    void paddleCollision(int collision);
    int checkCollision();
    void update();
private:
    GameState& m_gameState;
    GameView& m_gameView;
};
