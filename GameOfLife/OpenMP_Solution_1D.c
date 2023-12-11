#include "GameOfLifeConfig.h"
#include <omp.h>

void updateGrid1D(int grid[ROWS][COLS])
{
    int newGrid[ROWS][COLS] = { 0 };
    int i, j;

#pragma omp parallel for private(j)
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            int neighbors = countNeighbors(grid, i, j);

            if (IS_ALIVE(grid[i][j]))
            {
                newGrid[i][j] = (neighbors < 2 || neighbors > 3) ? 0 : 1;
            }
            else
            {
                newGrid[i][j] = (neighbors == 3) ? 1 : 0;
            }
        }
    }

#pragma omp parallel for private(j)
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            grid[i][j] = newGrid[i][j];
        }
    }
}

double startOpenMP1D()
{
    double start_time;
    double end_time;

    int index = 0;
    int grid[ROWS][COLS] = { 0 };

    setRandomGridState(grid);

    omp_set_num_threads(ROWS);

    printf("\n\nStart Game of Life using OpenMP 1D method...");

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

        updateGrid1D(grid);
    }

    end_time = omp_get_wtime();

    if (PRINT)
    {
        printGrid(grid);
    }

    printf("\nExecution time: %f seconds\n", end_time - start_time);

    return end_time - start_time;
}
