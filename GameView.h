#pragma once
#include <SDL.h>
#include "GameState.h"

class GameView {
public:
    GameView(SDL_Renderer* renderer);
    void render(const GameState& gameState);
private:
    SDL_Renderer* m_renderer;
};
