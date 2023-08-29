#pragma once

#include <array>
#include <functional>
#include <set>
#include <iostream>
#include <sstream>
#include <string>

template <int dim>
class PointCloud
{
public:
    using Point = std::array<double, dim>;
    using CallbackFunction = std::function<void(Point)>;

    // defaultní konstruktor
    PointCloud() = default;

    // konstruktor s callback funkcí (volá se při přidání nového bodu)
    PointCloud(CallbackFunction callback)
    : callback(callback)
    {}

    // metoda pro získání dimenze
    static constexpr int getDimension()
    {
        return dim;
    }

    // metoda pro přidání nového bodu
    void addPoint(const Point& p)
    {
        points.insert(p);
        if (callback)
            callback(p);
    }

    // metody pro přístup k bodům v cloudu pomocí iterátorů
    auto begin()
    {
        return points.begin();
    }
    auto begin() const
    {
        return points.begin();
    }
    auto end()
    {
        return points.end();
    }
    auto end() const
    {
        return points.end();
    }

    // metoda pro nalezení dvou nejvzdálenějších bodů (úkol 1)
    // MetricFunction - typ funkce pro měření vzdálenosti; použití: d = dist(p1, p2);
    template <typename MetricFunction>
    std::pair<Point, Point> findMostDistantPoints(MetricFunction dist) const
    {
        double max_d = 0;
        std::pair<Point, Point> result;
        for (const auto& p1 : points)
            for (const auto& p2 : points) {
                const double d = dist(p1, p2);
                if (d > max_d) {
                    result.first = p1;
                    result.second = p2;
                    max_d = d;
                }
            }
        return result;
    }

private:
    CallbackFunction callback = nullptr;
    std::set<Point> points;
};

template <typename Cloud>
void readPoints(Cloud& cloud, std::istream& str)
{
    while (true) {
        std::string line;
        std::getline(str, line);
        if (!str)
            break;

        std::stringstream s(line);
        typename Cloud::Point p;
        for (auto& component : p)
            s >> component;

        if (s.eof() && !s.fail())
            cloud.addPoint(p);
        else
            std::cerr << "chyba pri cteni dat z radku \"" << line << "\"" << std::endl;
    }
}

template <typename T, std::size_t dim>
std::ostream& operator<<(std::ostream& str, const std::array<T, dim>& point)
{
    str << "[";
    if (dim > 0)
        str << point[0];
    for (std::size_t i = 1; i < dim; i++)
        str << ", " << point[i];
    str << "]";

    return str;
}