#include <raylib.h>

const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 600;

int main() {
  SetTargetFPS(60);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Im!");

  while (!WindowShouldClose()) {
    
    // -- Drawing
    BeginDrawing();
    ClearBackground(DARKBLUE);


    EndDrawing();
    // -- EndDrawing
  }

  CloseWindow();
  return 0;
}
