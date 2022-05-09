#include <game.h>

Game::Game()
{
    //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(
        "SDL_FMOD",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //Initialize Fmod
    fmodMan = FmodManager::GetInstance();
}

Game::~Game()
{
    //Release SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //Relase Fmod
    delete fmodMan;
}


void Game::Loop()
{
    while(running)
    {
        //Get FPS
        currentUpdate = SDL_GetPerformanceCounter();

        //Get Input
        running = GetEvent();

        Update(dt);
        Draw();

        //Set FPS
        lastUpdate = SDL_GetPerformanceCounter();
        dt =  currentUpdate - lastUpdate / (float)SDL_GetPerformanceFrequency();
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

void Game::Update(double dt)
{
    fmodMan->Update();
}

void Game::Draw()
{
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}