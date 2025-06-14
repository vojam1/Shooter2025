//
// Created by sputnik on 5/22/25.
//

#ifndef ASSETBANK_H
#define ASSETBANK_H
#include <raylib.h>
#include <string>
#include <unordered_map>


class AssetBank {
public:
    AssetBank() = default;

    void addModel(const std::string& modelId, const char* filePath);
    void removeModel(const std::string& modelId);
    Model& getModel(const std::string& modelId);

    void addModelAnimation(const std::string& modelAnimId, const char* filePath);
    void removeModelAnimation(const std::string& modelAnimId);
    std::pair<ModelAnimation*, int>& getModelAnimation(const std::string& modelAnimId);

    void addSound(const std::string& soundId, const char* filePath, float volume);
    void removeSound(const std::string& soundId);
    Sound& getSound(const std::string& soundId);

private:
    std::unordered_map<std::string, Model> models;
    std::unordered_map<std::string, std::pair<ModelAnimation*, int>> animations;

    std::unordered_map<std::string, Sound> sounds;
};



#endif //ASSETBANK_H
