#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "gba.h"
#include "events.h"
#include "images/welcomePage.h"
#include "images/playerDesign.h"
#include "images/enemyDesign.h"
#include "images/winPage.h"
#include "images/lossPage.h"

/* TODO: */
// Add any additional states you need for your app. You are not required to use
// these specific provided states.
enum gba_state
{
  START,
  PLAY,
  RESTART,
  RESET,
  WIN,
  LOSE,
};

// Constants
Player player = {75, 15, 15, 15, 0};
Enemies enemy1 = {30, 50, 15, 15, 0};
Enemies enemy2 = {50, 100, 15, 15, 0};
Enemies enemy3 = {100, 150, 15, 15, 0};
Goal goal = {40, 200, 40, 80};

int main(void)
{
  // Manipulate REG_DISPCNT here to set Mode 3.
  REG_DISPCNT = MODE3 | BG2_ENABLE;

  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  enum gba_state state = START;

  int timer = 0;

  while (1)
  {
    currentButtons = BUTTONS;
    waitForVBlank();

    // Update timer
    if (state == PLAY)
    {
      timer--;
      if (timer <= 0)
      {
        state = LOSE;
      }
    }

    // Handle different states
    switch (state)
    {
    case START:
      // Handle start state
      drawFullScreenImageDMA(welcome_page);
      if (KEY_DOWN(BUTTON_START, currentButtons))
      {
        state = PLAY;
        timer = vBlankCounter + (25 * 60); // Set timer to 25 seconds (25 * 60 frames)
      }
      break;

    case PLAY:
      fillScreenDMA(COLOR(161 / 8, 161 / 8, 161 / 8));
      if (KEY_DOWN(BUTTON_DOWN, BUTTONS) && (player.row < 140))
      {
        player.row++;
      }
      if (KEY_DOWN(BUTTON_UP, BUTTONS) && (player.row > 10))
      {
        player.row--;
      }
      if (KEY_DOWN(BUTTON_LEFT, BUTTONS) && (player.col > 0))
      {
        player.col--;
      }
      if (KEY_DOWN(BUTTON_RIGHT, BUTTONS) && (player.col < 230))
      {
        player.col++;
      }

      drawImageDMA(enemy1.row, enemy1.col, enemy1.width, enemy1.height, enemyDesign);
      drawImageDMA(enemy2.row, enemy2.col, enemy2.width, enemy2.height, enemyDesign);
      drawImageDMA(enemy3.row, enemy3.col, enemy3.width, enemy3.height, enemyDesign);

      drawRectDMA(0, 0, 40, 160, CYAN);
      drawRectDMA(goal.row, goal.col, goal.width, goal.height, GREEN);
      drawImageDMA(player.row, player.col, player.width, player.height, playerDesign);

      // Draw timer at the bottom right corner
      char buffer[10];
      snprintf(buffer, sizeof(buffer), "Timer: %d", timer / 60); // Convert frames back to seconds
      drawString(150, 180, buffer, WHITE);               // Bottom right corner

      if (KEY_DOWN(BUTTON_SELECT, BUTTONS))
      {
        state = RESET;
      }

      if (checkCollision(player, enemy1) || checkCollision(player, enemy2) || checkCollision(player, enemy3))
      {
        state = RESTART;
      }

      if (checkGoalCollision(player, goal))
      {
        state = WIN;
      }

      if (enemy1.row <= 10)
      {
        enemy1.state = 0; // Change direction when enemy reaches top
      }
      else if (enemy1.row >= 140)
      {
        enemy1.state = 1; // Change direction when enemy reaches bottom
      }

      if (enemy1.state)
      {
        enemy1.row -= 2; // Move up
      }
      else
      {
        enemy1.row += 2; // Move down
      }

      // Similar modifications for enemy2 and enemy3
      if (enemy2.row <= 10)
      {
        enemy2.state = 0; // Change direction when enemy reaches top
      }
      else if (enemy2.row >= 140)
      {
        enemy2.state = 1; // Change direction when enemy reaches bottom
      }

      if (enemy2.state)
      {
        enemy2.row -= 3; // Move up
      }
      else
      {
        enemy2.row += 3; // Move down
      }

      if (enemy3.row <= 10)
      {
        enemy3.state = 0; // Change direction when enemy reaches top
      }
      else if (enemy3.row >= 140)
      {
        enemy3.state = 1; // Change direction when enemy reaches bottom
      }

      if (enemy3.state)
      {
        enemy3.row -= 2; // Move up
      }
      else
      {
        enemy3.row += 2; // Move down
      }
      break; // This is the missing closing bracket for case PLAY

    case RESTART:
      player.col = 15;
      player.row = 75;
      state = PLAY;
      break;

    case RESET:
      player.col = 15;
      player.row = 75;
      state = START;
      vBlankCounter = 0;
      timer = vBlankCounter + (25 * 60);
      break;

    case WIN:
      currentButtons = BUTTONS;
      drawFullScreenImageDMA(winPage);

      waitForVBlank();

      if (KEY_DOWN(BUTTON_START, currentButtons))
      {
        state = RESET;
      }
      if (KEY_DOWN(BUTTON_SELECT, BUTTONS))
      {
        state = RESET;
      }
      break;

    case LOSE:
      currentButtons = BUTTONS;
      waitForVBlank();
      drawFullScreenImageDMA(lossPage);

      if (KEY_DOWN(BUTTON_START, currentButtons))
      {
        state = RESET;
      }
      if (KEY_DOWN(BUTTON_SELECT, BUTTONS))
      {
        state = RESET;
      }

      break;
    }

    previousButtons = currentButtons;
  }

  UNUSED(previousButtons);

  return 0;
}
