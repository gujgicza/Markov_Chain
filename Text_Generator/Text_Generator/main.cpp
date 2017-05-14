#include <iostream>
#include <map>
#include <fstream>

#include <cstdlib>
#include <ctime>

// Adatstruktúra
using suffix = std::map<std::string, int>;
using prefix = std::string;
using markov_chain = std::map<prefix, suffix>;

// Beállítások
static int char_length = 5;                         // milyen hosszú karaktersorokat vizsgáljon
static std::string input_file_name = "alice.txt";   // melyik szöveg stílusát anulja meg
static long text_length = 2000;                     // milyen hosszú szöveget generáljon

int main() {
    
    markov_chain chain;
    std::ifstream is(input_file_name);
    char c; std::string prefix, suffix;
    
    // Markov-lánc megalkotása
    while (suffix.length() < char_length) { is.get(c); suffix.append(&c); }     // első prefix
    while (is.get(c)) {
        prefix = suffix;
        suffix.erase(0,1); suffix.append(&c);                                   // csúszóablak eggyel eltolása
        ++chain[prefix][suffix];                                                // Markov-lánc frissítése
    }
    
    // Szöveg generálás
    std::srand((int)std::time(0));
    int random = rand()%chain.size()+1;
    int range;
    std::string next_str;
    
    auto current = chain.begin();
    for(int i = 0; i < random; i++) ++current;      // Első prefix vélétlenszerű kiválasztása
    std::cout << current->first;
    
    for (int i = 0; i < text_length; i++) {         // Szöveggenerálás a beállított hosszig
        range = 0;
        std::for_each(current->second.begin(), current->second.end(), [&](auto element) {range += element.second;});
        random = rand()%range +1;                   // random szám attól függően, hogy a prefix milyen gyakran fordult elő a szövegben
        
        std::for_each(current->second.begin(), current->second.end(), [&, sum = 0](auto element) mutable {
            if(sum < random) next_str = element.first;
            sum += element.second;});               // szuffixek közül a valószínűségeknek megfelelően választ

        current = chain.find(next_str);             // beállítja a szuffixet a következő iteráció prefixének
        
        if(current == chain.end()) {                // ha nem talált volna következő elemet, random választ
            random = rand()%chain.size()+1;
            for(int i = 0; i < random; i++) --current;
        }
        std::cout << current->first.back();         // kiírja csak az utolsó karaktert (hiszen csak 1 karakter eltolás különbség van)
    }
}
