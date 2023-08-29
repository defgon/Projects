#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>

class WordCounter
{
public:
    // konstruktor
    WordCounter() = default;

    // metoda pro přidání dalšího slova
    void addWord(const std::string& word)
    {
        word_counts [word]++;
        all_words++;
    }

    // metoda pro získání počtu všech slov (úkol 1)
    int getWordsCount() const
    {
        return all_words;
    }

    // metoda pro získání počtu různých slov (úkol 1)
    int getUniqueWordsCount() const
    {
        return word_counts.size();
    }

    // metoda pro získání nejdelšího slova (úkol 2)
    std::string getLongestWord() const
    {
        std::string longest;
        for(const auto& pair : word_counts){
            const std::string& word = pair.first;
            if(word.size() > longest.size())
                longest = word;
        }
        return longest;
    }

    // metoda pro získání nejkratšího slova (úkol 2)
    std::string getShortestWord() const
    {
        std::string shortest = getLongestWord();
        for(const auto& pair : word_counts){

            const std::string& word = pair.first;
            if(word.size() < shortest.size())
                shortest = word;
        }
        return shortest;
    }

    // metoda pro získání nejfrekventovanějších slov (úkoly 3 a 4)
    std::vector<std::pair<std::string,int>> getMostFrequentWords(int count) const
    {
        std::vector<std::pair<std::string,int>> words;
        //zkopirovani prvku z mapy
        for(const auto& pair : word_counts)
            words.emplace_back(pair);
        //serazeni dle poctu vyskytu
        auto comparator = [] (std::pair<std::string,int>& a,
                              std::pair<std::string,int>& b)
        {
            return a.second > b.second;
        };
        std::sort(words.begin(),words.end(),comparator);
        //zkraceni vektoru
        words.resize(count);
        return words;

    }
    // metoda pro získání nejméně frekventovaných slov (úkoly 3 a 4)
    std::vector<std::pair<std::string,int>> getLeastFrequentWords(int count) const
    {
        std::vector<std::pair<std::string,int>> words;
        //zkopirovani prvku z mapy
        for(const auto& pair : word_counts)
            words.emplace_back(pair);
        //serazeni dle poctu vyskytu
        auto comparator = [] (std::pair<std::string,int>& a,
                              std::pair<std::string,int>& b)
        {
            return a.second < b.second;
        };
        std::sort(words.begin(),words.end(),comparator);
        //zkraceni vektoru
        words.resize(count);
        return words;
    }

private:
    std::unordered_map<std::string,int> word_counts;
    int all_words = 0;
};



// funkce pro přečtení slov ze souboru a přidávání do objektu WordCounter
void readWords(WordCounter& counter, std::istream& str)
{
    std::string word;
    while((str >> word).good()) {
        // overime jestli prvni char je valid
        if (isprint(word[0]))
            counter.addWord(word);
    }
}

// funkce pro výpis dat ve formátu tabulky (úkol 4)
//void printTable(std::ostream& str, const std::vector<...>& data);

int main()
{
    const std::string filename = "C:\\Users\\Mikovec-PC\\Desktop\\FJFI2\\2 semestr\\18PRC2\\CV2\\data2.txt";
    std::ifstream file(filename);

    if (!file.good()) {
        std::cout << "soubor " << filename << " neslo otevrit" << std::endl;
        return 1;
    }

    WordCounter counter;
    readWords(counter, file);

    // úkol 1
    std::cout << "Pocet vsech slov je " << counter.getWordsCount() << std::endl;
    std::cout << "Pocet ruznych slov je " << counter.getUniqueWordsCount() << std::endl;

    // Dále vypište informace pro úkoly 2, 3, 4.

    //ukol 2 Vypíše nejdelší a nejkratší slovo v textu včetně jeho délky.

    std::cout<< "Nejdelsi slovo je: \'" << counter.getLongestWord() << "\' jehoz delka je " << counter.getLongestWord().size() << std::endl;
    std::cout<< "Nejkratsi slovo je: \'" << counter.getShortestWord() << "\' jehoz delka je " << counter.getShortestWord().size() << std::endl;
    std::cout << std::endl;

    //ukol 3 Vypíše 3 nejčastější a 3 nejméně častá slova včetně jejich počtu výskytů.
    //ukol 4 Vypíše dvě textové tabulky (Nejčastější slova a Nejméně častá slova) obsahující max 10 řádků v následujícím formátu:

    std::cout<< "Nejcastejsi slova: " << std::endl;
    std::cout<< "        slovo | pocet vyskytu" << std::endl;
    std::cout<< "--------------|--------------" << std::endl;

    // Nejcastejsi slova
    for (const auto& n : counter.getMostFrequentWords(10))
    {

        std::cout << n.first;
        for(int i = 14 - n.first.size(); i > 0;i--){
            std::cout << " ";
        }
        std::cout << "|";
        std::cout<< n.second << std::endl;
    }
    std::cout << std::endl;
    std::cout<< "Nejmene casta slova: " << std::endl;
    std::cout<< "        slovo | pocet vyskytu" << std::endl;
    std::cout<< "--------------|--------------" << std::endl;

    // Nejmene casta slova
    for (const auto& n : counter.getLeastFrequentWords(10))
    {
        std::cout << n.first;
        for(int i = 14 - n.first.size(); i > 0;i--){
            std::cout << " ";
        }
        std::cout << "|";
        std::cout<< n.second << std::endl;
    }


    return 0;
}
