#include "ISound.h"

ISound::ISound() {
    if ((result = FMOD::System_Create(&system)) != FMOD_OK) {
        // You're fucked O_O
    }
    result = system->init(100, FMOD_INIT_NORMAL, 0);
}

ISound::~ISound() {
    result = system->release();
}

void ISound::frameUpdate() {
    result = system->update();
}

bool ISound::LoadSFX(const std::string& _filename, const std::string _shortName) {
    std::string text;
    if (_shortName.size() != 0) {
        text = _shortName;
    } else {
        text = _filename.substr(_filename.find_last_of("\\"), _filename.find_last_of("."));
    }
    soundMap.insert(std::make_pair(text, system->createSound(_filename.c_str(), FMOD_2D | FMOD_LOOP_OFF | FMOD_CREATESAMPLE, 0, &tempSound)));
    return true;
}