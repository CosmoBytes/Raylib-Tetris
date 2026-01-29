#pragma once
#include <raylib.h>
#include "Renderer/grid.hpp"
#include "Renderer/blockType.hpp"
#include "Renderer/colors.hpp"

class Game
{
    public:
        Game();
        Game(const std::string& font, const int& size);
        ~Game();
        void gameUpdate();

    private:
        void Draw();
        void HandleInput();
        void MoveBlockDown();
        bool gameOver;
        int score;
        Music music;

        void MoveBlockLeft();
        void MoveBlockRight();
        Block GetRandomBlock();
        std::vector<Block> GetAllBlocks();
        bool IsBlockOutside();
        void RotateBlock();
        void LockBlock();
        bool BlockFits();
        void Reset();
        void UpdateScore(int linesCleared, int moveDownPoints);
        Grid grid;
        std::vector<Block> blocks;
        Block currentBlock;
        Block nextBlock;
        Sound rotateSound;
        Sound clearSound;

        bool paused = false;
        bool muted  = false;
        Rectangle muteButton  = {320, 410, 170, 45};
        Rectangle pauseButton = {320, 465, 170, 45};

        double gameSpeed = 0.2;
        double lastUpdateTime = 0;
        bool EventTriggered(double interval);
        char scoreText[10];
        Font m_font;    
};