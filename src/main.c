#define SDL_MAIN_HANDLED
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 48;
const int SCREEN_HEIGHT = 16;
const int PLAYERS_HEIGHT = 4;
const int PLAYER_DISTANCE_FROM_WALL = 2; 

int player1Position = 2;
int player2Position = 2;

int calculatePlayerPosition () {
  int screenHalf = SCREEN_HEIGHT / 2;
  int playerHeightHalf = PLAYERS_HEIGHT / 2;
  return screenHalf - playerHeightHalf;
}

int getPlayerEnd(int playerStart) {
  return playerStart + PLAYERS_HEIGHT;
}

bool isPlayerRow(int currentRow) {
  int player1End = getPlayerEnd(player1Position);
  int player2End = getPlayerEnd(player2Position);
  bool isPlayer1Row = player1Position <= currentRow && player1End >= currentRow;
  bool isPlayer2Row = player2Position <= currentRow && player2End >= currentRow;
  return isPlayer1Row || isPlayer2Row;
}

bool isPlayerColumn(int currentColumn) {
  int startWall = 1;
  int endWall = SCREEN_WIDTH - 2;
  int player1Col = startWall + PLAYER_DISTANCE_FROM_WALL;
  int player2Col = endWall - PLAYER_DISTANCE_FROM_WALL;

  return currentColumn == player1Col || currentColumn == player2Col;
}

bool isPlayerCell(int currentColumn, int currentRow) {
  return isPlayerColumn(currentColumn) && isPlayerRow(currentRow);
}

void clearScreen() {
  system("cls");
}

void update() {
  player1Position = player1Position + 1;;
}

void draw() {
  clearScreen();
  for(int i = 0; i < SCREEN_HEIGHT; i++) { 
    bool isFirstRow = i == 0; 
    bool isLastRow = i == (SCREEN_HEIGHT - 1); 
    for(int j = 0; j < SCREEN_WIDTH; j++) {
      bool isFirstColumn = j == 0;
      bool isLastColumn = j == (SCREEN_WIDTH - 1);
      if(
          isFirstRow    || 
          isLastRow     || 
          isFirstColumn ||
          isLastColumn ||
          isPlayerCell(j, i)
        ) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

// void handleKeyPress(SDL_Event sdlEvent) {
//   switch (sdlEvent.key.keysym.sym)
//   {
//   case SDLK_w:
//     player1Position = player1Position - 1;
//     break;

//   case SDLK_s:
//     player1Position = player1Position + 1;;
//     break;

//   default:
//     break;
//   }
// }

int main() {
  while(true) {
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        // Break out of the loop on quit
        break;
      }
    }
    SDL_Delay(1000);
    update();
    draw();
  }
  return 0;
}


