#include "GameOfLifeConfig.h"
#include <omp.h>

int cycleGrid[ROWS][COLS];

void updateSubgrid1D(int grid[ROWS][COLS], int row)
{
    int newGrid[COLS] = { 0 };

    int i;

#pragma omp parallel for private(i)
    for (i = 0; i < COLS; i++)
    {
        int neighbors = countNeighbors(grid, row, i);

        if (IS_ALIVE(grid[row][i]))
        {
            newGrid[i] = (neighbors < 2 || neighbors > 3) ? 0 : 1;
        }
        else
        {
            newGrid[i] = (neighbors == 3) ? 1 : 0;
        }
    }

#pragma omp parallel for private(i)
    for (i = 0; i < COLS; i++)
    {
        cycleGrid[row][i] = newGrid[i];
    }
}

void updateGrid1D(int grid[ROWS][COLS])
{
#pragma omp parallel
    {
        int threadID = omp_get_thread_num();

        updateSubgrid1D(grid, threadID);
    }
}

double startOpenMP1DD(int grid[ROWS][COLS])
{
    int index = 0;
    int indexRows = 0;

    double start_time;
    double end_time;

    int testGrid[ROWS][COLS];
    memcpy(testGrid, grid, sizeof(int) * ROWS * COLS);

    omp_set_num_threads(ROWS);

    printf("\n\nStart Game of Life using OpenMP 1D method...");

    if (PRINT_CYCLE)
    {
        printf("\n");
    }

    start_time = omp_get_wtime();

    for (index = 0; index < CYCLES; index++)
    {
        if (PRINT_CYCLE)
        {
            printf("\rCycle: %d", index + 1);
        }

        updateGrid1D(testGrid);

        copyGrid(testGrid, cycleGrid);
    }

    end_time = omp_get_wtime();

    if (PRINT)
    {
        printGrid(testGrid);
    }

    printf("\nExecution time: %f seconds\n", end_time - start_time);

    return end_time - start_time;
}
