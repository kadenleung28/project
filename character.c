// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include "defines.h"
#include "character.h"
#include "colours.h"

extern char * map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int minotaur_y, int minotaur_x) {
    // check if the Minotaur has caught the player
    if (player_y == minotaur_y && player_x == minotaur_x) {
        return CAUGHT_PLAYER;
    }

    // look in each cardinal direction from the Minotaur until hitting a wall or leaving the map
    const char directions[] = {UP, DOWN, LEFT, RIGHT};
    for (int i = 0; i < 4; i++) {
        char dir = directions[i];
        int dy = 0;
        int dx = 0;
        if (dir == UP) dy = -1;
        else if (dir == DOWN) dy = 1;
        else if (dir == LEFT) dx = -1;
        else if (dir == RIGHT) dx = 1;

        int y = minotaur_y + dy;
        int x = minotaur_x + dx;
        while (y >= 0 && y < height && x >= 0 && x < width) {
            char tile = map[y * width + x];
            if (tile == WALL) {
                break;
            }
            if (y == player_y && x == player_x) {
                return dir;
            }
            y += dy;
            x += dx;
        }
    }
    return SEES_NOTHING;
}

int move_character(int * y, int * x, char direction, char character) {
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    if (direction!=UP&&direction!=DOWN&&direction!=LEFT&&direction!=RIGHT) {
        return MOVED_INVALID_DIRECTION;
    }
    // calculate the new coordinates to use on success (store in local variables)
    int newx=*x, newy=*y;
    if (direction == UP) newy--;
    else if (direction == DOWN) newy++;
    else if (direction == LEFT) newx--;
    else if (direction == RIGHT) newx++;

    // check if the new coordinates point to a wall or outside the map
    if (newy <= 0 || newx <= 0 || newy >= height - 1 || newx >= width - 1) {
        return MOVED_WALL;
    }
    int oldIndex = (*y) * width + (*x);
    int newIndex = newy * width + newx;
    if (map[newIndex] == WALL) {
        return MOVED_WALL;
    }

    // at this point, the move is known to be valid (OK direction and not a wall)
    // remove character from the old position and replace with EMPTY
    map[oldIndex] = EMPTY;
    // set character in the new position in map
    map[newIndex] = character;
    // update the x/y coordinate pointers
    *y = newy;
    *x = newx;
    return MOVED_OKAY;
}

int charge_minotaur(int *y, int *x, int player_y, int player_x, char charge_direction) {
    // check for an invalid direction (not LEFT, RIGHT, UP, or DOWN)
    if (charge_direction!=UP&&charge_direction!=DOWN&&charge_direction!=LEFT&&charge_direction!=RIGHT) {
        return MOVED_INVALID_DIRECTION;
    }

    int dy = 0;
    int dx = 0;
    if (charge_direction == UP) dy = -1;
    else if (charge_direction == DOWN) dy = 1;
    else if (charge_direction == LEFT) dx = -1;
    else if (charge_direction == RIGHT) dx = 1;

    // Move up to MINOTAUR_CHARGE_STEP_SIZE tiles each call.
    for (int step = 0; step < MINOTAUR_CHARGE_STEP_SIZE; step++) {
        int target_y = *y + dy;
        int target_x = *x + dx;

        // If the target is outside the map, treat it as a wall we cannot enter.
        if (target_y < 0 || target_y >= height || target_x < 0 || target_x >= width) {
            return MOVED_WALL;
        }

        int target_index = target_y * width + target_x;
        if (map[target_index] == WALL) {
            // Smash through the wall by moving into it.
            map[(*y) * width + (*x)] = EMPTY;
            map[target_index] = MINOTAUR;
            *y = target_y;
            *x = target_x;
            return MOVED_WALL;
        }

        int move_result = move_character(y, x, charge_direction, MINOTAUR);
        if (move_result != MOVED_OKAY) {
            // Should not happen due to checks above, but keep behaviour consistent.
            return move_result;
        }

        // Stop early if the Minotaur caught the player.
        if (*y == player_y && *x == player_x) {
            return MOVED_OKAY;
        }
    }
    return MOVED_OKAY;
