//
// Created by sputnik on 5/22/25.
//

#include "AssetBank.h"

void AssetBank::addModel(const std::string& modelId, const char *filePath) {
    Model model = LoadModel(filePath);
    models.insert(std::pair<std::string, Model>(modelId, model));
}

void AssetBank::removeModel(const std::string &modelId) {
    models.erase(models.find(modelId));
}

Model& AssetBank::getModel(const std::string &modelId) {
    return models.at(modelId);
}

void AssetBank::addModelAnimation(const std::string& modelAnimId, const char *filePath) {
    int animCount = 0;
    ModelAnimation *anim = LoadModelAnimations(filePath, &animCount);
    animations.insert(std::make_pair(modelAnimId, std::make_pair(anim, animCount)));
}

void AssetBank::removeModelAnimation(const std::string& modelAnimId) {
    animations.erase(animations.find(modelAnimId));
}

std::pair<ModelAnimation*, int>& AssetBank::getModelAnimation(const std::string &modelAnimId) {
    return animations.at(modelAnimId);
}