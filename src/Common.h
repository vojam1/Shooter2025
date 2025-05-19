//
// Created by sputnik on 5/18/25.
//

#ifndef COMMON_H
#define COMMON_H

// std libraries
#include <cstdint>
#include <memory>

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T>
using WeakRef = std::weak_ptr<T>;

template <typename T>
using UniqueRef = std::unique_ptr<T>;

#endif //COMMON_H
