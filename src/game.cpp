#include "game.h"
#include <raylib.h>
#include <cstdlib>


// Basket properties
float basketWidth = 120.0f;
float basketHeight = 30.0f;
CODS basketPos((WindowX - basketWidth) / 2.0f, WindowY - basketHeight - 20.0f);
float basketSpeed = 0.4;

// Ball properties
float ballRadius = 20.0f;
CODS ballPos(WindowX / 2.0f, ballRadius + 10.0f);
float ballSpeedY = 0.2f;      // Start with a small initial speed
float ballSpeedIncrement = 0.0005f; // Speed increase after each point

// Detect collision between ball and basket
int collision = 0;
float ballBottom = ballPos.getY() + ballRadius;
float basketTop = basketPos.getY();
float basketLeft = basketPos.getX();
float basketRight = basketPos.getX() + basketWidth;

bool gameOver = false;

float Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void Event() {
    if (gameOver) {
        if (IsKeyPressed(KEY_R)) {
            // Reset game state
            collision = 0;
            float minX = ballRadius;
            float maxX = WindowX - ballRadius;
            float randomX = minX + static_cast<float>(rand()) / RAND_MAX * (maxX - minX);
            ballPos.set(randomX, ballRadius + 10.0f);
            ballSpeedY = 0.2f; // Reset to initial speed
            gameOver = false;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
            exit(0);
        }
        return;
    }
    // Move basket left with 'A', right with 'D'
    if (IsKeyDown(KEY_A)) basketPos.setX(basketPos.getX() - basketSpeed);
    if (IsKeyDown(KEY_D)) basketPos.setX(basketPos.getX() + basketSpeed);
    // Clamp basket within window bounds using Clamp function
    basketPos.setX(Clamp(basketPos.getX(), 0, WindowX - basketWidth));
}

void Update() {
    if (gameOver) return;

    // Apply gravity to ball
    ballPos.setY(ballPos.getY() + ballSpeedY);

    // Update collision variables
    float ballBottom = ballPos.getY() + ballRadius;
    float basketTop = basketPos.getY();
    float basketLeft = basketPos.getX();
    float basketRight = basketPos.getX() + basketWidth;

    // Check if the bottom of the ball touches the top of the basket and is horizontally within the basket
    if (ballBottom >= basketTop &&
        ballPos.getX() >= basketLeft &&
        ballPos.getX() <= basketRight) {
        collision++;
        // Increase ball speed after each point
        ballSpeedY += ballSpeedIncrement;

        // Reset ball to a random X position at the top
        float minX = ballRadius;
        float maxX = WindowX - ballRadius;
        float randomX = minX + static_cast<float>(rand()) / RAND_MAX * (maxX - minX);
        ballPos.set(randomX, ballRadius + 10.0f);
    }

    // If the ball misses the basket (falls below the window), set game over
    if (ballBottom > WindowY) {
        gameOver = true;
    }
}

void Draw() {
    // Draw basket on the bottom of the window
    DrawRectangle(static_cast<int>(basketPos.getX()), static_cast<int>(basketPos.getY()),
                  static_cast<int>(basketWidth), static_cast<int>(basketHeight), BROWN);

    // Draw ball at the top of the window
    DrawCircle(static_cast<int>(ballPos.getX()), static_cast<int>(ballPos.getY()), ballRadius, ORANGE);

    // Draw collision count (score) at the top-left corner
    DrawText(TextFormat("Score: %d", collision), 20, 20, 30, DARKGRAY);

    // If game over, show prompt and clickable options
    if (gameOver) {
        int centerX = WindowX / 2;
        int centerY = WindowY / 2;

        DrawRectangle(centerX - 200, centerY - 80, 400, 160, Fade(RAYWHITE, 0.95f));
        DrawText("Game Over!", centerX - 100, centerY - 60, 40, RED);
        DrawText(TextFormat("Final Score: %d", collision), centerX - 100, centerY - 10, 30, DARKGRAY);

        // Draw "Play Again" button
        Rectangle playAgainBtn = { (float)(centerX - 120), (float)(centerY + 30), 240, 40 };
        DrawRectangleRec(playAgainBtn, DARKGREEN);
        DrawText("Play Again", centerX - 60, centerY + 38, 25, RAYWHITE);

        // Draw "Exit" button
        Rectangle exitBtn = { (float)(centerX - 100), (float)(centerY + 80), 200, 40 };
        DrawRectangleRec(exitBtn, GRAY);
        DrawText("Exit", centerX - 25, centerY + 88, 25, RAYWHITE);

        // Handle mouse click on buttons
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            if (CheckCollisionPointRec(mouse, playAgainBtn)) {
                // Reset game state
                collision = 0;
                float minX = ballRadius;
                float maxX = WindowX - ballRadius;
                float randomX = minX + static_cast<float>(rand()) / RAND_MAX * (maxX - minX);
                ballPos.set(randomX, ballRadius + 10.0f);
                ballSpeedY = 0.2f; // Reset to initial speed
                gameOver = false;
            }
            if (CheckCollisionPointRec(mouse, exitBtn)) {
                CloseWindow();
                exit(0);
            }
        }
    }
}

// CODS class definitions
CODS::CODS() : coord{0.0f, 0.0f} {}
CODS::CODS(float xVal, float yVal) : coord{xVal, yVal} {}

void CODS::setX(float xVal) { coord[0] = xVal; }
void CODS::setY(float yVal) { coord[1] = yVal; }
void CODS::set(float xVal, float yVal) { coord[0] = xVal; coord[1] = yVal; }

float CODS::getX() const { return coord[0]; }
float CODS::getY() const { return coord[1]; }

void InitWindowCustom() {
    int rectWidth = 200;
    int rectHeight = 120;
    int rectX = (WindowX - rectWidth) / 2;
    int rectY = (WindowY - rectHeight) / 2;

    while (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
           !IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) &&
           !IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON)) {
        
        BeginDrawing();
        ClearBackground(GRAY);
        DrawRectangle(rectX, rectY, rectWidth, rectHeight, BLACK);
        EndDrawing();
    }
}