#ifndef _SOUND_MANAGER_INCLUDE
#define _SOUND_MANAGER_INCLUDE

#include <irrKlang.h>

using namespace irrklang;

class SoundManager {
private:
    ISoundEngine* engine;
    SoundManager();

public:
    static SoundManager& instance();
    void playSound(const char* soundFile, float volume);
    void stopAllSounds();
    ~SoundManager();
};

#endif 
