#include "graph.h"
#include <iostream>

int main() {
  Graph m;
  std::vector<int> path;

  int s;
  int n;
  int f;
  while (true) {
        std::cout << "Zadejte pocet paliva:" << std::endl;
        std::cin >> f;
        m.setFuel(f);
        if (std::cin.fail() || (s < 0)) {
              std::cout << "Neplatny vstup zadejte znovu" << std::endl;
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    std::cout << std::endl;
  }

  while (true) {
        std::cout << "Zadejte typ nacteni:" << std::endl;
        std::cout << "Pro nacteni matice ze souboru zadejte 1" << std::endl;
        std::cout << "Pro nacteni matice rucne zadejte 2" << std::endl;
        std::cout << "Pro nacteni random matice zadejte 3" << std::endl;
        std::cin >> s;

        if (std::cin.fail() || (s != 1 && s != 2 && s != 3)) {
              std::cout << "Neplatny vstup zadejte 1 nebo 2 nebo 3" << std::endl;
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    std::cout << std::endl;
  }
  switch (s) {
    case 1:
      // Nacteni ze souboru
      try {
        m.loadFromFile("C:\\Users\\Mikovec-PC\\Desktop\\FJFI2\\4 semestr\\18PRC2\\Zapocet\\graph.txt");
      } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
      }
      break;
    case 2:
      // Zadání ručně
      try {
        m.getFromConsole();
      } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 2;
      }
      break;
    case 3:
      try {
          std::cout << "Zadejte pocet uzlu (radek = sloupcu) < 10:" << std::endl;
          std::cin >> n;
          m.generateRandom(n);
      } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 3;
      }
      break;
  }

  int a,b;
  // Hledani nejkratsi cesty
  while (true) {
          // a
          std::cout << "Zadejte uzly od 0 -> do " << m.getSize()-1 << " pro nejkratsi cestu mezi nimy (od<do):" << std::endl;
          std::cout << "a: ";
          std::cin >> a;
          if (std::cin.fail() || (a < 0 || a > m.getSize()-1)) {
                std::cout << "Neplatny vstup zadejte cislo v rozpeti od 0 do " << m.getSize() << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          }

          // b
          std::cout << "b: ";
          std::cin >> b;
          if (std::cin.fail() || (b < 0 || b > m.getSize()-1 || b <= a)) {
                std::cout << "Neplatny vstup zadejte cislo v rozpeti od 0 do " << m.getSize()-1 << " (od < do)" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          } else {
              break;
          }
      std::cout << std::endl;
  }
  try {
    path = m.dijkstra(a,b);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 4;
  }

  // Vypis cesty
  std::cout << "Cesta vypis: " << std::endl;
  for (auto &x : path) {
      std::cout << " -> " << x;
  }
  std::cout << std::endl;

  return 0;
}
