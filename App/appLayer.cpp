#include <random>
#include "appLayer.hpp"

Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    m_font = LoadFontEx("Fonts/monogram.ttf", 64, 0, 0);    
}

Game::Game(const std::string& font, const int& size)
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
    m_font = LoadFontEx(font.c_str(), size, nullptr, 0);    
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, blocks.size() - 1);

    size_t randomIndex = dist(rng);
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        Reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0, 1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    currentBlock.Rotate();
    if(IsBlockOutside() || BlockFits() == false)
    {
        currentBlock.UndoRotation();
    }
    else{
        PlaySound(rotateSound);
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    default:
        break;
    }

    score += moveDownPoints;
}

bool Game::EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void Game::gameUpdate() 
{
    UpdateMusicStream(music);
    if (!paused)
    {        
        HandleInput();
        if (EventTriggered(gameSpeed))
        {
            MoveBlockDown();
        }
    }

    ClearBackground(darkBlue);        
    DrawTextEx(m_font, "Sorce", {365, 15},  38, 2, WHITE);
    DrawTextEx(m_font, "Next",  {370, 175}, 38, 2, WHITE);

    if(gameOver)
    {
        DrawTextEx(m_font, "GAME OVER",  {320, 550}, 38, 2, WHITE); 
    }
    DrawRectangleRounded({320,  55, 170,  60}, 0.3, 6, lightBlue);

    sprintf(scoreText, "%d", score);
    Vector2 textSize = MeasureTextEx(m_font, scoreText, 38, 2);

    DrawTextEx(m_font, scoreText, {320 + (170 - textSize.x)/2, 65},  38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mouse, muteButton))
        {
            muted = !muted;
            SetMusicVolume(music, muted ? 0.0f : 1.0f);
        }

        if (CheckCollisionPointRec(mouse, pauseButton))
        {
            paused = !paused;
        }
    }

    // TODO: Mute all sound not just the music
    DrawRectangleRounded(muteButton, 0.3f, 6, lightBlue);
    DrawTextEx(
        m_font,
        muted ? "UNMUTE" : "MUTE",
        {muteButton.x + 25, muteButton.y + 8},
        28,
        2,
        WHITE
    );

    DrawRectangleRounded(pauseButton, 0.3f, 6, lightBlue);
    DrawTextEx(
        m_font,
        paused ? "RESUME" : "PAUSE",
        {pauseButton.x + 25, pauseButton.y + 8},
        28,
        2,
        WHITE
    );
    
    Draw();
}