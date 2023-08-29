#include "maze.h"

int main()
{
    Maze m;
    std::vector<Position> path; // vysledna cesta bludistem jako seznam pozic

    // Nacteni bludiste ze souboru
    try {
        m.loadFromFile("C:\\Users\\Mikovec-PC\\Desktop\\FJFI2\\4 semestr\\18PRC2\\Bludiste\\data\\maze2.txt");
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // Vypis nacteneho bludiste
    std::cout << "Nactene bludiste ze souboru: " << std::endl;
    m.print();

    // Hledani nejkratsi cesty ven z bludiste
    try {
        path = m.solve();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // Vypis cesty
    std::cout << "Cesta z bludiste je: " << std::endl;
    for (auto& x : path) {
        std::cout << x << std::endl;
    }
    std::cout << std::endl;

    // Vypis bludiste s cestou
    std::cout << "Vyresene bludiste: " << std::endl;
    m.print();

    return 0;
}
