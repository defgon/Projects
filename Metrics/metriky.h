#pragma once

#include <cmath>

template <typename Point>
typename Point::value_type maximova_metrika(const Point& p1, const Point& p2)
{
    typename Point::value_type d = std::abs(p1[0] - p2[0]);
    for (std::size_t i = 1; i < p1.size(); i++) {
        typename Point::value_type di = std::abs(p1[i] - p2[i]);
        if (di > d)
            d = di;
    }
    return d;
}

template <typename Point>
typename Point::value_type manhattanska_metrika(const Point& p1, const Point& p2)
{
    typename Point::value_type dist = 0;
    for (std::size_t i = 0; i < p1.size(); i++) {
        dist += std::abs(p1[i] - p2[i]);
    }
    return std::sqrt(dist);
}

template <typename Point>
typename Point::value_type euklidovska_metrika(const Point& p1, const Point& p2)
{
    typename Point::value_type sum = 0;
    for (std::size_t i = 0; i < p1.size(); i++) {
        typename Point::value_type di = std::abs(p1[i] - p2[i]);
        sum += di * di;
    }
    return std::sqrt(sum);
}