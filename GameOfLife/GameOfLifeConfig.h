#ifndef GAME_OF_LIFE_CONFIG_H
#define GAME_OF_LIFE_CONFIG_H

// Grid details
#define ROWS 100
#define COLS 100
#define CYCLES 100000

// Cell print
#define ALIVE_PRINT '*'
#define DEAD_PRINT '-'

// Cell details
#define ALIVE 1
#define ALIVEDEAD -2

#define DEAD 0
#define DEADALIVE -1

// Console clearing macro for Windows
#define CLEAR_CONSOLE() system("cls")

// Macros for cell states
#define IS_ALIVE(cell) ((cell) == 1)
#define IS_DEAD(cell)  ((cell) == 0)

#define PRINT 1
#define PRINT_CYCLE 1

#endif
