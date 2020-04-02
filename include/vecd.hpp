//
// Created by goksu on 3/30/20.
//

#pragma once

#include <glm/glm.hpp>
#include <ostream>
// user defined types logging by implementing operator<<
#include "spdlog/fmt/ostr.h" // must be included

template<int d>
struct vec : glm::vec<d, float, glm::defaultp>
{
    using glm::vec<d, float, glm::defaultp>::vec;

    vec(float scalar)
        : glm::vec<d, float, glm::defaultp>(scalar)
    {}
    vec(glm::vec1 scalar)
        : glm::vec<d, float, glm::defaultp>(scalar)
    {}

    friend std::ostream& operator<<(std::ostream& os, vec& vec)
    {
        os << "{";
        for (int i = 0; i < d; ++i) os << vec[i] << ", ";

        os << '\b';
        os << '\b';
        os << "}";
        return os;
    }

    template<typename OStream>
    friend OStream& operator<<(OStream& os, const vec& vec)
    {
        os << "{";
        for (int i = 0; i < d; ++i) os << vec[i] << ", ";

        os << '\b';
        os << '\b';
        os << "}";
        return os;
    }
};
