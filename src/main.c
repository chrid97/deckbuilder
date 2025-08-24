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
typedef enum { DRAW, ACTION } Phase;
enum { MAX_HAND_SIZE = 7 };
typedef enum { PLAYER, ENEMY, CARD, HEALTH_BAR } EntityType;
// testing NOT_A_CARD instead of union
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
  // card should have a picked up mode and a static mode. When in static mode
  // the placement in hand is decided by its position

  // card specific maybe need a union for this so only entities that are cards
  // can even have this property
  CardLocation card_location;
  char *card_name;
} Entity;

typedef struct {
  int id;
  int instance_id;
  int cost;
} Card;

// deck
// array of pointers pointing to the respective cards in entity array
// hand
// discard

Entity deck[100] = {0};

int main(void) {
  // InitWindow(960, 540, "deckbuilder");
  InitWindow(800, 450, "deckbuilder");
  SetTargetFPS(60);

  float virtual_width = 850;
  float virtual_height = 450;

  Entity entities[MAX_ENTITIES] = {0};
  int entity_count = 0;

  int hand[MAX_HAND_SIZE] = {0};
  int cards_in_hand = 0;

  int library[100] = {0};
  int cards_in_library = 0;

  int discard[100] = {0};
  int cards_in_discard = 0;

  for (int i = 0; i < 10; i++) {
    Entity card = {.width = CARD_WIDTH,
                   .height = CARD_HEIGHT,
                   .color = WHITE,
                   .type = CARD,
                   .card_location = DECK,
                   .card_name = "Attack"};
    entities[entity_count] = card;
    library[cards_in_library++] = entity_count;
    entity_count++;
  }

  Entity enemy = {
      .health = 100,
      .color = RED,
      .type = CARD,
  };

  entities[entity_count++] = enemy;

  Entity enemy_health_bar = {
      .x = 50,
      .y = 50,
      .height = 10,
      .width = 100,
      .color = GRAY,
      .type = HEALTH_BAR,
  };
  entities[entity_count++] = enemy_health_bar;

  Phase current_phase = DRAW;

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

    if (current_phase == DRAW) {
      current_phase = ACTION;
      for (int i = 0; i < 5; i++) {
        int entity_index = library[i];
        hand[cards_in_hand++] = entity_index;
        entities[entity_index].card_location = HAND;
      }
    }

    for (int i = 0; i < cards_in_hand; i++) {
      Entity *card = &entities[hand[i]];
      card->x = i * (CARD_WIDTH + 10);
      card->y = GetScreenHeight() - CARD_HEIGHT - 20;
    }

    /// Draw ///
    BeginDrawing();
    ClearBackground(BLACK);

    DrawEllipse(600, 150, 100, 50, GREEN);
    // player circle
    DrawEllipse(200, 300, 100, 50, GREEN);

    for (int i = 0; i < entity_count; i++) {
      Entity entity = entities[i];
      DrawRectangle(entity.x, entity.y, entity.width * scale,
                    entity.height * scale, entity.color);

      // I think I can remove this. This doesn't have to be a conditional
      if (entity.type == HEALTH_BAR) {
        DrawText("ENEMY", entity.x, entity.y - 20, 15, WHITE);
        DrawText("HP", entity.x - 20, entity.y, 10 * scale, ORANGE);
        DrawRectangle(entity.x, entity.y, enemy.health * scale,
                      entity.height * scale, RED);
      }
    }

    // Draw library
    // DrawRectangleLines((width - CARD_WIDTH) * scale,
    //                    height - (CARD_HEIGHT * scale), CARD_WIDTH * scale,
    //                    CARD_HEIGHT * scale, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
