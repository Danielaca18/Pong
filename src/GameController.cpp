#include "GameController.h"

const int PADDLE_SPEED = 5;
const int PADDLE_WIDTH = 15;
const int PADDLE_HEIGHT = 60;
const int BALL_SPEED = 5;
const int BALL_SIZE = 10;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX_ANGLE = 45;

/**
 * Initializes game controller object
 * @param gameState Model of game logic
 * @param gameView View of game
 */
GameController::GameController(GameState& gameState):m_gameState(gameState) {
    // Game values
    resetPaddles();
    resetBall(0);
    resetGame();

    // Start game paused
    m_gameState.play = false;
}

/**
 * Maps user input to corresponding game logic
 * @param keycode
 * @param down
 */
void GameController::handleInput(SDL_Keycode keycode, bool down) {
    // Move player 1 paddle
    switch (keycode) {
        case SDLK_w:
            m_gameState.player1YDir = (down)?-1:0;
            break;
        case SDLK_s:
            m_gameState.player1YDir = (down)?1:0;
            break;
        default:
            break;
    }

    // Move player 2 paddle
    switch (keycode) {
        case SDLK_UP:
            m_gameState.player2YDir = (down)?-1:0;
            break;
        case SDLK_DOWN:
            m_gameState.player2YDir = (down)?1:0;
            break;
        default:
            break;
    }

    // Pause/unpause game
    switch (keycode) {
        case SDLK_SPACE:
            if (m_gameState.winner) m_gameState.winner = 0;
            m_gameState.play = true;
            break;
        case SDLK_p:
            m_gameState.play = false;
            break;
        default:
            break;
    }
}

/**
 * Updates ball direction after collision
 * @param collision
 */
void GameController::paddleCollision(int collision) {
    if (collision == 1) {
        float intersectY = (m_gameState.player1.y + (PADDLE_HEIGHT/(float)2)) - m_gameState.ball.y;
        float bounceAngle = (intersectY/(PADDLE_HEIGHT/(float)2)) * MAX_ANGLE;
        m_gameState.ballXDir = (cos(bounceAngle) > 0)?(cos(bounceAngle)):(-cos(bounceAngle));
        m_gameState.ballYDir = -sin(bounceAngle);
        SDL_Log("%s", std::to_string(m_gameState.ballXDir).c_str());
        SDL_Log("%s", std::to_string(m_gameState.ballYDir).c_str());
    } else if (collision == 2) {
        float intersectY = (m_gameState.player2.y + (PADDLE_HEIGHT/(float)2)) - m_gameState.ball.y;
        float bounceAngle = (intersectY/(PADDLE_HEIGHT/(float)2)) * MAX_ANGLE;
        m_gameState.ballXDir = (cos(bounceAngle) < 0)?(cos(bounceAngle)):(-cos(bounceAngle));
        m_gameState.ballYDir = -sin(bounceAngle);
        SDL_Log("%s", std::to_string(m_gameState.ballXDir).c_str());
        SDL_Log("%s", std::to_string(m_gameState.ballYDir).c_str());
    }
}

/**
 * Resets game values
 */
void GameController::resetGame() {
    // Initialize player scores
    m_gameState.player1Score = 0;
    m_gameState.player2Score = 0;

    // Initialize game winner
    m_gameState.winner = 0;
}

/**
 * Sets paddle positions to default
 */
void GameController::resetPaddles() {
    // Initialize paddle positions
    m_gameState.player1.x = 7.5;
    m_gameState.player1.y = SCREEN_HEIGHT/(double)2 - PADDLE_HEIGHT/(double)2;
    m_gameState.player2.x = SCREEN_WIDTH - 22.5;
    m_gameState.player2.y = SCREEN_HEIGHT/(double)2 - PADDLE_HEIGHT/(double)2;

    // Set paddle motion to 0
    m_gameState.player1YDir = 0;
    m_gameState.player2YDir = 0;
}

/**
 * Resets ball position and direction
 * @param dir integer represents ball direction to start with
 */
void GameController::resetBall(int dir = 0) {
    // Initialize ball position
    m_gameState.ball.x = SCREEN_WIDTH / (double) 2 - BALL_SIZE / (double) 2;
    m_gameState.ball.y = SCREEN_HEIGHT / (double) 2 - BALL_SIZE / (double) 2;

    // Set ball Y direction
    m_gameState.ballYDir = 0;
    m_gameState.ballXDir = (!dir)?1:-1;
}

/**
 * Checks for collisions with ball
 */
void GameController::checkCollision() {
    // Check player 1 paddle and ball collision
    if (((m_gameState.ball.x + BALL_SIZE) >= (m_gameState.player1.x - PADDLE_WIDTH/(double)2)) &&
        ((m_gameState.ball.x - BALL_SIZE) <= (m_gameState.player1.x + PADDLE_WIDTH/(double)2))) {
        if ((m_gameState.ball.y + BALL_SIZE >= (m_gameState.player1.y - PADDLE_HEIGHT/(double)2)) &&
            (m_gameState.ball.y - BALL_SIZE <= (m_gameState.player1.y + PADDLE_HEIGHT/(double)2))) {
            m_gameState.ball.x += PADDLE_WIDTH/(double)2;
            paddleCollision(1);
        }
    }

    // Check player 2 paddle and ball collision
    if (((m_gameState.ball.x + BALL_SIZE) >= (m_gameState.player2.x - PADDLE_WIDTH/(double)2)) &&
        ((m_gameState.ball.x - BALL_SIZE) <= (m_gameState.player2.x + PADDLE_WIDTH/(double)2))) {
        if ((m_gameState.ball.y + BALL_SIZE >= (m_gameState.player2.y - PADDLE_HEIGHT/(double)2)) &&
            (m_gameState.ball.y - BALL_SIZE <= (m_gameState.player2.y + PADDLE_HEIGHT/(double)2))) {
            m_gameState.ball.x -= PADDLE_WIDTH/(double)2;
            paddleCollision(2);
        }
    }

    // Check for collision of ball with top or bottom of screen
    if (m_gameState.ball.y < 0 || m_gameState.ball.y + BALL_SIZE > SCREEN_HEIGHT) {
        m_gameState.ballYDir *= -1;
    }
}

/**
 * Checks if either player has won
 * @return int winner of game
 */
int GameController::checkWin() const {
    if (m_gameState.player1Score > 9) {
        return 1;
    } else if (m_gameState.player2Score > 9) {
        return 2;
    }

    return 0;
}

/**
 * Updates game state values each frame
 */
void GameController::update() {
    // Check for ball collisions
    checkCollision();

    // Move ball
    if (m_gameState.play) {
        SDL_Log("%s", std::to_string(m_gameState.ballYDir).c_str());
        SDL_Log("%s", std::to_string(m_gameState.ballXDir).c_str());
        m_gameState.ball.y += m_gameState.ballYDir / (float)(BALL_SPEED * 2);
        m_gameState.ball.x += m_gameState.ballXDir / (float)(BALL_SPEED * 2);
    }

    // Move player paddles
    if (m_gameState.player1YDir > 0 && ((m_gameState.player1.y + PADDLE_HEIGHT) < SCREEN_HEIGHT - 10)) {
        m_gameState.player1.y += m_gameState.player1YDir / ((float) PADDLE_SPEED * 2);
    } else if (m_gameState.player1YDir < 0 && ((m_gameState.player1.y - PADDLE_HEIGHT / (float) 2) > -18)) {
        m_gameState.player1.y += m_gameState.player1YDir / ((float) PADDLE_SPEED * 2);
    } if (m_gameState.player2YDir > 0 && ((m_gameState.player2.y + PADDLE_HEIGHT) < SCREEN_HEIGHT-10)) {
        m_gameState.player2.y += m_gameState.player2YDir / ((float)PADDLE_SPEED * 2);
    } else if (m_gameState.player2YDir < 0 && ((m_gameState.player2.y - PADDLE_HEIGHT/(double)2) > -18)) {
        m_gameState.player2.y += m_gameState.player2YDir / ((float)PADDLE_SPEED * 2);
    }

    // Check for goal
    if (m_gameState.ball.x < 0) {
        ++m_gameState.player2Score;
        // Reset paddles and ball
        resetBall(1);
        resetPaddles();
        // Pause game
        m_gameState.play = false;
    } else if (m_gameState.ball.x + BALL_SIZE > SCREEN_WIDTH) {
        ++m_gameState.player1Score;
        // Reset paddles and ball
        resetBall();
        resetPaddles();
        // Pause game
        m_gameState.play = false;
    }

    int winner = checkWin();
    // Check if game is over
    if (winner) {
        m_gameState.winner = winner;
        m_gameState.player1Score = 0;
        m_gameState.player2Score = 0;
    }
}
