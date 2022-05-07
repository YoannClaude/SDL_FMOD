#include <audioEngine.h>

AudioEngine::AudioEngine(){}

AudioEngine::~AudioEngine()
{
    auto _result = studioSystem->release();
    if (_result == FMOD_OK) {
		std::cout<<"FMOD released";
	}
}

void AudioEngine::Update()
{
    auto _result = studioSystem->update();
    if (_result != FMOD_OK) {
		std::cout<<"FMOD didn't update properly";
	}
}

void AudioEngine::Init()
{
    auto _result = FMOD::Studio::System::create(&studioSystem, FMOD_VERSION);
	if (_result != FMOD_OK) {
		std::cout<<"couldn't create FMOD SYSTEM";
	}
    _result = studioSystem->initialize(1200, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);
    if (_result == FMOD_OK && studioSystem->isValid()) {
		std::cout<<"FMOD initialized"<<std::endl;
	}
    else
    {
        std::cout<<"couldn't initialize FMOD"<<std::endl;
    }
}

void AudioEngine::LoadBank(std::string _path, const char* _name)
{
    std::string _bankPath = _path + _name + ".bank";
    FMOD::Studio::Bank *_bank;
    auto _result = studioSystem->loadBankFile(_bankPath.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &_bank);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't load bank "<< _name;
        return;
    }
    if (_bank) 
    {
        bankList.emplace(_name, _bank);
    }
}

void AudioEngine::LoadBus(std::string _path, const char* _name)
{
    std::string _busPath = _path + _name;
    FMOD::Studio::Bus *_bus;
    auto _result = studioSystem->getBus(_busPath.c_str(), &_bus);
    if (_result != FMOD_OK)
    {
        printf("couldn't find bus %s\n", _name);
        return;
    }
    if (_bus) 
	{
		busList.emplace(_name, _bus);
	}
}

void AudioEngine::LoadVCA(std::string _path, const char* _name)
{
    std::string _vcaPath = _path + _name;
    FMOD::Studio::VCA *_vca;
    auto _result = studioSystem->getVCA(_vcaPath.c_str(), &_vca);
    if (_result != FMOD_OK)
    {
        printf("couldn't find VCA %s\n", _name);
        return;
    }
    if (_vca) 
	{
		vcaList.emplace(_name, _vca);
	}
}

void AudioEngine::LoadEvent(std::string _path, const char* _name)
{
    std::string _eventPath = _path + _name;
    FMOD::Studio::EventInstance *_event;
    FMOD::Studio::EventDescription *_eventDescription = nullptr;
    auto _result = studioSystem->getEvent(_eventPath.c_str(), &_eventDescription);
    if (_result != FMOD_OK) {
        printf("couldn't find event %s\n", _name);
        return;
    }
    _result = _eventDescription->createInstance(&_event);
    if (_result != FMOD_OK)
    {
        printf("couldn't create instance for %s\n", _name);
        return;
    }
    if (_event) 
	{
		eventList.emplace(_name, _event);
	}
}

void AudioEngine::SetListenerNumber(int _number)
{
    auto _result = studioSystem->setNumListeners(_number);
    if (_result != FMOD_OK)
    {
        printf("couldn't set listeners number");
    }
}

void AudioEngine::SetListener3DAttributes(int _listener, FMOD_3D_ATTRIBUTES* _attributes, FMOD_VECTOR* _attenuationPosition)
{
    auto _result = studioSystem->setListenerAttributes(_listener, _attributes, _attenuationPosition);
    if (_result != FMOD_OK)
    {
        printf("couldn't set attributes for listener %d", _listener);
    }
}

FMOD_3D_ATTRIBUTES AudioEngine::GetListener3DAttributes(int _listener)
{
    FMOD_3D_ATTRIBUTES _attributes;
    FMOD_VECTOR _attenuationPosition;
    auto _result = studioSystem->getListenerAttributes(_listener, &_attributes, &_attenuationPosition);
    if (_result != FMOD_OK)
    {
        printf("couldn't get attributes for listener %d", _listener);
    }
    return _attributes;
}

float AudioEngine::GetGlobalParameter(const char* _name, bool _final)
{
    float _value, _finalValue;
    auto _result = studioSystem->getParameterByName(_name, &_value, &_finalValue);
    if (_result != FMOD_OK)
    {
        printf("couldn't get value for parameter %s\n", _name);
    }
    if (_final)
    {
        return _finalValue;
    }
    else
    {
        return _value;
    }
}

void AudioEngine::SetGlobalParameter(const char* _name, float _value, bool _ignoreSeekSpeed)
{
    auto _result = studioSystem->setParameterByName(_name, _value, _ignoreSeekSpeed);
    if (_result != FMOD_OK)
    {
        printf("couldn't set parameter %s\n", _name);
    }
}


float AudioEngine::GetBusVolume(const char* _busName, bool _final)
{
    float _value, _finalValue;
    if (busList[_busName])
    {
        auto _result = busList[_busName]->getVolume(&_value, &_finalValue);
        if (_result == FMOD_OK)
        {
            printf("couldn't get volume for bus %s\n", _busName);
        }
    }
    else
    {
        printf("couldn't find bus %s\n", _busName);
    }
    if (_final)
    {
        return _finalValue;
    }
    else
    {
        return _value;
    }
}

void AudioEngine::SetBusVolume(const char* _busName, float _volume)
{
    if (busList[_busName])
    {
        auto _result = busList[_busName]->setVolume(_volume);
        if (_result != FMOD_OK)
        {
            printf("couldn't set volume for bus %s\n", _busName);
        }
    }
    else
    {
        printf("couldn't find bus %s\n", _busName);
    }
}

bool AudioEngine::GetBusMute(const char* _busName)
{
    bool _mute;
    if (busList[_busName])
    {
        auto _result = busList[_busName]->getMute(&_mute);
        if (_result != FMOD_OK)
        {
            printf("couldn't get mute for bus %s\n", _busName);
        }
    }
    else
    {
        printf("couldn't find bus %s\n", _busName);
    }
    return _mute;
}

void AudioEngine::SetBusMute(const char* _busName, bool _mute)
{
    if (busList[_busName])
    {
        auto _result = busList[_busName]->setMute(_mute);
        if (_result != FMOD_OK)
        {
            printf("couldn't set mute for bus %s\n", _busName);
        }
    }
    else
    {
        printf("couldn't find bus %s\n", _busName);
    }
    
}

float AudioEngine::GetVCAVolume(const char* _vcaName, bool _final)
{
    float _value, _finalValue;
    if (vcaList[_vcaName])
    {
        auto _result = vcaList[_vcaName]->getVolume(&_value, &_finalValue);
        if (_result != FMOD_OK)
        {
            printf("couldn't get volume for vca %s\n", _vcaName);
        }
    }
    else
    {
        printf("couldn't find vca %s\n", _vcaName);
    }
    if (_final)
    {
        return _finalValue;
    }
    else
    {
        return _value;
    }
}

void AudioEngine::SetVCAVolume(const char* _vcaName, float _volume)
{
    if (vcaList[_vcaName])
    {
        auto _result = vcaList[_vcaName]->setVolume(_volume);
        if (_result != FMOD_OK)
        {
            printf("couldn't set volume for vca %s\n", _vcaName);
        }
    }
    else
    {
        printf("couldn't find vca %s\n", _vcaName);
    }
}

float AudioEngine::GetEventVolume(const char* _eventName, bool _final)
{
    float _value, _finalValue;
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->getVolume(&_value, &_finalValue);
        if (_result != FMOD_OK)
        {
            printf("couldn't get volume for event %s\n", _eventName);
        }
    }
    else
    {
        printf("couldn't find event %s\n", _eventName);
    }
    if (_final)
    {
        return _finalValue;
    }
    else
    {
        return _value;
    }
}

void AudioEngine::SetEventVolume(const char* _eventName, float _volume)
{
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->setVolume(_volume);
        if (_result != FMOD_OK)
        {
            printf("couldn't set volume for event %s\n", _eventName);
        }
    }
    else
    {
        printf("couldn't find event %s\n", _eventName);
    }
}

int AudioEngine::GetEventPosition(const char* _eventName)
{
    int _position;
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->getTimelinePosition(&_position);
        if (_result != FMOD_OK)
        {
            printf("couldn't set timeline position for event %s\n", _eventName);
        }
    }
    else
    {
        printf("couldn't find event %s\n", _eventName);
    }
    return _position;
}

void AudioEngine::SetEventPosition(const char* _eventName, int _position)
{
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->setTimelinePosition(_position);
        if (_result != FMOD_OK)
        {
            printf("couldn't set timeline position for event %s\n", _eventName);
        }
    }
    else
    {
        printf("couldn't find event %s\n", _eventName);
    }
}

void AudioEngine::PlayOneShotEvent(const char* _eventPath)
{
    FMOD::Studio::EventInstance *_event;
    FMOD::Studio::EventDescription *_eventDescription = nullptr;
    auto _result = studioSystem->getEvent(_eventPath, &_eventDescription);
    if (_result != FMOD_OK) {
        printf("couldn't find event %s\n", _eventPath);
        return;
    }
    _result = _eventDescription->createInstance(&_event);
    if (_result != FMOD_OK)
    {
        printf("couldn't create instance for %s\n", _eventPath);
        return;
    }
    if (_event) 
	{
		_event->start();
        _event->release();
	}
}

void AudioEngine::StartEvent(const char* _name)
{
	if (eventList[_name])
    {
        auto _result = eventList[_name]->start();
        if (_result != FMOD_OK)
        {
            printf("couldn't start event %s\n", _name);
        }
	}
    else
    {
        printf("couldn't find event %s\n", _name);
    }
}

void AudioEngine::StopEvent(const char* _name, bool _fade)
{
	if (eventList[_name])
    {
        FMOD_RESULT _result;
        if (_fade)
        {
            _result = eventList[_name]->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
        }
        else
        {
            _result = eventList[_name]->stop(FMOD_STUDIO_STOP_IMMEDIATE);
        }
        if (_result != FMOD_OK)
        {
            printf("couldn't stop event %s\n", _name);
        }
	}
    else
    {
        printf("couldn't find event %s\n", _name);
    }
}

void AudioEngine::SetEventPaused(const char* _name, bool _paused)
{
    if (eventList[_name])
    {
        auto _result = eventList[_name]->setPaused(_paused);
        if (_result != FMOD_OK)
        {
            printf("couldn't set pause for event %s\n", _name);
        }
	}
    else
    {
        printf("couldn't find event %s\n", _name);
    }
}

bool AudioEngine::GetEventPaused(const char* _name)
{
    bool _paused;
    if (eventList[_name])
    {
        auto _result = eventList[_name]->getPaused(&_paused);
        if (_result != FMOD_OK)
        {
            printf("couldn't get pause for event %s\n", _name);
        }
	}
    else
    {
        printf("couldn't find event %s\n", _name);
    }
    return _paused;
}

float AudioEngine::GetEventParameter(const char* _eventName, const char* _parameterName, bool _final)
{
    float _value, _finalValue;
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->getParameterByName(_parameterName, &_value, &_finalValue);
        if (_result != FMOD_OK)
        {
            printf("couldn't get value for parameter %s\n", _parameterName);
        }
    }
    else
    {
        printf("couldn't find event %s\n", _eventName);
    }
    if (_final)
    {
        return _finalValue;
    }
    else
    {
        return _value;
    }
}

void AudioEngine::SetEventParameter(const char* _eventName, const char* _parameterName, float _value, bool _ignoreSeekSpeed)
{
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->setParameterByName(_parameterName, _value, _ignoreSeekSpeed);
        if (_result != FMOD_OK)
        {
            printf("couldn't set parameter %s\n", _parameterName);
        }
    }
    else
    {
        printf("couldn't find event %s\n", _eventName);
    }   
}

void AudioEngine::SetEvent3DAttributes(const char* _name, FMOD_3D_ATTRIBUTES* _attributes)
{
    if (eventList[_name])
    {
        auto _result = eventList[_name]->set3DAttributes(_attributes);
        if (_result != FMOD_OK)
        {
            printf("couldn't set 3D attributes for event %s\n", _name);
        }
	}
    else
    {
        printf("couldn't find event %s\n", _name);
    }
}

FMOD_3D_ATTRIBUTES AudioEngine::GetEvent3DAttributes(const char* _name)
{
    FMOD_3D_ATTRIBUTES _attributes;
    if (eventList[_name])
    {
        auto _result = eventList[_name]->get3DAttributes(&_attributes);
        if (_result != FMOD_OK)
        {
            printf("couldn't get 3D attributes for event %s\n", _name);
        }
	}
    else
    {
        printf("couldn't find event %s\n", _name);
    }
    return _attributes;
}