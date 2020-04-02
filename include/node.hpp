//
// Created by goksu on 3/30/20.
//

#pragma once

#include <glm/glm.hpp>
#include <iostream>

#include "vecd.hpp"

namespace kd_tree
{
template <int d>
class node
{
    vec<d> min_boundaries;
    vec<d> max_boundaries;
public:

    node();
    node(float min, float max);
    node(vec<d> min, vec<d> max);
};

template <int d>
node<d>::node() : node(-std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity())
{}

template <int d>
node<d>::node(float min, float max)
{
    min_boundaries = vec<d>(min);
    max_boundaries = vec<d>(max);
}

template<int d>
node<d>::node(vec<d> min, vec<d> max)
{
    min_boundaries = min;
    max_boundaries = max;
}
}