#pragma once
#include <vector>
#include <array>
#include <raylib.h>

class Grid
{
    public:
        static constexpr int Rows = 20;
        static constexpr int Cols = 10;

        Grid();
        ~Grid() = default;

        void Draw() const;

        bool IsCellOutside(int row, int column) const;
        bool IsCellEmpty(int row, int column) const;

        int ClearFullRows();

        std::array<std::array<int, Cols>, Rows> grid{};

    private:
        bool IsRowFull(int row) const;
        void ClearRow(int row);
        void MoveRowDown(int row, int numRows);

        static constexpr int cellSize = 30;

        std::vector<Color> colors;;
};