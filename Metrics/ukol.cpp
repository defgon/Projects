#include <fstream>

#include "PointCloud.h"
#include "metriky.h"
#include "specifications.h"

int main()
{
    using Cloud = PointCloud<3>;
    using Point = typename Cloud::Point;

    Cloud cloud;

    std::ifstream data("C:\\Users\\Mikovec-PC\\Desktop\\FJFI2\\2 semestr\\18PRC2\\ukol4\\data_3d.txt");
    readPoints(cloud, data);

    // definice metriky pro daný typ bodů
    auto metrika = euklidovska_metrika<Point>;

    // nalezení dvojice nejvzdálenějších bodů
    auto p = cloud.findMostDistantPoints(metrika);
    std::cout << "2 nejvzdalenejsi body jsou: " << p.first << " a " << p.second << std::endl;

    // Úkol 1: naprogramujte filtrování dle vzdálenosti od daného bodu (dist(p,c) <= r)
    const Point c = {1, 1, 1};
    const double r = 1;
    DistanceFromPointSpecification<Point> spec1(c, r, metrika);
    auto result1 = filter(cloud, spec1);
    std::cout << "Body se vzdalenosti nejvyse " << r << " od bodu " << c << " jsou: \n";
    for(const auto& b : result1)
    {
        std::cout << b << std::endl;
    }
    // Úkol 2: naprogramujte filtrování dle intervalu vzdálenosti od daného bodu (r1 <= dist(p,c) <= r2)
    SphericalShellSpecification<Point> spec2(c, r, 2*r, metrika);
    auto result2 = filter(cloud, spec2);
    std::cout << "Body se vzdalenosti alespon " << r << " a nejvyse " << 2*r << " od bodu " << c << " jsou: \n";
    for(const auto& b : result2)
    {
        std::cout << b << std::endl;
    }
    // Úkol 3: naprogramujte filtrování dle bounding-boxu (body uvnitř kvádru daného dvojicí protějších vrcholů)
    const Point p1 = {-1, 1, -1};
    const Point p2 = {1, -1, 1};
    BoundingBoxSpecification<Point> spec3(p1, p2);
    auto result3 = filter(cloud, spec3);
    std::cout << "Body uvnitr bounding-boxu daneho body " << p1 << " a " << p2 << " jsou: \n";
    for(const auto& b : result3)
    {
        std::cout << b << std::endl;
    }


    // Úkol 4: naprogramujte složené filtrování: logické operace AND, OR, NOT
    //auto result4 = filter(cloud,!(spec2 && spec3) || spec1);
    //std::cout << "Body vyhovující složenému filtru jsou: \n";
    /*for(const auto& b : result4)
    {
        std::cout << b << std::endl;
    }
    */
}
