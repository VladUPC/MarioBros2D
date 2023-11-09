#include "SoundManager.h"
#include <iostream>



SoundManager::SoundManager() {
    engine = createIrrKlangDevice();
    if (!engine)
        std::cout << "Error al iniciar el motor de sonido" << std::endl;
}

SoundManager& SoundManager::instance() {
    static SoundManager SM;
    return SM;
}



void SoundManager::playSound(const char* soundFile, float volume) {
    if (engine ) {
        ISound* sound = engine->play2D(soundFile, false, false, true);
        if (sound) {
            sound->setVolume(volume);
            sound->drop(); 
        }
    }
}

void SoundManager::stopAllSounds() {
    if (engine)
        engine->stopAllSounds();
}


SoundManager::~SoundManager() {
    if (engine)
        engine->drop(); 
}