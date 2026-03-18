// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

#define BUFFER_SIZE 10


extern char *map;
extern int width, height;

/**
 * You should use this function to print out individual characters
 * in the colours used in the demo.
 * @param c
 */
static void printc(char c) {
    switch (c) {
        case WALL:
            change_text_colour(BLUE);
            break;
        case MINOTAUR:
            change_text_colour(MAGENTA);
            break;
        case PLAYER:
            change_text_colour(YELLOW);
            break;
        default:
            change_text_colour(WHITE);
    }
    printf("%c", c);
}

void print_map(void) {
    //print the map and refresh into a new line when appropriate
    for (int i = 0; i < height * width; i++) {
        printc(map[i]);
        if ((i + 1) % width == 0) {
            printf("\n");
        }
    }
    //testing codes for character's coord:
}

void print_revealed_map(int player_y, int player_x) {
    // Only the map within PLAYER_VISION_DISTANCE of the player (including diagonals) should be printed
}

int locate_character(char character, int* character_y, int* character_x) {
    // Attempt to find the character in the map and return a status code indicating
    // if they were present
    //sweeps through the map on columns then move on to rows
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (map[y * width + x] == character) {
                    //update the address with usable values
                    *character_y = y;
                    *character_x = x;
                    return FOUND_CHARACTER;
                }
            }
        }
        return CHARACTER_NOT_FOUND;
}


char *load_map(char *filename, int *map_height, int *map_width) {
    return NULL;
}
