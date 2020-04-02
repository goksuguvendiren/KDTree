//
// Created by goksu on 3/30/20.
//

#pragma once

#include "node.hpp"
#include "utils.hpp"
#include "vecd.hpp"

#include <algorithm>
#include <glm/glm.hpp>
#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include <sstream>
#include <vector>

namespace kd_tree
{
template <class T>
class tree
{
    node<T> m_node;
    uint8_t m_dimension;

public:
    tree(std::vector<T> points);
    tree(std::vector<T> points, float min, float max);
    tree(std::vector<T> points, T min, T max);

    std::unique_ptr<tree> left;
    std::unique_ptr<tree> right;
};

template <class T>
tree<T>::tree(std::vector<T> points, float min, float max) : tree(points, T(min), T(max))
{}

template <class T>
tree<T>::tree(std::vector<T> points) : tree(points,
                                            -std::numeric_limits<float>::infinity(),
                                             std::numeric_limits<float>::infinity())
{}

template <class T>
tree<T>::tree(std::vector<T> points, T min, T max) : left(nullptr), right(nullptr), m_node(min, max)
{
    if (points.size() == 0) return;
    if (points.size() == 1)
    {
        std::stringstream points_string;
        for (auto elem : points) points_string << elem;// << ", ";
        spdlog::trace("Points in this level are : {}", points_string.str());
        spdlog::trace("The bounding box of the points is : {} - {}", min, max);

        return;
    }

    //TODO: don't choose the dimension randomly, choose it among the maximum variation
    int d = points[0].length(); // .length() function returns the dimensionality of the point.
    assert(d == 1);
    m_dimension = utils::get_random_float() * d;

    // apply nth element to divide the points according to dimension
    std::nth_element(points.begin(), points.begin() + points.size() / 2 - 1, points.end(), [m_dimension = m_dimension](const T& point1, const T& point2)
    {
        return point1[m_dimension] < point2[m_dimension];
    });

    auto median_closest_left = points[points.size() / 2 - 1];

    // apply nth element to divide the points according to dimension
    std::nth_element(points.begin(), points.begin() + points.size() / 2, points.end(), [m_dimension = m_dimension](const T& point1, const T& point2)
    {
          return point1[m_dimension] < point2[m_dimension];
    });

    auto median = points[points.size() / 2];
    auto divider = (median[m_dimension] + median_closest_left[m_dimension]) / 2.f;

    std::stringstream points_string;
    for (auto elem : points) points_string << elem << ", ";
    spdlog::trace("Points in this level are : {}", points_string.str());
    spdlog::trace("The bounding box of the points is : {} - {}", min, max);
    spdlog::trace("Dividing the points in {}th dimension", m_dimension);
    spdlog::trace("The point before the median and the median are: {} and {}", median_closest_left, median);
    spdlog::trace("The divider between those is : {}", divider);

    std::vector<T> left_half = {points.begin(), points.begin() + points.size() / 2};
    std::vector<T> right_half = {points.begin() + points.size() / 2, points.end()};

    std::stringstream trace_string;
    for (auto elem : left_half) trace_string << elem << ", ";
    trace_string << "  |  ";
    for (auto elem : right_half) trace_string << elem << ", ";
    spdlog::trace(trace_string.str());

    auto left_min = min;
    auto left_max = max; left_max[m_dimension] = divider;

    auto right_min = min; right_min[m_dimension] = divider;
    auto right_max = max;

    left  = std::make_unique<tree>(tree(left_half, left_min, left_max));
    right = std::make_unique<tree>(tree(right_half, right_min, right_max));
}
}