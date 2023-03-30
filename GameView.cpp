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
