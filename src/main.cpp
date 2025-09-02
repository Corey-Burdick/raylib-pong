#include <raylib.h>
#include <stdio.h>
#include "gruvboxcolors.h"
#include "ponglib.hpp"

using namespace std;

int main() {
  const int screen_width = 1280;
  const int screen_height = 800;
  printf("Starting the game.\n");
  InitWindow(screen_width, screen_height, "Pong");
  SetTargetFPS(60);
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
      ball.speed_x -= 1;
    }

    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{(float)cpu.x, (float)cpu.y, (float)cpu.width, (float)cpu.height})) {
      ball.speed_x *= -1;
      ball.speed_x += 1;
    }
    
    //Drawing

    ClearBackground(GRUVBOX_BG);
    DrawText(TextFormat("%i", cpuScore), screen_width / 4, screen_height / 8, 40, GRUVBOX_RED);
    DrawText(TextFormat("%i", playerScore), screen_width / 4 + screen_width / 2, screen_height / 8, 40, GRUVBOX_RED);
    DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, GRUVBOX_FG);
    ball.Draw();
    player.Draw();
    cpu.Draw();
               
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
