#include <tuple.h>
#include <cassert>

int main()
{
    //my::tuple<> t0;  // nema smysl
    my::tuple<int> t1;
    my::tuple<int, long> t2;
    my::tuple<int, long, float> t3;

    // konstruktor s parametry
    my::tuple<int, int, float> t4(1, 2, 3.14);

    // pristup k prvkum
    int& a0 = my::get<0>(t4);
    int& a1 = my::get<1>(t4);
    float& a2 = my::get<2>(t4);
    assert(a0 == 1);
    assert(a1 == 2);
    assert(a2 == 3.14);

    return 0;
}
