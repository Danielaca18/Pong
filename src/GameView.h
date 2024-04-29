#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "SDL_surface.h"
#include "GameState.h"
#include "font.h"

class GameView {
public:
    explicit GameView(SDL_Renderer* renderer);
    void render(const GameState& gameState);
    ~GameView();

private:
    SDL_Renderer* m_renderer;
    TTF_Font* font{};
    SDL_Surface* scoreP1{};
    SDL_Surface* scoreP2{};
    SDL_Surface* winner{};
    SDL_Texture* p1ScoreText{};
    SDL_Texture* p2ScoreText{};
    SDL_Texture* winnerText{};
};
