#include <raylib.h>
#include <stdio.h>
#include "gruvboxcolors.h"
#include "ponglib.hpp"

using namespace std;

int main() {
  const int screen_width = 1920;
  const int screen_height = 1080;
  printf("Starting the game.\n");
  InitWindow(screen_width, screen_height, "Pong");
  SetTargetFPS(60);
  ToggleFullscreen();
  Ball ball = Ball(); 
  Paddle player = Paddle();
  //Paddle cpu = Paddle(10, screen_height / 2 - 60);
  CpuPaddle cpu = CpuPaddle();
  
  player.x = screen_width - 35;
  player.y = screen_height / 2 - 60;

  cpu.x = 10;
  cpu.y = screen_height / 2 - 60;

  while (!WindowShouldClose()) {
    BeginDrawing();
    
    //Update
    ball.Update();
    player.Update();
    cpu.Update(ball.y);

    //Checking Collision
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{(float)player.x, (float)player.y, (float)player.width, (float)player.height})) {
      ball.speed_x *= -1;
      if (player.moving) {
        ball.speed_x -= player.speed / 4;
      }
    }
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{(float)cpu.x, (float)cpu.y, (float)cpu.width, (float)cpu.height})) {
      ball.speed_x *= -1;
      if (cpu.moving) {
        ball.speed_x += ball.speed_x / 4;
      }
    }
    
    //Drawing

    ClearBackground(GRUVBOX_BG);
    DrawRectangle(0, 0, GetScreenWidth() / 2, GetScreenHeight(), GRUVBOX_BLUE);
    DrawRectangle(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), GRUVBOX_AQUA);
    DrawCircle(0, GetScreenHeight() / 2, GetScreenWidth() / 4, GRUVBOX_DARKGREEN);
    DrawCircle(0, GetScreenHeight() / 2, GetScreenWidth() / 5, GRUVBOX_GREEN);
    DrawRectangle(GetScreenWidth() / 2 - 5, 0, 10, GetScreenHeight(), GRUVBOX_FG);
    DrawCircle(GetScreenWidth(), GetScreenHeight() / 2, GetScreenWidth() / 4, GRUVBOX_DARKGREEN);
    DrawCircle(GetScreenWidth(), GetScreenHeight() / 2, GetScreenWidth() / 5, GRUVBOX_GREEN);
    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenWidth() / 7, GRUVBOX_FG);
    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenWidth() / 8, GRUVBOX_BG);
    DrawText(TextFormat("%i", cpuScore), screen_width / 4, screen_height / 8, 40, GRUVBOX_RED);
    DrawText(TextFormat("%i", playerScore), screen_width / 4 + screen_width / 2, screen_height / 8, 40, GRUVBOX_RED);
    ball.Draw();
    player.Draw();
    cpu.Draw();
               
    EndDrawing();
  }
  ToggleFullscreen();
  CloseWindow();

  return 0;
}
