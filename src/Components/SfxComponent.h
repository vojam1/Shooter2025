//
// Created by sputnik on 6/14/25.
//

#ifndef SFXCOMPONENT_H
#define SFXCOMPONENT_H

#include <raylib.h>

struct SfxComponent {
    Sound dyingSound {};

    explicit SfxComponent(const Sound& sfx = {nullptr}) {
        dyingSound = sfx;
    }

    explicit SfxComponent(std::string& filePath, const float volume = 1.f) {
        dyingSound = LoadSound(filePath.c_str());
        SetSoundVolume(dyingSound, volume);
    }
};

#endif //SFXCOMPONENT_H
