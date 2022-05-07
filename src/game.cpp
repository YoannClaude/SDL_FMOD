#include <game.h>


Game::Game()
{

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(
        "SDL_FMOD",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    audioMan = AudioManager::GetInstance();
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


void Game::Loop()
{
    bool running = true;
    Uint64 lastUpdate = SDL_GetPerformanceCounter();
    while(running)
    {
        Uint64 currentUpdate = SDL_GetPerformanceCounter();
        float dt = (currentUpdate - lastUpdate) / 1000000000.0f;
        running = GetEvent();
        Update(dt);
        Draw();
        lastUpdate = currentUpdate;
    }
}

bool Game::GetEvent()
{
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            return false;
        }
    }
    return true;
}

void Game::Update(float dt)
{
    audioMan->Update();
}

void Game::Draw()
{
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}