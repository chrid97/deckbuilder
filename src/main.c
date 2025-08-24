#include "raylib.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/_types/_u_int8_t.h>

#define CARD_WIDTH 100
#define CARD_HEIGHT 150
#define MAX_ENTITIES 1000
typedef enum { PLAYER, ENEMY, CARD } EntityType;
typedef enum { DRAW, ACTION } Phase;
typedef enum { HAND, DISCARD, DECK } CardLocation;

typedef struct {
  float x;
  float y;
  float dx;
  float dy;
  float width;
  float height;
  Color color;
  int health;
  EntityType type;

  // Card stuff
  CardLocation card_location;
  char *card_name;
} Entity;

typedef struct {
  int id;
  int instance_id;
  int cost;
} Card;

Entity deck[100] = {0};

int main(void) {
  // InitWindow(960, 540, "deckbuilder");
  InitWindow(800, 450, "deckbuilder");
  SetTargetFPS(60);

  float virtual_width = 850;
  float virtual_height = 450;

  Entity entities[MAX_ENTITIES] = {0};
  int entity_count = 0;

  while (!WindowShouldClose()) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();
    float delta = GetFrameTime();
    float scale_x = (float)width / virtual_width;
    float scale_y = (float)height / virtual_height;
    float scale = (scale_x < scale_y) ? scale_x : scale_y;

    /// Input ///

    /// Update ///
    for (int i = 0; i < entity_count; i++) {
      Entity *entity = &entities[i];
    }

    /// Draw ///
    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < entity_count; i++) {
      Entity entity = entities[i];
      DrawRectangle(entity.x, entity.y, entity.width * scale,
                    entity.height * scale, entity.color);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
