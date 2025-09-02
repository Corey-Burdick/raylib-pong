#include <raylib.h>

int playerScore = 0;
int cpuScore = 0;

class Ball{
public:
  float x, y;
  int speed_x, speed_y;
  int radius;

  Ball() {
    radius = 20;
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    speed_x = speed_y = 7;
  }

  void Draw() {
    DrawCircle(x, y, radius, GRUVBOX_FG);
    DrawCircle(x, y, radius / 1.5, GRUVBOX_BG);
    DrawCircle(x, y, radius / 2, GRUVBOX_FG);
  }

  void Update() {
    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
      speed_y *= -1;
    }
    if (x + radius >= GetScreenWidth()) {
      cpuScore += 1;
      Reset(false);
    }
    if (x - radius <= 0) {
      playerScore += 1;
      Reset(true);
    }
  }

  void Reset(bool didPlayerScore) {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    if (didPlayerScore) {
      speed_x = 6;
      speed_y = 6;
    }
    if (!didPlayerScore) {
      speed_x = -6;
      speed_y = -6;
    }
  }

};

class Paddle{
public:
  int x, y;
  int speed = 6;
  int width = 25;
  int height = 120;
  int score = 0;

  void Draw() {
    DrawRectangle(x, y, width, height, GRUVBOX_RED);
    DrawRectangleRoundedLinesEx(Rectangle{x, y, width, height}, 0.4, 10, 3, GRUVBOX_FG);
  }

  void Update() {
    if (IsKeyDown(KEY_UP)) {
      y -= speed;
    } 
    
    if (IsKeyDown(KEY_DOWN)) {
      y += speed;
    }

    if (y <= 0) {
      y = 0;
    }

    if (y >= GetScreenHeight() - height) {
      y = GetScreenHeight() - height;
    }
  }
};

class CpuPaddle: public Paddle{
public:

  void Update(int ball_y) {
    if (y + height/2 > ball_y) {
      y -= speed;
    }
    if (y + height/2 <= ball_y) {
      y += speed;
    }

    if (y >= GetScreenHeight() - height) {
      y = GetScreenHeight() - height;
    }
  }

};
