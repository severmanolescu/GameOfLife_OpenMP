#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "OpenMP_Solution_1D.h"
#include "OpenMP_Solution_2D.h"
#include "GameOfLifeConfig.h"

void setRandomGridState(int grid[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            grid[i][j] = rand() % 2;
        }
    }
}

void printGrid(int grid[ROWS][COLS])
{
    printf("\n");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%c", IS_ALIVE(grid[i][j]) ? ALIVE_PRINT : DEAD_PRINT);
        }
        printf("\n");
    }
}

void applyTheChanges(int grid[ROWS][COLS])
{
    int i;
    int j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (grid[i][j] == DEADALIVE)
            {
                grid[i][j] = 1;
            }
            else if (grid[i][j] == ALIVEDEAD)
            {
                grid[i][j] = 0;
            }
        }
    }
}

int countNeighbors(int grid[ROWS][COLS], int row, int col)
{
    int count = 0;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int neighborRow = row + i;
            int neighborCol = col + j;

            if (neighborRow >= 0 && neighborRow < ROWS &&
                neighborCol >= 0 && neighborCol < COLS &&
                !(i == 0 && j == 0))
            {
                if (grid[neighborRow][neighborCol] == ALIVE || grid[neighborRow][neighborCol] == ALIVEDEAD)
                {
                    count++;
                }
            }
        }
    }

    return count;
}

// -1 -> It is dead but will update to 1

// -2 -> It is alive but will update to 0

void updateGrid(int grid[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            int neighbors = countNeighbors(grid, i, j);

            if (IS_ALIVE(grid[i][j]))
            {
                if (neighbors == 2 || neighbors == 3)
                {
                    grid[i][j] = ALIVE;
                }
                else
                {
                    grid[i][j] = ALIVEDEAD;
                }
            }
            else
            {
                if (neighbors == 3)
                {
                    grid[i][j] = DEADALIVE;
                }
                else
                {
                    grid[i][j] = DEAD;
                }
            }
        }
    }

    applyTheChanges(grid);
}

double startGameOfLife(int grid[ROWS][COLS])
{
    double start_time;
    double end_time;

    int index = 0;

    int copiedGrid[ROWS][COLS];
    memcpy(copiedGrid, grid, sizeof(int) * ROWS * COLS);

    printf("Start Game of Life...");

    fflush(stdout);

    if (PRINT_CYCLE)
    {
        printf("\n");
    }

    start_time = omp_get_wtime();

    for (index = 0; index <= CYCLES; index++)
    {
        if (PRINT_CYCLE)
        {
            printf("\rCycle: %d", index);
        }

        updateGrid(copiedGrid);
    }

    end_time = omp_get_wtime();

    if (PRINT)
    {
        printGrid(copiedGrid);
    }

    printf("\nExecution time: %f seconds\n", end_time - start_time);

    return end_time - start_time;
}

int main()
{
    int grid[ROWS][COLS] = { 0 };

    setRandomGridState(grid);

    double gameOfLifeTime = startGameOfLife(grid);

    double gameOfLifeTime1D = startOpenMP1DD(grid);

    double gameOfLifeTime2D = startOpenMP2D(grid);

    printf("\nOpenMP 1D was: %.2f%% faster", ((gameOfLifeTime - gameOfLifeTime1D) / gameOfLifeTime) * 100);
    printf("\nOpenMP 2D was: %.2f%% faster\n", ((gameOfLifeTime - gameOfLifeTime2D) / gameOfLifeTime) * 100);

    return 0;
}
