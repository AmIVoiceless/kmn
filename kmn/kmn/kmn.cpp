#include "raylib.h"
#include <cstdlib>
#include <ctime>

enum Choice { ROCK, PAPER, SCISSORS, NONE };

const char* DetermineWinner(Choice p1, Choice p2, int& p1Wins, int& p2Wins, int& draws) {
    if (p1 == p2) {
        draws++;
        return "Draw!";
    }
    if ((p1 == ROCK && p2 == SCISSORS) ||
        (p1 == PAPER && p2 == ROCK) ||
        (p1 == SCISSORS && p2 == PAPER)) {
        p1Wins++;
        return "Player 1 Wins!";
    }
    p2Wins++;
    return "Player 2 Wins!";
}

const char* ChoiceToString(Choice choice) {
    switch (choice) {
    case ROCK: return "Rock";
    case PAPER: return "Paper";
    case SCISSORS: return "Scissors";
    default: return "-";
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Rock Paper Scissors - Two Players");
    SetTargetFPS(60);
    InitAudioDevice();

    Sound selectSound = LoadSound("resources/select.wav");
    Sound winSound = LoadSound("resources/win.wav");
    Sound drawSound = LoadSound("resources/draw.wav");

    Choice p1Choice = NONE;
    Choice p2Choice = NONE;
    const char* resultText = "";
    bool gameStarted = false;

    int p1Wins = 0;
    int p2Wins = 0;
    int draws = 0;

    while (!WindowShouldClose()) {
        if (!gameStarted) {
            if (IsKeyPressed(KEY_R)) { p1Choice = ROCK; PlaySound(selectSound); }
            if (IsKeyPressed(KEY_P)) { p1Choice = PAPER; PlaySound(selectSound); }
            if (IsKeyPressed(KEY_S)) { p1Choice = SCISSORS; PlaySound(selectSound); }

            if (IsKeyPressed(KEY_J)) { p2Choice = ROCK; PlaySound(selectSound); }
            if (IsKeyPressed(KEY_K)) { p2Choice = PAPER; PlaySound(selectSound); }
            if (IsKeyPressed(KEY_L)) { p2Choice = SCISSORS; PlaySound(selectSound); }

            if (p1Choice != NONE && p2Choice != NONE) {
                resultText = DetermineWinner(p1Choice, p2Choice, p1Wins, p2Wins, draws);
                if (resultText == "Draw!") PlaySound(drawSound);
                else PlaySound(winSound);
                gameStarted = true;
            }
        }
        else {
            if (IsKeyPressed(KEY_SPACE)) {
                p1Choice = NONE;
                p2Choice = NONE;
                resultText = "";
                gameStarted = false;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Rock Paper Scissors - 2 Players", screenWidth / 2 - MeasureText("Rock Paper Scissors - 2 Players", 30) / 2, 40, 30, DARKGRAY);

        DrawText(TextFormat("Score: Player 1 = %d | Player 2 = %d | Draws = %d", p1Wins, p2Wins, draws), 100, 100, 20, DARKGRAY);

        if (!gameStarted) {
            DrawText("Player 1: R - Rock, P - Paper, S - Scissors", 100, 150, 20, BLUE);
            DrawText("Player 2: J - Rock, K - Paper, L - Scissors", 100, 180, 20, RED);
            DrawText("Waiting for both players to choose...", 100, 230, 20, GRAY);
        }
        else {
            DrawText(TextFormat("Player 1 chose: %s", ChoiceToString(p1Choice)), 100, 300, 20, BLUE);
            DrawText(TextFormat("Player 2 chose: %s", ChoiceToString(p2Choice)), 100, 330, 20, RED);
            DrawText(resultText, screenWidth / 2 - MeasureText(resultText, 30) / 2, 400, 30, DARKGREEN);
            DrawText("Press SPACE to play again", screenWidth / 2 - MeasureText("Press SPACE to play again", 20) / 2, 460, 20, GRAY);
        }

        EndDrawing();
    }

    UnloadSound(selectSound);
    UnloadSound(winSound);
    UnloadSound(drawSound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
