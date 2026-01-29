#include <iostream>

#include "grid.hpp"
#include "colors.hpp"

Grid::Grid() : colors(GetCellColors()) {}

void Grid::Draw() const
{
    for (int row = 0; row < Rows; ++row)
    {
        for (int col = 0; col < Cols; ++col)
        {
            int value = grid[row][col];
            DrawRectangle(col * cellSize+11, row * cellSize+11, cellSize-1, cellSize-1, colors[value]);
        }
    }
}

bool Grid::IsCellOutside(int row, int column) const
{
    return row < 0 || row >= Rows || column < 0 || column >= Cols;
}

bool Grid::IsCellEmpty(int row, int column) const
{
    return grid[row][column] == 0;
}

bool Grid::IsRowFull(int row) const
{
    for (int cell : grid[row])
    {
        if (cell == 0)
            return false;
    }
    return true;
}

void Grid::ClearRow(int row)
{
    grid[row].fill(0);
}

void Grid::MoveRowDown(int row, int offset)
{
    grid[row + offset] = grid[row];
    grid[row].fill(0);
}

int Grid::ClearFullRows()
{
    int cleared = 0;

    for (int row = Rows - 1; row >= 0; --row)
    {
        if (IsRowFull(row))
        {
            ClearRow(row);
            ++cleared;
        }
        else if (cleared > 0)
        {
            MoveRowDown(row, cleared);
        }
    }
    return cleared;
}