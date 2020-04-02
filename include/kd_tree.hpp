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
#include <vector>

namespace kd_tree
{
template <int d>
class tree
{
    node<d> m_node;
    uint8_t m_dimension;

public:
    tree(std::vector<vec<d>> points);
    tree(std::vector<vec<d>> points, float min, float max);
    tree(std::vector<vec<d>> points, vec<d> min, vec<d> max);

    std::unique_ptr<tree> left;
    std::unique_ptr<tree> right;
};

template <int d>
tree<d>::tree(std::vector<vec<d>> points, float min, float max) : tree(points, vec<d>(min), vec<d>(max))
{}

template<int d>
tree<d>::tree(std::vector<vec<d>> points) : tree(points,
                                                 -std::numeric_limits<float>::infinity(),
                                                  std::numeric_limits<float>::infinity())
{}

template<int d>
tree<d>::tree(std::vector<vec<d>> points, vec<d> min, vec<d> max) : left(nullptr), right(nullptr), m_node(min, max)
{
    if (points.size() == 0) return;
    if (points.size() == 1)
    {
        return;
    }

    m_dimension = utils::get_random_float() * d;

    // apply nth element to divide the points according to dimension
    std::nth_element(points.begin(), points.begin() + points.size() / 2 - 1, points.end(), [](const vec<d>& point1, const vec<d>& point2)
    {
        return point1[d] < point2[d];
    });

    auto median_closest_left = points[points.size() / 2 - 1];

    // apply nth element to divide the points according to dimension
    std::nth_element(points.begin(), points.begin() + points.size() / 2, points.end(), [](const vec<d>& point1, const vec<d>& point2)
    {
          return point1[d] < point2[d];
    });

    auto median = points[points.size() / 2];

    std::cerr << "Median : " << median << '\n';
    std::cerr << "Point on the left of the median : " << median_closest_left << '\n';

    auto divider = (median[d] + median_closest_left[d]) / 2.f;

    std::cerr << "Divider : " << divider << '\n';

    std::vector<vec<d>> left_half = {points.begin(), points.begin() + points.size() / 2};
    std::vector<vec<d>> right_half = {points.begin() + points.size() / 2, points.end()};

    for (auto elem : left_half) std::cerr << elem << ", ";
    std::cerr << "  ---  ";
    for (auto elem : right_half) std::cerr << elem << ", ";
    std::cerr << '\n';

    auto left_min = min;
    auto left_max = max; left_max[m_dimension] = d;

    auto right_min = min; right_min[m_dimension] = d;
    auto right_max = max;

    left  = std::make_unique<tree>(tree(left_half, left_max, left_max));
    right = std::make_unique<tree>(tree(right_half, right_min, right_max));
}
}