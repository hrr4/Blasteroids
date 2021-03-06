#include "ISound.h"

ISound* ISound::Instance = NULL;

ISound::ISound() {
    if ((result = FMOD::System_Create(&system)) != FMOD_OK) {
        // You're fucked O_O
    }
    result = system->init(100, FMOD_INIT_NORMAL, 0);
}

ISound& ISound::getInstance() {
    if (Instance == NULL) {
        Instance = new ISound();
    }
    return(*Instance);
}

ISound::~ISound() {result = system->release();}

void ISound::frameUpdate() {result = system->update();}

bool ISound::LoadSFX(const std::string& _filename, const std::string _shortName) {
    std::string text;
    if (_shortName.size() != 0) {
        text = _shortName;
    } else {
        text = _filename.substr((_filename.find_last_of("\\") || _filename.find_last_of("/")), _filename.find_last_of("."));
    }
    result = system->createSound(_filename.c_str(), FMOD_2D | FMOD_LOOP_OFF | FMOD_CREATESAMPLE, 0, &tempSound);
    Instance->soundMap.insert(std::make_pair(text, *tempSound));
    tempSound = 0;
    return true;
}

void ISound::PlaySFX(const std::string _shortName) {
    for (sIt = soundMap.begin(); sIt != soundMap.end(); ++sIt) {
        if (sIt->first == _shortName) {
            // BUG: Current problem is here, ERR_INVALID_HANDLE is most likely a channel issue
            result = system->playSound(FMOD_CHANNEL_FREE, &sIt->second, false, &Instance->channel);
        }
    }
}

/*void ISound::PlaySFX(const std::string _fileName) {
    result = system->createSound(_fileName.c_str(), FMOD_DEFAULT, 0, &tempSound);
    if ((result = system->playSound(FMOD_CHANNEL_FREE, tempSound, false, 0)) != FMOD_OK) {
        // WHOOPS
    }
}*/