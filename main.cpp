#include <SDL.h>
#include <SDL_ttf.h>
#include "GameController.h"
#include "GameView.h"
#include "GameState.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argv, char** args) {
    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Create instances of the Model, View, and Controller
    GameState gameState;
    GameView gameView(renderer);
    GameController gameController(gameState, gameView);

    bool quit = false;
    SDL_Event event;

    // Main game loop
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            // Switch input handle to directly take events and scan for key up vs key down to handle two inputs at a time
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    gameController.handleInput(event.key.keysym.sym, true);
                    break;
                case SDL_KEYUP:
                    gameController.handleInput(event.key.keysym.sym, false);
                    break;
                default:
                    break;
            }
        }
        gameController.update();
        gameView.render(gameState);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
