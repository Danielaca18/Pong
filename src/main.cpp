#include <SDL.h>
#include <SDL_ttf.h>
#include "GameController.h"
#include "GameView.h"
#include "GameState.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// SDL does not support overriding, so command line args must be redundantly included
int main(int argv, char** args) {
    // Init sdl and sdl_ttf
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL failed to initialize: %s", SDL_GetError());
    }
    if (TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_ttf failed to initialize: %s", SDL_GetError());
    }

    // Renders main window
    SDL_Window* window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Create instances of the Model, View, and Controller
    GameState gameState{};
    GameView gameView(renderer);
    GameController gameController(gameState);

    bool quit = false;
    SDL_Event event;

    // Main game loop
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            // Switch input handle to user input
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

    // Deconstruction functions
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
