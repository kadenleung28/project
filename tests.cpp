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
TEST_CASE("move_character returns MOVED_INVALID_DIRECTION for invalid direction") {
    set_test_map({
        "WWWWW",
        "W M W",
        "W   W",
        "W   W",
        "WWWWW",
    });

    int y = 1, x = 2;
    CHECK(move_character(&y, &x, 'x', MINOTAUR) == MOVED_INVALID_DIRECTION);
    CHECK(y == 1);
    CHECK(x == 2);
    CHECK(map[1 * width + 2] == MINOTAUR);
}

TEST_CASE("move_character returns MOVED_WALL when walking into wall") {
    set_test_map({
        "WWWWW",
        "W M W",
        "W   W",
        "W   W",
        "WWWWW",
    });

    int y = 1, x = 2;
    CHECK(move_character(&y, &x, UP, MINOTAUR) == MOVED_WALL);
    CHECK(y == 1);
    CHECK(x == 2);
    CHECK(map[1 * width + 2] == MINOTAUR);
}

TEST_CASE("move_character moves and updates map") {
    set_test_map({
        "WWWWW",
        "W M W",
        "W   W",
        "W   W",
        "WWWWW",
    });

    int y = 1, x = 2;
    CHECK(move_character(&y, &x, DOWN, MINOTAUR) == MOVED_OKAY);
    CHECK(y == 2);
    CHECK(x == 2);
    CHECK(map[1 * width + 2] == EMPTY);
    CHECK(map[2 * width + 2] == MINOTAUR);
}

TEST_CASE("locate_character finds character and returns status") {
    set_test_map({
        "WWWWW",
        "W P W",
        "W   W",
        "W  MW",
        "WWWWW",
    });

    int py = -1, px = -1;
    CHECK(locate_character(PLAYER, &py, &px) == FOUND_CHARACTER);
    CHECK(py == 1);
    CHECK(px == 2);

    int my = -1, mx = -1;
    CHECK(locate_character(MINOTAUR, &my, &mx) == FOUND_CHARACTER);
    CHECK(my == 3);
    CHECK(mx == 3);

    int zy = -1, zx = -1;
    CHECK(locate_character('Z', &zy, &zx) == CHARACTER_NOT_FOUND);
}

TEST_CASE("sees_player returns CAUGHT_PLAYER when on same tile") {
    set_test_map({
        "WWW",
        "WMW",
        "WWW",
    });

    CHECK(sees_player(1, 1, 1, 1) == CAUGHT_PLAYER);
}

TEST_CASE("sees_player returns correct direction when unobstructed") {
    set_test_map({
        "WWWWW",
        "W   W",
        "W M W",
        "W   W",
        "WWWWW",
    });

    CHECK(sees_player(1, 2, 2, 2) == UP);
    CHECK(sees_player(3, 2, 2, 2) == DOWN);
    CHECK(sees_player(2, 1, 2, 2) == LEFT);
    CHECK(sees_player(2, 3, 2, 2) == RIGHT);
}

TEST_CASE("sees_player returns SEES_NOTHING when blocked or not aligned") {
    set_test_map({
        "WWWWW",
        "W W W",
        "W M W",
        "W   W",
        "WWWWW",
    });

    CHECK(sees_player(1, 2, 2, 2) == SEES_NOTHING); // blocked by wall
    CHECK(sees_player(1, 1, 2, 2) == SEES_NOTHING); // diagonal (not aligned)
}

TEST_CASE("charge_minotaur returns MOVED_INVALID_DIRECTION for invalid direction") {
    set_test_map({
        "WWWWW",
        "W M W",
        "W   W",
        "W   W",
        "WWWWW",
    });

    int y = 1, x = 2;
    CHECK(charge_minotaur(&y, &x, 0, 0, 'x') == MOVED_INVALID_DIRECTION);
    CHECK(y == 1);
    CHECK(x == 2);
}

TEST_CASE("charge_minotaur moves two tiles when clear") {
    set_test_map({
        "WWWWW",
        "W M W",
        "W   W",
        "W   W",
        "WWWWW",
    });

    int y = 1, x = 2;
    CHECK(charge_minotaur(&y, &x, 9, 9, DOWN) == MOVED_OKAY);
    CHECK(y == 3);
    CHECK(x == 2);

    CHECK(map[1 * width + 2] == EMPTY);
    CHECK(map[2 * width + 2] == EMPTY);
    CHECK(map[3 * width + 2] == MINOTAUR);
}

TEST_CASE("charge_minotaur smashes wall and returns MOVED_WALL") {
    set_test_map({
        "WWWWW",
        "W MWW",
        "W   W",
        "W   W",
        "WWWWW",
    });

    int y = 1, x = 2;
    CHECK(charge_minotaur(&y, &x, 9, 9, RIGHT) == MOVED_WALL);
    CHECK(y == 1);
    CHECK(x == 3);

    CHECK(map[1 * width + 2] == EMPTY);
    CHECK(map[1 * width + 3] == MINOTAUR);
}

TEST_CASE("charge_minotaur stops early when it catches player") {
    set_test_map({
        "WWWWW",
        "W M W",
        "W P W",
        "W   W",
        "WWWWW",
    });

    int y = 1, x = 2;
    CHECK(charge_minotaur(&y, &x, 2, 2, DOWN) == MOVED_OKAY);
    CHECK(y == 2);
    CHECK(x == 2);

    CHECK(map[2 * width + 2] == MINOTAUR);
    CHECK(map[3 * width + 2] == EMPTY); // should not take the second step
}

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Game tests");

TEST_CASE("check_win returns YOU_WIN only when player is outside map") {
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

TEST_CASE("check_loss returns YOU_LOSE when player and minotaur share same coord") {
    CHECK(check_loss(0, 0, 0, 0) == YOU_LOSE);
    CHECK(check_loss(2, 3, 2, 3) == YOU_LOSE);
    CHECK(check_loss(-1, 5, -1, 5) == YOU_LOSE);

    CHECK(check_loss(0, 0, 0, 1) == KEEP_GOING);
    CHECK(check_loss(0, 0, 1, 0) == KEEP_GOING);
    CHECK(check_loss(10, -4, 10, -3) == KEEP_GOING);
    CHECK(check_loss(10, -4, 9, -4) == KEEP_GOING);
}

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
