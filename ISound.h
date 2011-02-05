#ifndef ISOUND_H
#define ISOUND_H

#include <fmod.hpp>
#include <string>
#include <map>

class ISound {
public:
    ISound();
    ~ISound();
    bool LoadSFX(const std::string& _filename, const std::string _shortName=NULL);
    bool LoadMusic(const std::string& _filename, const std::string _shortName=NULL);
    void frameUpdate();

private:
    FMOD_RESULT result;
    FMOD::System *system;
    FMOD::Sound *tempSound;
    std::map<std::string, FMOD::Sound> soundMap;
};

#endif