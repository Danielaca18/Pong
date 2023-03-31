#include "GameView.h"

const int PADDLE_WIDTH = 15;
const int PADDLE_HEIGHT = 60;
const int BALL_SIZE = 10;

GameView::GameView(SDL_Renderer* renderer) : m_renderer(renderer) {}

/**
 * Renders view objects to display
 * @param gameState model of game logic
 */
void GameView::render(const GameState& gameState) {
    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Initialize fonts for player score
    //TTF_Font* font = TTF_OpenFont("Sans", 24);
    SDL_Color textColor = {255, 255, 255};

    /*
    // Render player scores
    SDL_Surface* scoreP1 = TTF_RenderText_Solid(font,
                                                std::to_string(gameState.player1Score).c_str(), textColor);
    SDL_Surface* scoreP2 = TTF_RenderText_Solid(font,
                                                std::to_string(gameState.player1Score).c_str(), textColor);

    SDL_Texture* p1ScoreText = SDL_CreateTextureFromSurface(m_renderer, scoreP1);
    SDL_Texture* p2ScoreText = SDL_CreateTextureFromSurface(m_renderer, scoreP2);
    SDL_Rect score1 = {0, 0, 0, 0};
    SDL_Rect score2 = {0, 0, 0, 0};
    SDL_RenderCopy(m_renderer, p1ScoreText, nullptr, &score1);
    SDL_RenderCopy(m_renderer, p2ScoreText, nullptr, &score2);
    */
    // Render player 1 paddle
    SDL_FRect player1Rect = { gameState.player1.x, gameState.player1.y, PADDLE_WIDTH, PADDLE_HEIGHT };
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRectF(m_renderer, &player1Rect);

    // Render player 2 paddle
    SDL_FRect player2Rect = { gameState.player2.x, gameState.player2.y, PADDLE_WIDTH, PADDLE_HEIGHT };
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRectF(m_renderer, &player2Rect);

    // Render ball
    SDL_FRect ballRect = { gameState.ball.x, gameState.ball.y, BALL_SIZE, BALL_SIZE };
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRectF(m_renderer, &ballRect);

    // Update screen
    SDL_RenderPresent(m_renderer);
}
