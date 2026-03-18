// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2026

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "character.h"
#include "game.h"
char *map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

/* Tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// Tests for load_map
TEST_CASE("A test for load_map") {
    CHECK(0 == 0);
}

TEST_SUITE_END();

/* tests for character.c */
TEST_SUITE_BEGIN("Character tests");
int width=11;
int height=12;
// tests for move_character
TEST_CASE("move_character returns MOVED_INVALID_DIRECTION when not pressing wasd"){

// tests for locate_character

// tests for charge_minotaur

// tests for sees_player

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

// tests for check_win
//defined keepgoing as 0
TEST_CASE("check_win returns YOU_WIN only when player is outside map") {
    // Lab instructions: make sure to set width and height inside the test case.
    width = 11;
    height = 12;
        CHECK(check_win(0, 0) == YOU_WIN);
        CHECK(check_win(height - 1, width - 1) == YOU_WIN);
        CHECK(check_win(2, 3) == KEEP_GOING);
        CHECK(check_win(0, 2) == YOU_WIN);

        CHECK(check_win(-1, 0) == YOU_WIN);
        CHECK(check_win(0, -1) == YOU_WIN);
        CHECK(check_win(height, 0) == YOU_WIN);
        CHECK(check_win(0, width) == YOU_WIN);
        CHECK(check_win(height + 10, width + 10) == YOU_WIN);

}



// test for check_loss
TEST_CASE("check_loss returns YOU_LOSE when player and minotaur share same coord") {
        CHECK(check_loss(0, 0, 0, 0) == YOU_LOSE);
        CHECK(check_loss(2, 3, 2, 3) == YOU_LOSE);
        CHECK(check_loss(-1, 5, -1, 5) == YOU_LOSE);
        CHECK(check_loss(0, 0, 0, 1) == KEEP_GOING);
        CHECK(check_loss(0, 0, 1, 0) == KEEP_GOING);
        CHECK(check_loss(10, -4, 10, -3) == KEEP_GOING);
        CHECK(check_loss(10, -4, 9, -4) == KEEP_GOING);
    }
TEST_SUITE_END();
