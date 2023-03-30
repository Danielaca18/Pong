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
GameController::GameController(GameState& gameState, GameView& gameView) : m_gameState(gameState), m_gameView(gameView) {
    // Initialize paddle positions
    m_gameState.player1.x = 7.5;
    m_gameState.player1.y = SCREEN_HEIGHT/2;
    m_gameState.player2.x = SCREEN_WIDTH - 22.5;
    m_gameState.player2.y = SCREEN_HEIGHT/2;

    // Set paddle motion to 0
    m_gameState.player1YDir = 0;
    m_gameState.player2YDir = 0;

    // Initialize ball position
    m_gameState.ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
    m_gameState.ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;

    // Initialize ball motion
    m_gameState.ballXDir = 1;

    // Initialize player scores
    m_gameState.player1Score = 0;
    m_gameState.player2Score = 0;

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

    switch (keycode) {
        case SDLK_SPACE:
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
 * Sets ball directions based on "bounce angle"
 * @param collision
 */
void GameController::paddleCollision(int collision) {
    if (collision == -1) {
        float intersectY = (m_gameState.player1.y + (PADDLE_HEIGHT/2)) - m_gameState.ball.y;
        float bounceAngle = (intersectY/(PADDLE_HEIGHT/2)) * MAX_ANGLE;
        m_gameState.ballXDir = (cos(bounceAngle) > 0)?(cos(bounceAngle)):(-cos(bounceAngle));
        m_gameState.ballYDir = -sin(bounceAngle);
        SDL_Log(std::to_string(m_gameState.ballXDir).c_str());
        SDL_Log(std::to_string(m_gameState.ballYDir).c_str());
    } else if (collision == 1) {
        float intersectY = (m_gameState.player2.y + (PADDLE_HEIGHT/2)) - m_gameState.ball.y;
        float bounceAngle = (intersectY/(PADDLE_HEIGHT/2)) * MAX_ANGLE;
        m_gameState.ballXDir = (cos(bounceAngle) < 0)?(cos(bounceAngle)):(-cos(bounceAngle));
        m_gameState.ballYDir = -sin(bounceAngle);
        SDL_Log(std::to_string(m_gameState.ballXDir).c_str());
        SDL_Log(std::to_string(m_gameState.ballYDir).c_str());
    }
}

/**
 * Checks for collisions between ball and paddles
 * @return integer representing paddle responsible for collision (-1: P1, 1: P2)
 */
int GameController::checkCollision() {
    // Check player 1 paddle and ball collision
    if (((m_gameState.ball.x + BALL_SIZE) >= (m_gameState.player1.x - PADDLE_WIDTH/2)) &&
        ((m_gameState.ball.x - BALL_SIZE) <= (m_gameState.player1.x + PADDLE_WIDTH/2))) {
        if ((m_gameState.ball.y + BALL_SIZE >= (m_gameState.player1.y - PADDLE_HEIGHT/2)) &&
            (m_gameState.ball.y - BALL_SIZE <= (m_gameState.player1.y + PADDLE_HEIGHT/2))) {
            m_gameState.ball.x += PADDLE_WIDTH/2;
            return -1;
        }
    }

    // Check player 2 paddle and ball collision
    if (((m_gameState.ball.x + BALL_SIZE) >= (m_gameState.player2.x - PADDLE_WIDTH/2)) &&
        ((m_gameState.ball.x - BALL_SIZE) <= (m_gameState.player2.x + PADDLE_WIDTH/2))) {
        if ((m_gameState.ball.y + BALL_SIZE >= (m_gameState.player2.y - PADDLE_HEIGHT/2)) &&
            (m_gameState.ball.y - BALL_SIZE <= (m_gameState.player2.y + PADDLE_HEIGHT/2))) {
            m_gameState.ball.x -= PADDLE_WIDTH/2;
            return 1;
        }
    }

    return 0;
}

/**
 * Updates game state values each frame
 */
void GameController::update() {
    // Check for collision with paddle
    int collision = checkCollision();
    if (collision) {
        SDL_Log("Collision");
        paddleCollision(collision);
    }

    // Check for collision of ball with top or bottom of screen
    if (m_gameState.ball.y < 0 || m_gameState.ball.y + BALL_SIZE > SCREEN_HEIGHT) {
        m_gameState.ballYDir *= -1;
    }

    // Move ball
    if (m_gameState.play) {
        SDL_Log(std::to_string(m_gameState.ballYDir).c_str());
        SDL_Log(std::to_string(m_gameState.ballXDir).c_str());
        m_gameState.ball.y += m_gameState.ballYDir / (double)(BALL_SPEED * 2);
        m_gameState.ball.x += m_gameState.ballXDir / (double)(BALL_SPEED * 2);
    }

    // Move player 1 paddle within boundaries
    if (m_gameState.player1YDir > 0 && ((m_gameState.player1.y + PADDLE_HEIGHT) < SCREEN_HEIGHT-10)) {
        m_gameState.player1.y += m_gameState.player1YDir / ((double)PADDLE_SPEED * 2);
    } else if (m_gameState.player1YDir < 0 && ((m_gameState.player1.y - PADDLE_HEIGHT/2) > -18)) {
        m_gameState.player1.y += m_gameState.player1YDir / ((double)PADDLE_SPEED * 2);
    }

    // Move player 1 paddle within boundaries
    if (m_gameState.player2YDir > 0 && ((m_gameState.player2.y + PADDLE_HEIGHT) < SCREEN_HEIGHT-10)) {
        m_gameState.player2.y += m_gameState.player2YDir / ((double)PADDLE_SPEED * 2);
    } else if (m_gameState.player2YDir < 0 && ((m_gameState.player2.y - PADDLE_HEIGHT/2) > -18)) {
        m_gameState.player2.y += m_gameState.player2YDir / ((double)PADDLE_SPEED * 2);
    }

    // Check for goal
    if (m_gameState.ball.x < 0) {
        // Add point to player 1 score
        m_gameState.player2Score += 1;

        // Reset ball position and direction
        m_gameState.ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
        m_gameState.ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;
        m_gameState.ballYDir = 0;
        m_gameState.ballXDir = -1;

        // Pause game
        m_gameState.play = false;
    } else if (m_gameState.ball.x + BALL_SIZE > SCREEN_WIDTH) {
        // Add point to player 1 score
        m_gameState.player1Score += 1;

        // Reset ball position and direction
        m_gameState.ball.x = SCREEN_WIDTH / 2 - BALL_SIZE / 2;
        m_gameState.ball.y = SCREEN_HEIGHT / 2 - BALL_SIZE / 2;
        m_gameState.ballYDir = 0;
        m_gameState.ballXDir = 1;

        // Pause game
        m_gameState.play = false;
    }
}
