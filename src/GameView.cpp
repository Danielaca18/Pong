#include "GameView.h"

const int PADDLE_WIDTH = 15;
const int PADDLE_HEIGHT = 60;
const int BALL_SIZE = 10;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

GameView::GameView(SDL_Renderer* renderer) : m_renderer(renderer) {
    font = TTF_OpenFont("resources/font/font.ttf", 24);
}

/**
 * Renders view objects to display
 * @param gameState model of game logic
 */
void GameView::render(const GameState& gameState) {
    // Free pointers
    if (scoreP1 != nullptr && scoreP2 != nullptr) {
        SDL_Log("Free scores");
        SDL_FreeSurface(scoreP1);
        SDL_FreeSurface(scoreP2);
        SDL_DestroyTexture(p1ScoreText);
        SDL_DestroyTexture(p2ScoreText);
    }

    if (winner != nullptr) {
        SDL_Log("Free Winner");
        SDL_FreeSurface(winner);
        SDL_DestroyTexture(winnerText);
    }

    // Clear screen
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Render player scores
    SDL_Color textColor = {255, 255, 255};

    scoreP1 = TTF_RenderText_Solid(font,
                                                std::to_string(gameState.player1Score).c_str(), textColor);
    scoreP2 = TTF_RenderText_Solid(font,
                                                std::to_string(gameState.player2Score).c_str(), textColor);

    p1ScoreText = SDL_CreateTextureFromSurface(m_renderer, scoreP1);
    p2ScoreText = SDL_CreateTextureFromSurface(m_renderer, scoreP2);
    SDL_Rect score1 = {100, 10, 40, 60};
    SDL_Rect score2 = {520, 10, 40, 60};
    SDL_RenderCopy(m_renderer, p1ScoreText, nullptr, &score1);
    SDL_RenderCopy(m_renderer, p2ScoreText, nullptr, &score2);

    // Prompt game over if players won
    if (gameState.winner) {
        std::string text = "Player " + std::to_string(gameState.winner) + " Wins!";
        winner = TTF_RenderText_Solid(font, text.c_str(), textColor);
        winnerText = SDL_CreateTextureFromSurface(m_renderer, winner);
        SDL_Rect winnerBox = {SCREEN_WIDTH/2 - 80, SCREEN_HEIGHT/2 - 24, 160, 96};
        SDL_RenderCopy(m_renderer, winnerText, nullptr, &winnerBox);
    }

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

GameView::~GameView() {
    TTF_CloseFont(font);
    SDL_FreeSurface(scoreP1);
    SDL_FreeSurface(scoreP2);
    SDL_FreeSurface(winner);
    SDL_DestroyTexture(p1ScoreText);
    SDL_DestroyTexture(p2ScoreText);
    SDL_DestroyTexture(winnerText);
}
