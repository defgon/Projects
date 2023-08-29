#include "maze.h"

int main() {
  Maze m;
  std::vector<Position> path; // vysledna cesta bludistem jako seznam pozic

  // Nacteni bludiste ze souboru
  try {
    m.loadFromFile("");
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }

  // Vypis nacteneho bludiste
  m.print();

  // Hledani nejkratsi cesty ven z bludiste
  try {
    path = m.solve();
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 2;
  }

  // Vypis bludiste s cestou
  m.print();

  // Vypis cesty
  std::cout << "Cesta final" << std::endl;
  for (auto &x : path) {
      std::cout << " > " << x;
  }
  std::cout << std::endl;


  return 0;
}
