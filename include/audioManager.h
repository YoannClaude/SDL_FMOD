#ifndef _AUDIO_MAN_H
#define _AUDIO_MAN_H

#include <audioEngine.h>
#include <string.h>

class AudioManager
{
    public:
        static AudioManager* GetInstance();
        ~AudioManager();
        void Update();
        void PlayEvent();
        void StopEvent();
        void PauseEvent(bool paused);
    
    private:
        AudioManager();
        void LoadBanks();
        void LoadBusses();
        void LoadVCAs();
        void LoadEvents();
};


#endif