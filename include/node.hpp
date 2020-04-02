//
// Created by goksu on 3/30/20.
//

#pragma once

#include <glm/glm.hpp>
#include <iostream>

#include "vecd.hpp"

namespace kd_tree
{
template <class T>
class node
{
    T min_boundaries;
    T max_boundaries;
public:

    node();
    node(float min, float max);
    node(T min, T max);
};

template <class T>
node<T>::node() : node(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity())
{}

template <class T>
node<T>::node(float min, float max)
{
    min_boundaries = T(min);
    max_boundaries = T(max);
}

template <class T>
node<T>::node(T min, T max)
{
    min_boundaries = min;
    max_boundaries = max;
}
}