#ifndef GAME_OF_LIFE_CONFIG_H
#define GAME_OF_LIFE_CONFIG_H

// Grid details
#define ROWS 100
#define COLS 100
#define CYCLES 200000

// Cell details
#define ALIVE '*'
#define DEAD '-'

// Console clearing macro for Windows
#define CLEAR_CONSOLE() system("cls")

// Macros for cell states
#define IS_ALIVE(cell) ((cell) == 1)
#define IS_DEAD(cell)  ((cell) == 0)

#define PRINT 0
#define PRINT_CYCLE 1

#endif // GAME_OF_LIFE_CONFIG_H
