//
// Created by goksu on 3/30/20.
//

#pragma once

#include "node.hpp"

#include <random>

namespace kd_tree::utils
{
inline static std::random_device rd;  // Will be used to obtain a seed for the random number engine
inline static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
inline float get_random_float()
{
    std::uniform_real_distribution<float> dis(0, 1.0);
    return dis(gen);
}
}
