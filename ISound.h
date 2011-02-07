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
    void PlaySFX(const std::string _fileName);
    //void PlaySFX(const std::string _shortName);
    void PlayMusic(const std::string& _filename);
    void PlayMusic(const std::string _shortName);
    void frameUpdate();

    // Quasi-Singleton instantiation
    static ISound* Instance;

private:
    FMOD_RESULT result;
    FMOD::System *system;
    FMOD::Sound *tempSound;
    FMOD::Channel *channel;
    std::map<std::string, FMOD::Sound> soundMap;
    std::map<std::string, FMOD::Sound>::const_iterator sIt;
};

#endif