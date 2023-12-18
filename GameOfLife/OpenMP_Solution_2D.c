#include "GameOfLifeConfig.h"
#include "OpenMP_Solution_2D.h"
#include <omp.h>

void updateSubgrid2D(int grid[ROWS][COLS], int startRow, int endRow)
{
    int i;
    int j;

#pragma omp parallel for private(i, j)
    for (i = startRow; i < endRow; i++)
    {
        for (j = 0; j < COLS; j++)
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
}

void updateGrid2D(int grid[ROWS][COLS])
{
    int rowsPerThread = ROWS / omp_get_max_threads();

#pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        int startRow = threadID * rowsPerThread;
        int endRow = (threadID + 1) * rowsPerThread;

        updateSubgrid2D(grid, startRow, endRow);
    }
}

double startOpenMP2D(int grid[ROWS][COLS])
{
    int index = 0;

    double start_time;
    double end_time;

    int testGrid[ROWS][COLS];
    memcpy(testGrid, grid, sizeof(int) * ROWS * COLS);

    printf("Start Game of Life...");

    omp_set_num_threads(4);

    printf("\n\nStart Game of Life using OpenMP 2D method...");

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

        updateGrid2D(testGrid);

        applyTheChanges(testGrid);
    }

    end_time = omp_get_wtime();

    if (PRINT)
    {
        printGrid(testGrid);
    }

    printf("\nExecution time: %f seconds\n", end_time - start_time);

    return end_time - start_time;
}