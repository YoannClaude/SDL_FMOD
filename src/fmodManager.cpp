#include <fmodManager.h>

static FmodManager* fmodManager;

/*
                                                                                                        SYSTEM
*/

FmodManager::FmodManager()
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

    FmodManager::LoadBank("fmod/banks/Desktop/", "Master");
    FmodManager::LoadBank("fmod/banks/Desktop/", "Master.strings");
    FmodManager::PlayOneShotEvent("event:/test");

}

FmodManager::~FmodManager()
{
    auto _result = studioSystem->release();
    if (_result == FMOD_OK) {
		std::cout<<"FMOD released\n";
	}
}

FmodManager* FmodManager::GetInstance()
{
    if (!fmodManager)
    {
        fmodManager = new FmodManager();
    }
    return fmodManager;
}

void FmodManager::Update()
{
    auto _result = studioSystem->update();
    if (_result != FMOD_OK) {
		std::cout<<"FMOD didn't update properly\n";
	}
}

void FmodManager::SetListenerNumber(int _number)
{
    auto _result = studioSystem->setNumListeners(_number);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't set listeners number\n";
    }
}

/*
                                                                                                    BANKS
*/

void FmodManager::LoadBank(std::string _path, const char* _bankName)
{
    std::string _bankPath = _path + _bankName + ".bank";
    FMOD::Studio::Bank *_bank;
    auto _result = studioSystem->loadBankFile(_bankPath.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &_bank);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't load bank "<< _bankName<<"\n";
        return;
    }
    if (_bank) 
    {
        bankList.emplace(_bankName, _bank);
    }
}

/*
                                                                                                    BUSES
*/

void FmodManager::LoadBus(std::string _path, const char* _busName)
{
    std::string _busPath = _path + _busName;
    FMOD::Studio::Bus *_bus;
    auto _result = studioSystem->getBus(_busPath.c_str(), &_bus);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't find bus "<< _busName<<"\n";
        return;
    }
    if (_bus) 
	{
		busList.emplace(_busName, _bus);
	}
}

float FmodManager::GetBusVolume(const char* _busName, bool _final)
{
    float _value, _finalValue;
    if (busList[_busName])
    {
        auto _result = busList[_busName]->getVolume(&_value, &_finalValue);
        if (_result == FMOD_OK)
        {
            std::cout<<"couldn't get volume for bus "<< _busName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find bus "<< _busName<<"\n";
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

void FmodManager::SetBusVolume(const char* _busName, float _volume)
{
    if (busList[_busName])
    {
        auto _result = busList[_busName]->setVolume(_volume);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't set volume for bus "<< _busName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find bus "<< _busName<<"\n";
    }
}

bool FmodManager::GetBusMute(const char* _busName)
{
    bool _mute;
    if (busList[_busName])
    {
        auto _result = busList[_busName]->getMute(&_mute);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't get mute for bus "<< _busName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find bus "<< _busName<<"\n";
    }
    return _mute;
}

void FmodManager::SetBusMute(const char* _busName, bool _mute)
{
    if (busList[_busName])
    {
        auto _result = busList[_busName]->setMute(_mute);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't set mute for bus "<< _busName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find bus "<< _busName<<"\n";
    }
    
}

/*
                                                                                                    VCAs
*/

void FmodManager::LoadVCA(std::string _path, const char* _vcaName)
{
    std::string _vcaPath = _path + _vcaName;
    FMOD::Studio::VCA *_vca;
    auto _result = studioSystem->getVCA(_vcaPath.c_str(), &_vca);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't find VCA "<< _vcaName<<"\n";
        return;
    }
    if (_vca) 
	{
		vcaList.emplace(_vcaName, _vca);
	}
}

float FmodManager::GetVCAVolume(const char* _vcaName, bool _final)
{
    float _value, _finalValue;
    if (vcaList[_vcaName])
    {
        auto _result = vcaList[_vcaName]->getVolume(&_value, &_finalValue);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't get volume for vca "<< _vcaName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find vca "<< _vcaName<<"\n";
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

void FmodManager::SetVCAVolume(const char* _vcaName, float _volume)
{
    if (vcaList[_vcaName])
    {
        auto _result = vcaList[_vcaName]->setVolume(_volume);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't set volume for vca "<< _vcaName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find vca "<< _vcaName<<"\n";
    }
}

/*
                                                                                                    EVENTS
*/

void FmodManager::LoadEvent(std::string _path, const char* _eventName)
{
    std::string _eventPath = _path + _eventName;
    FMOD::Studio::EventInstance *_event;
    FMOD::Studio::EventDescription *_eventDescription = nullptr;
    auto _result = studioSystem->getEvent(_eventPath.c_str(), &_eventDescription);
    if (_result != FMOD_OK) {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
        return;
    }
    _result = _eventDescription->createInstance(&_event);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't create instance for "<< _eventName<<"\n";
        return;
    }
    if (_event) 
	{
		eventList.emplace(_eventName, _event);
	}
}

float FmodManager::GetEventVolume(const char* _eventName, bool _final)
{
    float _value, _finalValue;
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->getVolume(&_value, &_finalValue);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't get volume for event "<< _eventName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
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

void FmodManager::SetEventVolume(const char* _eventName, float _volume)
{
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->setVolume(_volume);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't set volume for event "<< _eventName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }
}

int FmodManager::GetEventPosition(const char* _eventName)
{
    int _position;
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->getTimelinePosition(&_position);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't get timeline position for event "<< _eventName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }
    return _position;
}

void FmodManager::SetEventPosition(const char* _eventName, int _position)
{
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->setTimelinePosition(_position);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't set timeline position for event "<< _eventName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }
}

void FmodManager::PlayOneShotEvent(const char* _eventPath)
{
    FMOD::Studio::EventInstance *_event;
    FMOD::Studio::EventDescription *_eventDescription = nullptr;
    auto _result = studioSystem->getEvent(_eventPath, &_eventDescription);
    if (_result != FMOD_OK) {
        std::cout<<"couldn't find event "<< _eventPath<<"\n";
        return;
    }
    _result = _eventDescription->createInstance(&_event);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't create instance for "<< _eventPath<<"\n";
        return;
    }
    if (_event) 
	{
		_event->start();
        _event->release();
	}
}

void FmodManager::StartEvent(const char* _eventName)
{
	if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->start();
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't start event "<< _eventName<<"\n";
        }
	}
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }
}

void FmodManager::StopEvent(const char* _eventName, bool _fade)
{
	if (eventList[_eventName])
    {
        FMOD_RESULT _result;
        if (_fade)
        {
            _result = eventList[_eventName]->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT);
        }
        else
        {
            _result = eventList[_eventName]->stop(FMOD_STUDIO_STOP_IMMEDIATE);
        }
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't stop event "<< _eventName<<"\n";
        }
	}
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }
}

void FmodManager::SetEventPaused(const char* _eventName, bool _paused)
{
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->setPaused(_paused);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't set pause for event "<< _eventName<<"\n";
        }
	}
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }
}

bool FmodManager::GetEventPaused(const char* _eventName)
{
    bool _paused;
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->getPaused(&_paused);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't get pause for event "<< _eventName<<"\n";
        }
	}
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }
    return _paused;
}


/*
                                                                                                    3D
*/
void FmodManager::SetListener3DAttributes(int _listener, FMOD_3D_ATTRIBUTES* _attributes, FMOD_VECTOR* _attenuationPosition)
{
    auto _result = studioSystem->setListenerAttributes(_listener, _attributes, _attenuationPosition);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't set attributes for listener "<< _listener<<"\n";
    }
}

FMOD_3D_ATTRIBUTES FmodManager::GetListener3DAttributes(int _listener)
{
    FMOD_3D_ATTRIBUTES _attributes;
    FMOD_VECTOR _attenuationPosition;
    auto _result = studioSystem->getListenerAttributes(_listener, &_attributes, &_attenuationPosition);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't get attributes for listener "<< _listener<<"\n";
    }
    return _attributes;
}

void FmodManager::SetEvent3DAttributes(const char* _eventName, FMOD_3D_ATTRIBUTES* _attributes)
{
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->set3DAttributes(_attributes);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't set 3D attributes for event "<< _eventName<<"\n";
        }
	}
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }
}

FMOD_3D_ATTRIBUTES FmodManager::GetEvent3DAttributes(const char* _eventName)
{
    FMOD_3D_ATTRIBUTES _attributes;
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->get3DAttributes(&_attributes);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't get 3D attributes for event "<< _eventName<<"\n";
        }
	}
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }
    return _attributes;
}

/*
                                                                                                    PARAMETERS
*/

float FmodManager::GetGlobalParameter(const char* _parameterName, bool _final)
{
    float _value, _finalValue;
    auto _result = studioSystem->getParameterByName(_parameterName, &_value, &_finalValue);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't get value for parameter "<< _parameterName<<"\n";
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

void FmodManager::SetGlobalParameter(const char* _parameterName, float _value, bool _ignoreSeekSpeed)
{
    auto _result = studioSystem->setParameterByName(_parameterName, _value, _ignoreSeekSpeed);
    if (_result != FMOD_OK)
    {
        std::cout<<"couldn't set parameter "<< _parameterName<<"\n";
    }
}

float FmodManager::GetLocalParameter(const char* _eventName, const char* _parameterName, bool _final)
{
    float _value, _finalValue;
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->getParameterByName(_parameterName, &_value, &_finalValue);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't get value for parameter "<< _parameterName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
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

void FmodManager::SetLocalParameter(const char* _eventName, const char* _parameterName, float _value, bool _ignoreSeekSpeed)
{
    if (eventList[_eventName])
    {
        auto _result = eventList[_eventName]->setParameterByName(_parameterName, _value, _ignoreSeekSpeed);
        if (_result != FMOD_OK)
        {
            std::cout<<"couldn't set parameter "<< _parameterName<<"\n";
        }
    }
    else
    {
        std::cout<<"couldn't find event "<< _eventName<<"\n";
    }   
}
