#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <fmodManager.h>

class Game
{
    public:
        Game();
        ~Game();
        void Loop();

    private:

        SDL_Window *window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Event event;
        FmodManager* fmodMan = nullptr;

        bool running = true;
        Uint64 lastUpdate = SDL_GetPerformanceCounter();
        Uint64 currentUpdate = SDL_GetPerformanceCounter();
        double dt = currentUpdate - lastUpdate / (float)SDL_GetPerformanceFrequency();

        bool GetEvent();
        void Update(double dt);
        void Draw();
};


#endif