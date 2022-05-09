#ifndef _AUDIO_ENGINE_H
#define _AUDIO_ENGINE_H

#include <iostream>
#include <math.h>
#include <string>
#include <unordered_map>
#include "fmod_studio.hpp"

class FmodManager
{

    public:

        FmodManager();
        ~FmodManager();
        static FmodManager* GetInstance();
        void Update();
        void SetListenerNumber(int number);

        void LoadBank(std::string bankPath, const char* bankName);

        void SetListener3DAttributes(int listener, FMOD_3D_ATTRIBUTES* attributes, FMOD_VECTOR* attenuationPos);
        FMOD_3D_ATTRIBUTES GetListener3DAttributes(int listener);
        void SetEvent3DAttributes(const char* eventName, FMOD_3D_ATTRIBUTES* attributes);
        FMOD_3D_ATTRIBUTES GetEvent3DAttributes(const char* eventName);

        float GetGlobalParameter(const char* parameterName, bool final);
        void SetGlobalParameter(const char* parameterName, float value, bool ignoreSeekSpeed); 
        float GetLocalParameter(const char* eventName, const char* parameterName, bool final);
        void SetLocalParameter(const char* eventName, const char* parameterName, float value, bool ignoreSeekSpeed);

        void LoadBus(std::string busPath, const char* busName);
        void SetBusMute(const char* busName, bool mute);
        bool GetBusMute(const char * busName);
        void SetBusVolume(const char* busName, float volume);
        float GetBusVolume(const char* busName, bool final);

        void LoadVCA(std::string vcaPath, const char* vcaName);
        void SetVCAVolume(const char* vcaName, float volume);
        float GetVCAVolume(const char* vcaName, bool final);

        void LoadEvent(std::string eventPath, const char* eventName);
        void PlayOneShotEvent(const char* eventPath);
        void StartEvent(const char* eventName);
        void StopEvent(const char* eventName, bool fade);
        void SetEventPaused(const char* eventName, bool paused);
        bool GetEventPaused(const char* eventName);
        void SetEventPosition(const char* eventName, int position);
        int GetEventPosition(const char* eventName);
        void SetEventVolume(const char* eventName, float volume);
        float GetEventVolume(const char* eventName, bool final);

    private:

        FMOD::Studio::System* studioSystem = nullptr;

        std::unordered_map<const char*, FMOD::Studio::Bank*> bankList;
        std::unordered_map<const char*, FMOD::Studio::Bus*> busList;
        std::unordered_map<const char*, FMOD::Studio::VCA*> vcaList;
        std::unordered_map<const char*, FMOD::Studio::EventInstance*> eventList;
};

#endif