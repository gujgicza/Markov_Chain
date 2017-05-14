#include <iostream>
#include <map>
#include <fstream>

#include <cstdlib>
#include <ctime>

using suffix = std::map<std::string, int>;
using prefix = std::string;
using markov_chain = std::map<prefix, suffix>;

// Settings
static int char_length = 20;
static std::string input_file_name = "test.txt";
static long text_length = 500;

int main() {
    
    markov_chain chain;
    std::ifstream is(input_file_name);
    char c; std::string prefix, suffix;
    
    // Creating the Markov-chain
    while (suffix.length() < char_length) { is.get(c); suffix.append(&c); }
    while (is.get(c)) {
        prefix = suffix;
        suffix.erase(0,1); suffix.append(&c);
        ++chain[prefix][suffix];
    }
    
    // Generating text
    std::srand((int)std::time(0));
    int random = rand()%chain.size()+1;
    int range; std::string next_str;
    
    auto current = chain.begin();
    for(int i = 0; i < random; i++) ++current;
    std::cout << current->first;
    
    for (int i = 0; i < text_length; i++) {
        range = 0;
        std::for_each(current->second.begin(), current->second.end(), [&](auto element) {range += element.second;});
        random = rand()%range +1;
        
        std::for_each(current->second.begin(), current->second.end(), [&, sum = 0](auto element) mutable {
            if(sum < random) next_str = element.first;
            sum += element.second;});

        current = chain.find(next_str);
        
        if(current == chain.end()) for(int i = 0; i < rand()%chain.size()+1; i++) --current;
        std::cout << current->first.back();
    }
}
