#include <audioManager.h>

static AudioManager* audioManager;
AudioEngine audioEngine = AudioEngine();

const char* bankPath = "fmod/banks/Desktop/";
const char* banks[4] = {
    "Master.strings", "Master", "Music", "Test"
};
const char* events[1] = {
    "test"
};

const char* busses[0];
const char* VCAs[0];

AudioManager* AudioManager::GetInstance()
{
    if (!audioManager)
    {
        audioManager = new AudioManager;
    }
    return audioManager;
}

AudioManager::AudioManager()
{
    audioEngine.Init();
    LoadBanks();
    LoadBusses();
    LoadVCAs();
    LoadEvents();
}

AudioManager::~AudioManager()
{
}

void AudioManager::LoadBanks()
{
    for (long unsigned int i=0; i<sizeof(banks)/sizeof(banks[0]); i++)
    {
        audioEngine.LoadBank(bankPath, banks[i]);
    }
}


void AudioManager::LoadBusses()
{
    for (long unsigned int i=0; i<sizeof(busses)/sizeof(busses[0]); i++)
    {
        audioEngine.LoadBus("bus:/", busses[0]);
    }
}

void AudioManager::LoadVCAs()
{
    for (long unsigned int i=0; i<sizeof(VCAs)/sizeof(VCAs[0]); i++)
    {
        audioEngine.LoadVCA("vca:/", VCAs[0]);
    }
}

void AudioManager::LoadEvents()
{
    for (long unsigned int i=0; i<sizeof(events)/sizeof(events[0]); i++)
    {
        audioEngine.LoadEvent("event:/", events[0]);
    }
}

void AudioManager::Update()
{
    audioEngine.Update();
}

void AudioManager::PlayEvent()
{
    //audioEngine.StartEvent("test");
    //audioEngine.PlayOneShotEvent("event:/test");
}

void AudioManager::StopEvent()
{
    audioEngine.StopEvent("test", false);
}

void AudioManager::PauseEvent(bool _paused)
{
    audioEngine.SetEventPaused("test", _paused);
}