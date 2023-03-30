#pragma once
#include <SDL.h>

/**
 *
 */
struct GameState {
    SDL_FRect player1;
    SDL_FRect player2;
    SDL_FRect ball;
    int player1Score;
    int player2Score;
    float ballXDir;
    float ballYDir;
    float player1YDir;
    float player2YDir;
    bool play;
};
