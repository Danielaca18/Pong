#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "SDL_surface.h"
#include "GameState.h"

class GameView {
public:
    explicit GameView(SDL_Renderer* renderer);
    void render(const GameState& gameState);
private:
    SDL_Renderer* m_renderer;
};
