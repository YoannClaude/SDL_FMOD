#ifndef _GAME_H
#define _GAME_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <audioManager.h>

class Game
{
    public:
        Game();
        ~Game();
        bool Load();
        void Loop();

    private:

        SDL_Window *window = nullptr;
        AudioManager* audioMan = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Event event;
        int windowWidth = 640;
        int windowHeight = 480;
        bool GetEvent();
        void Update(float dt);
        void Draw();
};


#endif