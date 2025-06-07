//
// Created by sputnik on 5/18/25.
//

#ifndef COMMON_H
#define COMMON_H

// std libraries
#include <cstdint>
#include <memory>

constexpr float SCREEN_WIDTH = 1920;
constexpr float SCREEN_HEIGHT = 1080;

inline int32_t HIGH_SCORE = 0;

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using WeakRef = std::weak_ptr<T>;

template <typename T>
using UniqueRef = std::unique_ptr<T>;

#endif //COMMON_H
